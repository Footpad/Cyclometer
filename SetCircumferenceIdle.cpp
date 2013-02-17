/*
 * SetCircumferenceIdle.cpp
 *
 *  Created on: Feb 5, 2013
 *      Author: dam7633
 */

#include "SetCircumferenceIdle.h"
#include "SetCircumferenceHeld.h"

SetCircumferenceIdle::SetCircumferenceIdle(StateParent* parent, StateContext* context) :
State(parent, context) {}

void SetCircumferenceIdle::accept(Event event) {
	//only react to mode being depressed
	if (event == evModeDepressed) {
		parent->doTransition(new SetCircumferenceHeld(parent, context), NULL);
	}
}
