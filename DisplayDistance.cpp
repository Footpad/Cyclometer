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

	// The pulse scanner knows the speeds.
	PulseScanner* scanner = ((CyclometerController*)context)->getPulseScanner();

	// Get and format the speeds to the appropriate digits.
	// Hooray pointer arithmetic!
	formatSpeed(scanner->currentSpeed(), info.val, info.dp);
	formatSpeed(scanner->averageSpeed(),info.val + 2, info.dp + 2);

	return info;
}

void DisplayDistance::formatSpeed(float speed, int* digits, bool* decimals) {
	// Given a speed "AB.CD", if the speed is >= 10,
	// display "AB", otherwise display "B.C"
	bool isOverTen = speed >= 10;
	digits[0] = isOverTen ? (int)speed % 10 : (int)(speed * 10) % 10;
	digits[1] = isOverTen ? speed / 10 : (int)speed % 10;
	decimals[0] = false;
	decimals[1] = isOverTen ? false : true;
}
