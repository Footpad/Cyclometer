/*
 * StateParent.cpp
 *
 *  Created on: Feb 1, 2013
 *      Author: dam7633
 */

#include "StateParent.h"
#include "State.h"

StateParent::StateParent() :
childState(NULL) {}

StateParent::~StateParent() {
	delete childState;
}

void StateParent::doTransition(State* next, Action action) {
	assert(next);

	childState->exitAction();

	// If there is a transition action, perform it in order.
	if (action) {
		action();
	}

	// Delete the current state and make next the current state.
	delete childState;
	childState = next;

	childState->entryAction();
}
