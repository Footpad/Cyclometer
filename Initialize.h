/*
 * Initialize.h
 *
 *  Created on: Feb 5, 2013
 *      Author: dam7633
 */

#ifndef INITIALIZE_H_
#define INITIALIZE_H_

#include "State.h"
#include "DataProvider.h"

class Initialize : public State {
public:
	Initialize(StateParent* parent, StateContext* context);

	/**
	 * Accepts the events this state reacts to.
	 *
	 * @param event - the event which has occurred in the system.
	 */
	void accept(Event event);

	/**
	 * Perform a full reset on all objects in the system.
	 */
	void entryAction();

	/**
	 * While initializing, display just decimal points with no numbers.
	 *
	 * @return an "Initializing" message in the form of no digits and all
	 *         decimal points lit.
	 */
	DisplayInfo getData();
};

#endif /* INITIALIZE_H_ */
