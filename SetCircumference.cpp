/*
 * SetCircumference.cpp
 *
 *  Created on: Feb 5, 2013
 *      Author: dam7633
 */

#include "SetCircumference.h"
#include "SetCircumferenceIdle.h"
#include "NormalOperation.h"
#include "CyclometerController.h"

static void finishInitialization(StateContext* context) {
	((CyclometerController*)context)->setFullResetDone(true);
}

SetCircumference::SetCircumference(StateParent* parent, StateContext* context) :
State(parent, context) {
	childState = new SetCircumferenceIdle(this, context);
}

void SetCircumference::accept(Event event) {
	if (event == evSetDepressed) {
		if (((CyclometerController*)context)->getIsFullResetDone()) {
			parent->doTransition(new NormalOperation(parent, context, kDisplayDistanceState), NULL);
		} else {
			parent->doTransition(new NormalOperation(parent, context, NULL), finishInitialization);
		}
	} else {
		childState->accept(event);
	}
}

DisplayInfo SetCircumference::getData() {
	DisplayInfo info;

	// Clear the display info.
	for (int i = 0; i < NUM_DIGITS; i++) {
		info.dp[i] = false;
	}

	// Display 1 for kilometers, 2 for miles.
	int circumference = ((CyclometerController*)context)->getPulseScanner()->getCircumference();
	info.val[0] = circumference % 10;
	info.val[1] = (circumference % 100) / 10;
	info.val[2] = circumference / 100;

	return info;
}
