/*
 * ResetFull.h
 *
 *  Created on: Feb 3, 2013
 *      Author: dam7633
 */

#ifndef RESETFULL_H_
#define RESETFULL_H_

#include "TimeoutState.h"

class ResetFull: public TimeoutState {
public:
	ResetFull(StateParent* parent, StateContext* context);

	/**
	 * Accepts the events this state reacts to.
	 *
	 * @param event - the event which has occurred in the system.
	 */
	void accept(Event event);

	/**
	 * Return to waiting for a special button combo to be pressed on timeout
	 * and generate a system reset event.
	 */
	void timeout();
};

#endif /* RESETFULL_H_ */
