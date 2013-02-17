/*
 * SetCircumferenceIdle.h
 *
 *  Created on: Feb 5, 2013
 *      Author: dam7633
 */

#ifndef SETCIRCUMFERENCEIDLE_H_
#define SETCIRCUMFERENCEIDLE_H_

#include "State.h"

class SetCircumferenceIdle: public State {
public:
	SetCircumferenceIdle(StateParent* parent, StateContext* context);

	/**
	 * Accepts the events this state reacts to.
	 *
	 * @param event - the event which has occurred in the system.
	 */
	void accept(Event event);
};

#endif /* SETCIRCUMFERENCEIDLE_H_ */
