/*
 * State.cpp
 *
 *  Created on: Dec 29, 2012
 *      Author: jeff
 */

#include "State.h"

State::State(StateParent* _parent, StateContext* _context) :
parent(_parent),
context(_context) {
	assert(parent);
	assert(context);
}

void State::entryAction() {
	// Do nothing by default, override by concrete states.
}

void State::exitAction() {
	// Do nothing by default, override by concrete states.
}

StateParent* State::getParent() {
	return parent;
}

StateContext* State::getStateContext() {
	return context;
}

DisplayInfo State::getData() {
	DisplayInfo info;

	for (int i = 0; i < NUM_DIGITS; i++) {
		info.val[i] = BLANK_DIGIT;
		info.dp[i] = false;
	}

	return info;
}
