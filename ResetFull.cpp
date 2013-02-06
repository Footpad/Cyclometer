/*
 * ResetFull.cpp
 *
 *  Created on: Feb 3, 2013
 *      Author: dam7633
 */

#include "ResetFull.h"
#include "ResetIdle.h"
#include "ResetWatchdog.h"

static void fullResetHeld(StateContext* context) {
	((ResetWatchdog*)context)->fullReset();
}

ResetFull::ResetFull(StateParent* parent, StateContext* context) :
TimeoutState(parent, context, 2, 0) {}

void ResetFull::accept(Event event) {
	if (event == evAllReleased) {
		parent->doTransition(new ResetIdle(parent, context), NULL);
	}
}

void ResetFull::timeout() {
	// Timing out after the 2 seconds will reset the whole cyclometer.
	parent->doTransition(new ResetIdle(parent, context), fullResetHeld);
}
