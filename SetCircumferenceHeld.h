/*
 * SetCircumferenceHeld.h
 *
 *  Created on: Feb 5, 2013
 *      Author: dam7633
 */

#ifndef SETCIRCUMFERENCEHELD_H_
#define SETCIRCUMFERENCEHELD_H_

#include "TimeoutState.h"

class SetCircumferenceHeld: public TimeoutState {
public:
	SetCircumferenceHeld(StateParent* parent, StateContext* context);

	/**
	 * Accepts the events this state reacts to.
	 *
	 * @param event - the event which has occurred in the system.
	 */
	void accept(Event event);

	/**
	 * Overriding entry action; every time this state is entered, increment
	 * the wheel circumference.
	 */
	void entryAction();

	/**
	 * When timeout occurs (waiting for evModeReleased) transition to this state again.
	 */
	void timeout();
};

#endif /* SETCIRCUMFERENCEHELD_H_ */
