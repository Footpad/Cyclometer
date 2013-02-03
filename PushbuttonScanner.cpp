/*
 * PushbuttonScanner.cpp
 *
 *  Created on: Feb 3, 2013
 *      Author: jpm8766
 */

#include "PushbuttonScanner.h"

PushbuttonScanner::PushbuttonScanner(uintptr_t input_port)
:input_port_handle(input_port)
,killThread(false)
{ }

PushbuttonScanner::~PushbuttonScanner() { }

void* PushbuttonScanner::running(void* args) {
	PushbuttonScanner self = *((PushbuttonScanner*)args);

	char lastRead = in8(input_port_handle);
	char intermed;

	while(!self.killThread) {
		//Wait for there to be a change on the pushbutton inputs.
		while(lastRead == in8(input_port_handle)) {
			usleep(POLL_PERIOD);
		}
		//when a change is detected, wait for the inputs to settle.
		usleep(DEBOUNCE_PERIOD);
		//then save a copy of the inputs.
		intermed = in8(input_port_handle);

		//determine what has occurred by comparing the intermediate and the last read value.



		//save the last value read
		lastRead = intermed;
	}
}

void PushbuttonScanner::start() {
	this->create(PushbuttonScanner::running, this);
}

void PushbuttonScanner::stop() {
	killThread = true;
}
