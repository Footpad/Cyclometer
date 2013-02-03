/*
 * Display.cpp
 *
 *  Created on: Jan 31, 2013
 *      Author: jpm8766
 */

#include "Display.h"

Display::Display(DataProvider* d, uintptr_t cat, uintptr_t an)
:data(d)
,cathode( cat )
,anode( an )
,killThread( false )
{}

Display::~Display() {}

void Display::start() {
	this->create(Display::running, this);
}

void Display::setDataProvider(DataProvider* next) {
	data = next;
}

void Display::stop() {
	killThread = true;
}

void* Display::running(void* args) {
	Display* self = (Display*)args;

	char cathWriteVal;
	char decimal;

	//clear all the anodes.
	out8(self->anode, in8(self->anode) | (0b00001111));

	while(!self->killThread) {
		// if the data provider isn't null, update the display
		if(self->data != NULL) {
			//First get the DisplayInfo
			DisplayInfo inf = self->data->getData();

			//Iterate over the anodes of the display.
			for(int i = 0; i < NUM_ANODES; i++) {
				//set the anode for the digit being worked on
				out8(self->anode, (in8(self->anode) & ~(1 << i)));

				//set the decimal point if specified
				decimal = 0;
				if( inf.dp[i] ) {
					decimal = DP_CATHODE;
				}
				//bitwise OR the decimal bit with the bits which define the number to display on this LED
				cathWriteVal = CATHODE_TABLE[inf.val[i]] | decimal;

				//write the value to the cathodes; inverted because it is Active LOW
				out8(self->cathode, ~cathWriteVal);

				//sleep for 25% of the total time spent on updating the display.
				usleep(SLEEP_PERIOD);

				//clear the anode.
				out8(self->anode, (in8(self->anode) | (1 << i)));
			}
		}
	}

	return NULL;
}
