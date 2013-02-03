/*
 * State.h
 *
 *  Created on: Dec 29, 2012
 *      Author: jeff
 */

#ifndef STATE_H_
#define STATE_H_

#include <cstdio>
#include "Common.h"
#include "StateParent.h"

class StateContext; //forward declaration because we can't #include in both directions

class State : public StateParent {
public:
	State(StateParent* parent, StateContext* context);
	State(StateParent* parent, StateContext* context, State *childState);

	/**
	 * Accept an event and a context; transitions context to a new
	 * state if applicable.
	 *
	 * @param event - the event that the state is accepting
	 */
	virtual void accept(Event event) = 0;

	/**
	 * Entry action of the state when a transition occurs.
	 */
	virtual void entryAction() = 0;

	/**
	 * Exit action of the state when a transition occurs.
	 */
	virtual void exitAction() = 0;

	/**
	 * @return the parent of this state.
	 */
	StateParent* getParent();

protected:

	// Reference to the parent of this state.
	StateParent* parent;

	// Reference to the FSM that owns this state.
	StateContext* context;
};

#endif /* STATE_H_ */
