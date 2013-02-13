/*
 * SetCircumferenceHeld.cpp
 *
 *  Created on: Feb 5, 2013
 *      Author: dam7633
 */

#include "SetCircumferenceHeld.h"
#include "SetCircumferenceIdle.h"
#include "CyclometerController.h"

SetCircumferenceHeld::SetCircumferenceHeld(StateParent* parent, StateContext* context) :
TimeoutState(parent, context, 1, 0) {}

void SetCircumferenceHeld::accept(Event event) {
	if (event == evModeReleased) {
		parent->doTransition(new SetCircumferenceIdle(parent, context), NULL);
	}
}

void SetCircumferenceHeld::entryAction() {
    // Perform the entry action of incrementing the circumference.
	((CyclometerController*)context)->getPulseScanner()->incrementCircumference();
    
    // Call the superclass's entry action to timeout after 1 second.
    TimeoutState::entryAction();
}

void SetCircumferenceHeld::timeout() {
	parent->doTransition(new SetCircumferenceHeld(parent, context), NULL);
}
