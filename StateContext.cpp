/*
 * StateContext.cpp
 *
 *  Created on: Jan 31, 2013
 *      Author: dam7633
 */

#include "StateContext.h"

StateContext::StateContext() {}

StateContext::~StateContext() {}

void StateContext::accept(Event event) {
	eventQueue.push(event);
}

void StateContext::accept() {
	Event event = eventQueue.front();
	eventQueue.pop();
	childState->accept(event);
}
