/*
 * DisplaySpeed.cpp
 *
 *  Created on: Feb 5, 2013
 *      Author: dam7633
 */

#include "DisplaySpeed.h"
#include "DisplayDistance.h"
#include "CyclometerController.h"
#include "PulseScanner.h"

static void toggleTripMode(StateContext* context) {
	((CyclometerController*)context)->getPulseScanner()->toggleTripMode();
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

DisplayInfo DisplaySpeed::getData() {
	DisplayInfo info;

	// The pulse scanner knows the speeds.
	PulseScanner* scanner = ((CyclometerController*)context)->getPulseScanner();

	// Get and format the speeds to the appropriate digits.
	// Hooray pointer arithmetic!
	formatSpeed(scanner->currentSpeed(), info.val, info.dp);
	formatSpeed(scanner->averageSpeed(), info.val + 2, info.dp + 2);

	return info;
}

void DisplaySpeed::formatSpeed(float speed, int* digits, bool* decimals) {
	// Given a speed "AB.CD", if the speed is >= 10,
	// display "AB", otherwise display "B.C"
	bool isOverTen = speed >= 10;
	digits[0] = isOverTen ? (int)speed % 10 : (int)(speed * 10) % 10;
	digits[1] = isOverTen ? (int)(speed / 10) % 10 : (int)speed % 10;
	decimals[0] = false;
	decimals[1] = isOverTen ? false : true;
}
