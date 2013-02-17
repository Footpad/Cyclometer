/*
 * NormalOperation.h
 *
 *  Created on: Feb 5, 2013
 *      Author: dam7633
 */

#ifndef NORMALOPERATION_H_
#define NORMALOPERATION_H_

#include "State.h"

// Used to determine the initial child state.
extern const char *kDisplayDistanceState;

class NormalOperation: public State {
public:
	NormalOperation(StateParent* parent, StateContext* context, const char *initialState);

	/**
	 * Accepts the events this state reacts to.
	 *
	 * @param event - the event which has occurred in the system.
	 */
	void accept(Event event);

	/**
	 * Delegate to the child state (Distance, Time, Speed).
	 *
	 * @return the child states DisplayInfo
	 */
	DisplayInfo getData();
};

#endif /* NORMALOPERATION_H_ */
