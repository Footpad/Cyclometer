/*
 * NormalOperation.cpp
 *
 *  Created on: Feb 5, 2013
 *      Author: dam7633
 */

#include "NormalOperation.h"
#include "DisplaySpeed.h"
#include "DisplayDistance.h"
#include "Initialize.h"

const char *kDisplayDistanceState = "DisplayDistance";

NormalOperation::NormalOperation(StateParent* parent, StateContext* context, const char *initialState) :
State(parent, context) {
	if (initialState == kDisplayDistanceState) {
		childState = new DisplayDistance(this, context);
	} else {
		childState = new DisplaySpeed(this, context);
	}
	childState->entryAction();
}

void NormalOperation::accept(Event event) {
	if (event == evFullReset) {
		parent->doTransition(new Initialize(parent, context), NULL);
	} else {
		childState->accept(event);
	}
}
