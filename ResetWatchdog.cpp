/*
 * ResetWatchdog.cpp
 *
 *  Created on: Feb 3, 2013
 *      Author: dam7633
 */

#include "ResetWatchdog.h"
#include "EventCenter.h"
#include "ResetIdle.h"

ResetWatchdog::ResetWatchdog(CyclometerController* _cyclometer) :
StateContext(),
cyclometer(_cyclometer) {
	childState = new ResetIdle(this, this);
	childState->entryAction();
}

void ResetWatchdog::fullReset() {
	EventCenter::DefaultEventCenter()->sendEvent(evFullReset);
}

void ResetWatchdog::tripValuesReset() {
	EventCenter::DefaultEventCenter()->sendEvent(evTripReset);
}
