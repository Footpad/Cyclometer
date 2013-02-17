/*
 * ResetIdle.h
 *
 *  Created on: Feb 3, 2013
 *      Author: dam7633
 */

#ifndef RESETIDLE_H_
#define RESETIDLE_H_

#include "State.h"

class ResetIdle: public State {
public:
	ResetIdle(StateParent* parent, StateContext* context);

	/**
	 * Accepts the events this state reacts to.
	 *
	 * @param event - the event which has occurred in the system.
	 */
	void accept(Event event);
};

#endif /* RESETIDLE_H_ */
