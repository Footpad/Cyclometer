/*
 * StateParent.h
 *
 *  Created on: Feb 1, 2013
 *      Author: dam7633
 */

#ifndef STATEPARENT_H_
#define STATEPARENT_H_

#include "Common.h"

class State;

class StateParent {
public:
	StateParent();
	virtual ~StateParent();

	/**
	 * Changes the current child to the next state, and performs
	 * the exit, transition, and entry actions.
	 *
	 * @param next - the next state that the parent will transition to.
	 * @param action - the transition action of the transition.
	 */
	void doTransition(State* next, Action action);

protected:
	State* childState;
};

#endif /* STATEPARENT_H_ */
