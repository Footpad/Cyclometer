//Global includes.
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>       /* for uintptr_t */
#include <hw/inout.h>     /* for in*() and out*() functions */
#include <sys/neutrino.h> /* for ThreadCtl() */
#include <sys/mman.h>     /* for mmap_device_io() */


//-------- Local Includes ----------//

//Old test class includes
//#include "DataProviderImpl.h"
//#include "PushbuttonScanTester.h"

#include "PulseScanner.h"
#include "PushbuttonScanner.h"
#include "Display.h"
#include "CyclometerController.h"
#include "ResetWatchdog.h"

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
uintptr_t ctrl_handle;
uintptr_t cmd_handle;

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
	/* Get a handle to the command port for interrupts */
	cmd_handle = getHandle(DATA_BASE_ADDRESS);
	/* Get a handle to the control register... */
	ctrl_handle = getHandle(DATA_BASE_ADDRESS + 4);

	//enable Digital IO Interrupts (Ext Trig pin)...
	out8(ctrl_handle, (0b00011111));

	//Start the pulse scanner...
	PulseScanner pulseScanner(cmd_handle);

	//Start the pushbutton scanner...
	PushbuttonScanner pushbuttonScanner(daq_portc_handle);
	pushbuttonScanner.start();

	//Start the CyclometerController
	CyclometerController cyclometerController(&pulseScanner);

	//Start the ResetWatchdog
	ResetWatchdog resetWatchdog(&cyclometerController);

	//Start the display thread.
	// TODO: Figure out why the current implementation of DataProvider is crashing.
	Display display((DataProvider*)&cyclometerController, daq_porta_handle, daq_portb_handle);
	//Display display(NULL, daq_porta_handle, daq_portb_handle);
	//Start the display
	display.start();

	for (;;) {
		// Loop infinitely because this is an embedded system.
	}

	// Clean up threads.
	// NB: Program will never get here, just for show.
	pulseScanner.stop();
	pushbuttonScanner.stop();
	cyclometerController.stop();
	resetWatchdog.stop();
	display.stop();
	pulseScanner.join();
	pushbuttonScanner.join();
	cyclometerController.join();
	resetWatchdog.join();
	display.join();

	return EXIT_SUCCESS;
}
