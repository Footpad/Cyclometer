/*
 * Display.h
 *
 *  Created on: Jan 31, 2013
 *      Author: jpm8766
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "Thread.h"
#include "DataProvider.h"

#include <unistd.h>
#include <stdint.h>       /* for uintptr_t */
#include <hw/inout.h>     /* for in*() and out*() functions */

// The refresh rate of the screen in Hz
#define NUM_ANODES (4)

#define COUNT_INTERVAL (10)

#define SLEEP_PERIOD (3500)

#define DP_CATHODE (0b00000001)

// Defines the bits which must be set in order to produce the index's value on a 7 segment display
// NOTE: Bits are set to 1 if they should be on and follow the pattern: 0bABCDEFG(DP)
static const char CATHODE_TABLE[] = {
		//zero
		(0b11111100),
		//one
		(0b01100000),
		//two
		(0b11011010),
		//three
		(0b11110010),
		//four
		(0b01100110),
		//five
		(0b10110110),
		//six
		(0b10111110),
		//seven
		(0b11100000),
		//eight
		(0b11111110),
		//nine
		(0b11110110),
		//blank display
		(0b00000000)
};

class Display: public Thread {
public:
	Display(DataProvider* d, uintptr_t cat, uintptr_t an);
	virtual ~Display();

	/**
	 * Continuously update the 7 segment display from a
	 * data provider.
	 */
	void* run();

	/**
	 * Set the data provider; setting this on the fly updates the display
	 * accordingly.
	 *
	 * @param next - the new DataProvider which the display will reflect
	 */
	void setDataProvider(DataProvider* next);

private:
	DataProvider* data;
	uintptr_t cathode;
	uintptr_t anode;

	bool killThread;
};

#endif /* DISPLAY_H_ */
