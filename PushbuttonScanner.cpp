/*
 * PushbuttonScanner.cpp
 *
 *  Created on: Feb 3, 2013
 *      Author: jpm8766
 */

#include "PushbuttonScanner.h"

PushbuttonScanner::PushbuttonScanner(uintptr_t input_port) :
	input_port_handle(input_port) {
	killThread = false;
}

PushbuttonScanner::~PushbuttonScanner() {
}

void* PushbuttonScanner::running(void* args) {
	PushbuttonScanner self = *((PushbuttonScanner*) args);

	char lastRead = in8(self.input_port_handle);
	char intermed;

	char depressed;
	char released;

	int i;

	printf("PushbuttonScanner running\n");
	while (!self.killThread) {
		//Wait for there to be a change on the pushbutton inputs.
		while ((lastRead & LOW_MASK) == (in8(self.input_port_handle) & LOW_MASK)) {
			usleep(POLL_PERIOD);
		}
		printf("PushbuttonScanner: input changed...\n");
		//when a change is detected, wait for the inputs to settle.
		usleep(DEBOUNCE_PERIOD);
		//then save a copy of the inputs.
		intermed = in8(self.input_port_handle);

		//determine what has occurred by comparing the intermediate and the last read value.
		depressed = 0b00000000;
		released = 0b00000000;
		for(i = 0; i < MASK_ARRAY_SIZE; i++) {
			if ((lastRead & MASK_ARRAY[i]) != (intermed & MASK_ARRAY[i])) {
				//if that bit has changed...
				if((intermed & MASK_ARRAY[i]) == 0) {
					//it must have been released
					released |= MASK_ARRAY[i];
				} else if((intermed & MASK_ARRAY[i]) == MASK_ARRAY[i]) {
					//it must have been depressed
					depressed |= MASK_ARRAY[i];
				} else { /* cant reach this block */ }
			}
		}

		//if buttons were actually released...
		if(released != 0) {
			//if its a special combo (all or MODE+START/STOP), fire those events
			if((released & MASK_ARRAY[0]) && (released & MASK_ARRAY[1]) && (released & MASK_ARRAY[2])) {
				EventCenter::DefaultEventCenter().sendEvent(evAllReleased);
			} else if(!(released & MASK_ARRAY[0]) && (released & MASK_ARRAY[1]) && (released & MASK_ARRAY[2])) {
				EventCenter::DefaultEventCenter().sendEvent(evModeStartStopReleased);
			} else {
				//else fire the individual events
				if((released & MASK_ARRAY[0])) {
					EventCenter::DefaultEventCenter().sendEvent(evSetReleased);
				}
				if((released & MASK_ARRAY[1])) {
					EventCenter::DefaultEventCenter().sendEvent(evStartStopReleased);
				}
				if((released & MASK_ARRAY[2])) {
					EventCenter::DefaultEventCenter().sendEvent(evModeReleased);
				}
			}
		}

		//if buttons were actually depressed...
		if(depressed != 0) {
			//if its a special combo (all or MODE+START/STOP), fire those events
			if((depressed & MASK_ARRAY[0]) && (depressed & MASK_ARRAY[1]) && (depressed & MASK_ARRAY[2])) {
				EventCenter::DefaultEventCenter().sendEvent(evAllDepressed);
			} else if(!(depressed & MASK_ARRAY[0]) && (depressed & MASK_ARRAY[1]) && (depressed & MASK_ARRAY[2])) {
				EventCenter::DefaultEventCenter().sendEvent(evModeStartStopDepressed);
			} else {
				//else fire the individual events
				if((depressed & MASK_ARRAY[0])) {
					EventCenter::DefaultEventCenter().sendEvent(evSetDepressed);
				}
				if((depressed & MASK_ARRAY[1])) {
					EventCenter::DefaultEventCenter().sendEvent(evStartStopDepressed);
				}
				if((depressed & MASK_ARRAY[2])) {
					EventCenter::DefaultEventCenter().sendEvent(evModeDepressed);
				}
			}
		}

		//save the last value read
		lastRead = intermed;
	}

	return NULL;
}

void PushbuttonScanner::start() {
	this->create(PushbuttonScanner::running, this);
}

void PushbuttonScanner::stop() {
	killThread = true;
}
