/*
 * Initialize.h
 *
 *  Created on: Feb 5, 2013
 *      Author: dam7633
 */

#ifndef INITIALIZE_H_
#define INITIALIZE_H_

#include "State.h"

class Initialize : public State {
public:
	Initialize(StateParent* parent, StateContext* context);

	void accept(Event event);
	void entryAction();
};

#endif /* INITIALIZE_H_ */
