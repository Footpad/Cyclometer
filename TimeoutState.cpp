/*
 * TimeoutState.cpp
 *
 *  Created on: Feb 3, 2013
 *      Author: dam7633
 */

#include "TimeoutState.h"

// Forward declaration for the timer callback.
void timerExpired(sigval arg);

TimeoutState::TimeoutState(StateParent* parent, StateContext* context, time_t _timeout_s, long _timeout_ns) :
State(parent, context),
timeout_s(_timeout_s),
timeout_ns(_timeout_s) {}

void TimeoutState::entryAction() {
	// Create a timeout for the push button hold.
	struct sigevent event;
	SIGEV_THREAD_INIT(&event, timerExpired, this, NULL);

	// Configure the timeout spec.
	itimerspec timerSpec;
	timerSpec.it_value.tv_sec = timeout_s;
	timerSpec.it_value.tv_nsec = timeout_ns;
	timerSpec.it_interval.tv_sec = 0;
	timerSpec.it_interval.tv_nsec = 0;

	// Create and set the timer.
	timer_create(CLOCK_REALTIME, &event, &timer);
	timer_settime(timer, 0, &timerSpec, NULL);
}

void TimeoutState::exitAction() {
	// Cancel the timeout.
	timer_delete(timer);
}

void timerExpired(sigval arg) {
	// Get a reference to the timeout state and call its timeout function.
	TimeoutState* state = (TimeoutState*)arg.sival_ptr;
	state->timeout();
}
