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
