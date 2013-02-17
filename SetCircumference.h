/*
 * SetCircumference.h
 *
 *  Created on: Feb 5, 2013
 *      Author: dam7633
 */

#ifndef SETCIRCUMFERENCE_H_
#define SETCIRCUMFERENCE_H_

#include "State.h"
#include "DataProvider.h"
#include "Initialize.h"

class SetCircumference: public State {
public:
	SetCircumference(StateParent* parent, StateContext* context);

	/**
	 * Accepts the events this state reacts to.
	 *
	 * @param event - the event which has occurred in the system.
	 */
	void accept(Event event);

	/**
	 * Returns a properly formatted DisplayInfo instance which shows the
	 * current circumference of the wheel.
	 *
	 * @return a DisplayInfo with the current circumference of the wheel
	 */
	DisplayInfo getData();
};

#endif /* SETCIRCUMFERENCE_H_ */
