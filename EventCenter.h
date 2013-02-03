/*
 * EventCenter.h
 *
 *  Created on: Feb 1, 2013
 *      Author: dam7633
 */

#ifndef EVENTCENTER_H_
#define EVENTCENTER_H_

#include <vector>
#include "StateContext.h"

class EventCenter {
public:
	EventCenter();
	virtual ~EventCenter();

	/**
	 * Return the global default event center for the system.
	 *
	 * @return a reference to the default event center.
	 */
	static EventCenter& DefaultEventCenter() {
		static EventCenter defaultEventCenter;
		return defaultEventCenter;
	}

	/**
	 * Register a state context to receive events.
	 *
	 * @param context - the state context to register.
	 */
	void registerContext(StateContext* context);

	/**
	 * Broadcast an event to all registered state contexts.
	 *
	 * @param event - the event to broadcast.
	 */
	void sendEvent(Event event);

private:

	// A list of registered state contexts.
	std::vector<StateContext*> contexts;
};

#endif /* EVENTCENTER_H_ */
