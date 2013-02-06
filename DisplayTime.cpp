/*
 * DisplayTime.cpp
 *
 *  Created on: Feb 5, 2013
 *      Author: dam7633
 */

#include "DisplayTime.h"
#include "DisplaySpeed.h"
#include "CyclometerController.h"

static void toggleTripMode(StateContext* context) {
	((CyclometerController*)context)->toggleTripMode();
}

DisplayTime::DisplayTime(StateParent* parent, StateContext* context) :
State(parent, context) {}

void DisplayTime::accept(Event event) {
	if (event == evSetDepressed) {
		parent->doTransition(new DisplayTime(parent, context), toggleTripMode);
	} else if (event == evModeDepressed) {
		parent->doTransition(new DisplaySpeed(parent, context), NULL);
	}
}
