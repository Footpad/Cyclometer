/*
 * ResetTrip.cpp
 *
 *  Created on: Feb 3, 2013
 *      Author: dam7633
 */

#include "ResetTrip.h"
#include "ResetIdle.h"
#include "ResetWatchdog.h"

ResetTrip::ResetTrip(StateParent* parent, StateContext* context) :
TimeoutState(parent, context, 2, 0) {}

void ResetTrip::accept(Event event) {
	if (event == evModeStartStopReleased) {
		parent->doTransition(new ResetIdle(parent, context), NULL);
	}
}

void ResetTrip::timeout() {
	// Timing out after the 2 seconds will reset the trip values.
	((ResetWatchdog*)context)->tripValuesReset();
}
