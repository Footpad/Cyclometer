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
#include <math.h>

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
	formatSpeed(scanner->currentSpeed(), info.val + 2, info.dp + 2);
	formatSpeed(scanner->averageSpeed(), info.val, info.dp);

	return info;
}

void DisplaySpeed::formatSpeed(double speed, int* digits, bool* decimals) {
	// Given a speed "AB.CD", if the speed is >= 10,
	// display "AB", otherwise display "B.C"
	// Speeds are rounded to the nearest minimum sig fig.
	bool isOverTen = lround(speed) >= 10;
	digits[0] = isOverTen ? lround(speed) % 10 : lround(speed * 10) % 10;
	digits[1] = isOverTen ? (lround(speed) / 10) % 10 : lround(speed) % 10;
	decimals[0] = false;
	decimals[1] = isOverTen ? false : true;
}
