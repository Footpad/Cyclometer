/*
 * DisplayTime.h
 *
 *  Created on: Feb 5, 2013
 *      Author: dam7633
 */

#ifndef DISPLAYTIME_H_
#define DISPLAYTIME_H_

#include "State.h"

class DisplayTime: public State {
public:
	DisplayTime(StateParent* parent, StateContext* context);

	void accept(Event event);
};

#endif /* DISPLAYTIME_H_ */
