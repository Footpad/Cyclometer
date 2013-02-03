/*
 * ResetWatchdog.h
 *
 *  Created on: Feb 3, 2013
 *      Author: dam7633
 */

#ifndef RESETWATCHDOG_H_
#define RESETWATCHDOG_H_

#include "StateContext.h"
#include "CyclometerController.h"

class ResetWatchdog: public StateContext {
public:
	ResetWatchdog(CyclometerController* cyclometer);

	/**
	 * Posts a full reset event to the default event center.
	 */
	void fullReset();

	/**
	 * Tells the cyclometer to reset its trip values.
	 */
	void tripValuesReset();

private:
	// We perform a trip values reset on the cyclometer.
	CyclometerController* cyclometer;
};

#endif /* RESETWATCHDOG_H_ */
