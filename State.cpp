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

State::State(StateParent* _parent, StateContext* _context, State* _childState) :
parent(_parent),
context(_context) {
	assert(parent);
	assert(context);
	assert(childState);
	childState = _childState;
}

StateParent* State::getParent() {
	return parent;
}
