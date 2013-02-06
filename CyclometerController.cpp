/*
 * CyclometerController.cpp
 *
 *  Created on: Feb 3, 2013
 *      Author: dam7633
 */

#include "CyclometerController.h"
#include "Initialize.h"
#include "PulseScanner.h"

CyclometerController::CyclometerController() :
isFullResetDone(false),
tripMode(TRIP_MANUAL) {
	childState = new Initialize(this, this);
	childState->entryAction();
}

bool CyclometerController::getIsFullResetDone() {
	return isFullResetDone;
}

void CyclometerController::setFullResetDone(bool _isFullResetDone) {
	isFullResetDone = _isFullResetDone;
	if (isFullResetDone == false) {
		tripMode = TRIP_MANUAL;
	}
}

void CyclometerController::toggleTripMode() {
	// TODO: Actually perform what needs to happen.
	tripMode = (tripMode == TRIP_AUTO) ? TRIP_MANUAL : TRIP_AUTO;
}

PulseScanner* CyclometerController::getPulseScanner() {
	return &pulseScanner;
}
