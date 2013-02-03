/*
 * EventCenter.cpp
 *
 *  Created on: Feb 1, 2013
 *      Author: dam7633
 */

#include "EventCenter.h"

EventCenter::EventCenter() {}

EventCenter::~EventCenter() {}

void EventCenter::registerContext(StateContext* context) {
	contexts.push_back(context);
}

void EventCenter::sendEvent(Event event) {
	// Send the event to all of the registered contexts.
	for(std::vector<StateContext*>::size_type i = 0; i != contexts.size(); i++) {
		contexts[i]->accept(event);
	}
}
