/*
 * ResetIdle.cpp
 *
 *  Created on: Feb 3, 2013
 *      Author: dam7633
 */

#include "ResetIdle.h"
#include "ResetFull.h"
#include "ResetTrip.h"

ResetIdle::ResetIdle(StateParent* parent, StateContext* context) :
State(parent, context) {}

void ResetIdle::accept(Event event) {
	if (event == evAllDepressed) {
		parent->doTransition(new ResetFull(parent, context), NULL);
	} else if (event == evModeStartStopDepressed) {
		parent->doTransition(new ResetTrip(parent, context), NULL);
	}
}
