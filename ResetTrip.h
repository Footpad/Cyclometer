/*
 * ResetTrip.h
 *
 *  Created on: Feb 3, 2013
 *      Author: dam7633
 */

#ifndef RESETTRIP_H_
#define RESETTRIP_H_

#include "TimeoutState.h"

class ResetTrip: public TimeoutState {
public:
	ResetTrip(StateParent* parent, StateContext* context);

	/**
	 * Accepts the events this state reacts to.
	 *
	 * @param event - the event which has occurred in the system.
	 */
	void accept(Event event);

	/**
	 * Return to waiting for a new special button combo to be pressed on
	 * timeout and trigger a trip reset event.
	 */
	void timeout();
};

#endif /* RESETTRIP_H_ */
