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
	((CyclometerController*)context)->getPulseScanner()->incrementCircumference();
}

void SetCircumferenceHeld::timeout() {
	parent->doTransition(new SetCircumferenceHeld(parent, context), NULL);
}
