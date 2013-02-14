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

	void accept(Event event);

	DisplayInfo getData();
};

#endif /* NORMALOPERATION_H_ */
