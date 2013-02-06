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
