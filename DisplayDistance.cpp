/*
 * DisplayDistance.cpp
 *
 *  Created on: Feb 5, 2013
 *      Author: dam7633
 */

#include "DisplayDistance.h"
#include "SetCircumference.h"
#include "DisplayTime.h"
#include "NormalOperation.h"
#include "PulseScanner.h"
#include "CyclometerController.h"

DisplayDistance::DisplayDistance(StateParent* parent, StateContext* context) :
State(parent, context) {}

void DisplayDistance::accept(Event event) {
	if (event == evSetDepressed) {
		StateParent* context_parent = ((State*)parent)->getParent();
		context_parent->doTransition(new SetCircumference(context_parent, context), NULL);
	} else if (event == evModeDepressed) {
		parent->doTransition(new DisplayTime(parent, context), NULL);
	}
}

DisplayInfo DisplayDistance::getData() {
	DisplayInfo info;

	// Clear the display.
	for (int i = 0; i < NUM_DIGITS; i++) {
		info.val[i] = BLANK_DIGIT;
		info.dp[i] = false;
	}

	// Always display the decimal point.
	info.dp[1] = true;

	// The get the distance number.
	float distance = ((CyclometerController*)context)->getPulseScanner()->distance();

	info.val[0] = (int)(distance * 10) % 10; // Tenths
	info.val[1] = (int)distance % 10; // Ones

	if (distance >= 10) {
		info.val[2] = (int)(distance / 10) % 10; // Tens

		if (distance >= 100) {
			info.val[3] = (int)(distance / 100) % 10; // Hundreds
		}
	}

	return info;
}
