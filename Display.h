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
#define REFRESH_RATE (120)
#define NUM_ANODES (4)

#define SLEEP_PERIOD ((1000000/REFRESH_RATE)/NUM_ANODES)

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
	 * Implement with a call to the create protected function with the
	 * proper statically defined function.
	 */
	virtual void start();

	/**
	 * Set the data provider; setting this on the fly updates the display
	 * accordingly.
	 *
	 * @param next - the new DataProvider which the display will reflect
	 */
	void setDataProvider(DataProvider* next);

	/**
	 * Stop the display thread from running.
	 */
	void stop();

	static void* running(void* args);

private:
	DataProvider* data;
	uintptr_t cathode;
	uintptr_t anode;

	bool killThread;
};

#endif /* DISPLAY_H_ */
