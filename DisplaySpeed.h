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

	void accept(Event event);

	DisplayInfo getData();
	
private:
	// Writes the speed as specified in the requirements to
	// the given two digits and two decimal points.
	void formatSpeed(float speed, int* digits, bool* decimals);
};

#endif /* DISPLAYSPEED_H_ */
