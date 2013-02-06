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

	void accept(Event event);
};

#endif /* SETCIRCUMFERENCEIDLE_H_ */
