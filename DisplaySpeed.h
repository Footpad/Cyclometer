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
};

#endif /* DISPLAYSPEED_H_ */
