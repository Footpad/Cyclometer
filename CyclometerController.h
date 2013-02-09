/*
 * CyclometerController.h
 *
 *  Created on: Feb 3, 2013
 *      Author: dam7633
 */

#ifndef CYCLOMETERCONTROLLER_H_
#define CYCLOMETERCONTROLLER_H_

#include "StateContext.h"
#include "PulseScanner.h"

// Enumeration of the two trip modes for the cyclometer.
enum TripMode {
	TRIP_MANUAL = 0,
	TRIP_AUTO
};

class CyclometerController: public StateContext {
public:
	CyclometerController(PulseScanner* scanner);

	/**
	 * @return whether initialization has completed.
	 */
	bool getIsFullResetDone();

	/**
	 * @param whether initialization has completed.
	 */
	void setFullResetDone(bool isFullResetDone);

	/**
	 * Changes from auto to manual trip modes or vice versa.
	 */
	void toggleTripMode();

	/**
	 * Get a reference to the pulse scanner.
	 */
	PulseScanner* getPulseScanner();

private:
	// Used to determine which state is next after SetCircumference.
	bool isFullResetDone;

	// This controller's pulse scanner.
	PulseScanner* pulseScanner;

	// Which trip mode is currently being displayed.
	TripMode tripMode;
};

#endif /* CYCLOMETERCONTROLLER_H_ */
