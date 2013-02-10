/*
 * Initialize.cpp
 *
 *  Created on: Feb 5, 2013
 *      Author: dam7633
 */

#include "Initialize.h"
#include "SetUnits.h"
#include "CyclometerController.h"

Initialize::Initialize(StateParent* parent, StateContext* context) :
State(parent, context) {}

void Initialize::accept(Event event) {
	// We won't actually accept any events because
	// of our anonymous transition. Implemented because
	// accept is pure virtual.
}

void Initialize::entryAction() {
	((CyclometerController*)context)->setFullResetDone(false);
	parent->doTransition(new SetUnits(parent, context), NULL);
}

DisplayInfo Initialize::getData() {
	DisplayInfo info;

	// Numbers should all be blank, decimal points should be lit.
	for (int i = 0; i < NUM_DIGITS; i++) {
		info.val[i] = BLANK_DIGIT;
		info.dp[i] = true;
	}
	return info;
}
