/*
 * SetUnits.cpp
 *
 *  Created on: Feb 5, 2013
 *      Author: dam7633
 */

#include "SetUnits.h"
#include "SetCircumference.h"
#include "CyclometerController.h"
#include "PulseScanner.h"

static void toggleUnits(StateContext* context) {
	((CyclometerController*)context)->getPulseScanner()->toggleUnits();
}

SetUnits::SetUnits(StateParent* parent, StateContext* context) :
State(parent, context) {}

void SetUnits::accept(Event event) {
	if (event == evModeDepressed) {
		parent->doTransition(new SetUnits(parent, context), toggleUnits);
	} else if (event == evSetDepressed) {
		parent->doTransition(new SetCircumference(parent, context), NULL);
	} else if (event == evFullReset) {
		parent->doTransition(new Initialize(parent, context), NULL);
	}
}

DisplayInfo SetUnits::getData() {
	DisplayInfo info;

	// Clear the display info.
	for (int i = 0; i < NUM_DIGITS; i++) {
		info.val[i] = BLANK_DIGIT;
		info.dp[i] = false;
	}

	// Display 1 for kilometers, 2 for miles.
	DistanceUnit units = ((CyclometerController*)context)->getPulseScanner()->getUnits();
	info.val[0] = (units == KM) ? 1 : 2;

	return info;
}
