/*
 * CyclometerController.cpp
 *
 *  Created on: Feb 3, 2013
 *      Author: dam7633
 */

#include "CyclometerController.h"
#include "Initialize.h"
#include "PulseScanner.h"

CyclometerController::CyclometerController(PulseScanner* scanner) :
	StateContext(), isFullResetDone(false), pulseScanner(scanner) {
	childState = new Initialize(this, this);
	childState->entryAction();

	pulseScanner->start();
}

bool CyclometerController::getIsFullResetDone() {
	return isFullResetDone;
}

void CyclometerController::setFullResetDone(bool _isFullResetDone) {
	isFullResetDone = _isFullResetDone;
}

PulseScanner* CyclometerController::getPulseScanner() {
	return pulseScanner;
}

DisplayInfo CyclometerController::getData() {
	DataProvider* dp = (DataProvider*)childState;
	DisplayInfo inf = dp->getData();
//	DisplayInfo inf;
//	for(int i = 0; i < NUM_DIGITS; i++) {
//		inf.val[i] = i;
//		inf.dp[i] = false;
//	}
	return inf;
}

