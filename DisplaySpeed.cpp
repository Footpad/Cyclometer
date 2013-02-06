/*
 * DisplaySpeed.cpp
 *
 *  Created on: Feb 5, 2013
 *      Author: dam7633
 */

#include "DisplaySpeed.h"
#include "DisplayDistance.h"
#include "CyclometerController.h"

static void toggleTripMode(StateContext* context) {
	((CyclometerController*)context)->toggleTripMode();
}

DisplaySpeed::DisplaySpeed(StateParent* parent, StateContext* context) :
State(parent, context) {}

void DisplaySpeed::accept(Event event) {
	if (event == evSetDepressed) {
		parent->doTransition(new DisplaySpeed(parent, context), toggleTripMode);
	} else if (event == evModeDepressed) {
		parent->doTransition(new DisplayDistance(parent, context), NULL);
	}
}
