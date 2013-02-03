/*
 * TimeoutState.h
 *
 *  Created on: Feb 3, 2013
 *      Author: dam7633
 */

#ifndef TIMEOUTSTATE_H_
#define TIMEOUTSTATE_H_

#include "State.h"

#include <time.h>
#include <sys/siginfo.h>

class TimeoutState: public State {
public:
	TimeoutState(StateParent* parent, StateContext* context, time_t timeout_s, long timeout_ns);

	/**
	 * Overridden entry and exit points responsible for the timeout
	 * functionality. You must call these from subclasses of
	 * TimeoutState if you wish to have custom entry/exit actions.
	 */
	virtual void entryAction();
	virtual void exitAction();

	/**
	 * Function which is called when the timeout has expired.
	 */
	virtual void timeout() = 0;

private:
	// Timer for timeout functionality.
	timer_t timer;

	// The length of a timeout in seconds.
	time_t timeout_s;

	// The length of the timeout in nanoseconds.
	long timeout_ns;
};

#endif /* TIMEOUTSTATE_H_ */
