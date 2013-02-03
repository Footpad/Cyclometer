#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include <stdint.h>       /* for uintptr_t */
#include <hw/inout.h>     /* for in*() and out*() functions */
#include <sys/neutrino.h> /* for ThreadCtl() */
#include <sys/mman.h>     /* for mmap_device_io() */

#include "DataProviderImpl.h"

#include "Display.h"

// DAQ Port addresses
#define DATA_BASE_ADDRESS (0x280)
#define DATA_PORT_A (DATA_BASE_ADDRESS + 8)
#define DATA_PORT_B (DATA_BASE_ADDRESS + 9)
#define DATA_DIRECTION (DATA_BASE_ADDRESS + 11)

#define PORT_LENGTH (1)

// Sets A and B to outputs...
#define SET_DIRECTION (0b10000000)

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
	// Declare the hardware port handles they are used...
	uintptr_t daq_dir_handle;
	uintptr_t daq_porta_handle;
	uintptr_t daq_portb_handle;

	/* Give this thread root permissions to access the hardware */
	getPermissions();

	/* Get a handle to Port A for controller inputs */
	daq_porta_handle = getHandle(DATA_PORT_A);
	/* Get a handle to Port B for controller outputs */
	daq_portb_handle = getHandle(DATA_PORT_B);
	/* Get a handle for the direction register to set Port A and B */
	daq_dir_handle = getHandle(DATA_DIRECTION);
	// set the data directions...
	out8(daq_dir_handle, SET_DIRECTION);

	//Declare where the data is gonna come from initially...
	DataProviderImpl dpi(1);
	Display d(&dpi, daq_porta_handle, daq_portb_handle);

	//Start the display
	d.start();

	//get another data provider...
	DataProviderImpl dpi2(2);

	//wait 3 seconds...
	sleep(3);

	//change up the data!
	d.setDataProvider(&dpi2);

	d.join();

	return EXIT_SUCCESS;
}
