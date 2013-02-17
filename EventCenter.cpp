/*
 * EventCenter.cpp
 *
 *  Created on: Feb 1, 2013
 *      Author: dam7633
 */

#include "EventCenter.h"

EventCenter::EventCenter() {
}

EventCenter::~EventCenter() {
}

void EventCenter::registerContext(StateContext* context) {
	contexts.push_back(context);
}

void EventCenter::sendEvent(Event event) {
	// Send the event to all of the registered contexts.
	for (std::vector<StateContext*>::size_type i = 0; i != contexts.size(); i++) {
		contexts[i]->accept(event);
	}
}

// The instance of the EventCenter; contained in the scope of the module where
// no one but EventCenter can see it.
static EventCenter* defaultEventCenter = NULL;

EventCenter* EventCenter::DefaultEventCenter() {
	if( defaultEventCenter == NULL ) {
		defaultEventCenter = new EventCenter();
	}
	return defaultEventCenter;
}
