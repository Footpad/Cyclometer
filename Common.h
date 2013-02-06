/*
 * Common.h
 *
 *  Created on: Jan 31, 2013
 *      Author: dam7633
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <cassert>

class StateContext;

// Abstracting the type of system events.
typedef int Event;

// Function pointer for transition actions.
typedef void (*Action)(StateContext*);

// Enumeration of event types in the system.
enum EventTypes {
	// Unused
	evNoEvent = 0,

	// Events internal to the system.
	evFullReset,

	// External push button events.
	evSetDepressed,
	evSetReleased,
	evModeDepressed,
	evModeReleased,
	evStartStopDepressed,
	evStartStopReleased,
	evModeStartStopDepressed,
	evModeStartStopReleased,
	evAllDepressed,
	evAllReleased
};

#endif /* COMMON_H_ */
