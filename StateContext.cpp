/*
 * StateContext.cpp
 *
 *  Created on: Jan 31, 2013
 *      Author: dam7633
 */

#include "StateContext.h"

StateContext::StateContext() {}

void StateContext::accept(Event event) {
	// TODO: make the StateContext a thread and accept events
	// asynchronously blocked by a semaphore on the eventQueue.
	//eventQueue.push(event);
	childState->accept(event);
}

void StateContext::accept() {
	Event event = eventQueue.front();
	eventQueue.pop();
	childState->accept(event);
}

StateContext* StateContext::getStateContext() {
	return this;
}
