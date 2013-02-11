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

DisplayInfo DisplayTime::getData() {
	DisplayInfo info;

	// Clear the decimal points.
	for (int i = 0; i < NUM_DIGITS; i++) {
		info.val[i] = 0;
		info.dp[i] = false;
	}

	// Always display the decimal point in between minutes and seconds.
	info.dp[2] = true;

	// The get the elapsed time in seconds.
	unsigned int elapsedTime = ((CyclometerController*)context)->getPulseScanner()->elapsedTime();
	unsigned int minutes = elapsedTime / 60;
	unsigned int seconds = elapsedTime % 60;

	info.val[0] = seconds % 10;
	info.val[1] = (seconds / 10) % 10;
	info.val[2] = minutes % 10;
	info.val[3] = (minutes / 10) % 10;

	return info;
}