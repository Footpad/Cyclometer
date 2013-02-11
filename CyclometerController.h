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
#include "DataProvider.h"

class CyclometerController: public StateContext, DataProvider {
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
	 * @return a reference to the pulse scanner.
	 */
	PulseScanner* getPulseScanner();

	/**
	 * @return the active state's getData.
	 */
	DisplayInfo getData();

private:
	// Used to determine which state is next after SetCircumference.
	bool isFullResetDone;

	// This controller's pulse scanner.
	PulseScanner* pulseScanner;

	// Which trip mode is currently being displayed.
	TripMode tripMode;
};

#endif /* CYCLOMETERCONTROLLER_H_ */
