/*
 * SetUnits.cpp
 *
 *  Created on: Feb 5, 2013
 *      Author: dam7633
 */

#include "SetUnits.h"
#include "SetCircumference.h"
#include "CyclometerController.h"

static void toggleUnits(StateContext* context) {
	((CyclometerController*)context)->getPulseScanner()->toggleUnits();
}

SetUnits::SetUnits(StateParent* parent, StateContext* context) :
State(parent, context) {}

void SetUnits::accept(Event event) {
	if (event == evModeDepressed) {
		parent->doTransition(new SetUnits(parent, context), toggleUnits);
	} else if (event == evSetDepressed) {
		parent->doTransition(new SetCircumference(parent, context), NULL);
	}
}
