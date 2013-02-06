#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include <stdint.h>       /* for uintptr_t */
#include <hw/inout.h>     /* for in*() and out*() functions */
#include <sys/neutrino.h> /* for ThreadCtl() */
#include <sys/mman.h>     /* for mmap_device_io() */

#include "DataProviderImpl.h"

#include "PushbuttonScanTester.h"
#include "PushbuttonScanner.h"

#include "Display.h"

#include "CyclometerController.h"

#include "ResetWatchdog.h"

#include "EventCenter.h"

// DAQ Port addresses
#define DATA_BASE_ADDRESS (0x280)
#define DATA_PORT_A (DATA_BASE_ADDRESS + 8)
#define DATA_PORT_B (DATA_BASE_ADDRESS + 9)
#define DATA_PORT_C (DATA_BASE_ADDRESS + 10)
#define DATA_DIRECTION (DATA_BASE_ADDRESS + 11)

#define PORT_LENGTH (1)

// Sets A and B to outputs and C to input
#define SET_DIRECTION (0b10001001)

// Declare the hardware port handles they are used...
uintptr_t daq_dir_handle;
uintptr_t daq_porta_handle;
uintptr_t daq_portb_handle;
uintptr_t daq_portc_handle;

/**
 * Get root permissions to get access to hardware...
 */
void getPermissions() {
	int privity_err = ThreadCtl(_NTO_TCTL_IO, NULL );
	if (privity_err == -1) {
		fprintf(stderr, "can't get root permissions\n");
		exit(-1);
	}
}

/**
 * Get a handle to hardware.
 *
 * @param address - the memory mapped address of the hardware register requested
 * @return the uintptr_t handle to the hardware register of 8 bit length
 */
uintptr_t getHandle(int address) {
	uintptr_t ret = mmap_device_io(PORT_LENGTH, address);
	if (ret == MAP_DEVICE_FAILED) {
		fprintf(stderr, "can't get handle on %d\n", address);
		exit(-1);
	}

	return ret;
}

int main(int argc, char *argv[]) {
	/* Give this thread root permissions to access the hardware */
	getPermissions();

	/* Get a handle for the direction register to set Port A and B */
	daq_dir_handle = getHandle(DATA_DIRECTION);
	// set the data directions...
	out8(daq_dir_handle, SET_DIRECTION);

	/* Get a handle to Port A for controller outputs 1 */
	daq_porta_handle = getHandle(DATA_PORT_A);
	/* Get a handle to Port B for controller outputs 2 */
	daq_portb_handle = getHandle(DATA_PORT_B);
	/* Get a handle to Port C for controller inputs */
	daq_portc_handle = getHandle(DATA_PORT_C);

	//Start the display thread.
	Display d(NULL, daq_porta_handle, daq_portb_handle);
	//Start the display
	d.start();

	//Start the pushbutton scanner...
	PushbuttonScanner pbs(daq_portc_handle);
	pbs.start();

	//Start the CyclometerController
	CyclometerController cc;

	//Start the ResetWatchdog
	ResetWatchdog rw(&cc);

	//Register all the state contexts
	EventCenter::DefaultEventCenter()->registerContext(&rw);
	EventCenter::DefaultEventCenter()->registerContext(&cc);

	// TODO: Do we join on someone or just let the main thread loop infinitely?
	d.join();

	return EXIT_SUCCESS;
}
