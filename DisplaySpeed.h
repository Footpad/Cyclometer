/*
 * DisplaySpeed.h
 *
 *  Created on: Feb 5, 2013
 *      Author: dam7633
 */

#ifndef DISPLAYSPEED_H_
#define DISPLAYSPEED_H_

#include "State.h"

class DisplaySpeed: public State {
public:
	DisplaySpeed(StateParent* parent, StateContext* context);

	/**
	 * Accepts the events this state reacts to.
	 *
	 * @param event - the event which has occurred in the system.
	 */
	void accept(Event event);

	/**
	 * Returns speed in the form of "S.S" if the speed is less than 10 Units/Hour
	 * or "SS" if greater than 10 units per hour. This is done for Current Speed and
	 * Average speed and they are displayed as "S1S2"
	 *
	 * @return a formatted DisplayInfo for the speed.
	 */
	DisplayInfo getData();
	
private:
	// Writes the speed as specified in the requirements to
	// the given two digits and two decimal points.
	void formatSpeed(double speed, int* digits, bool* decimals);
};

#endif /* DISPLAYSPEED_H_ */
