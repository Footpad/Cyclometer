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

class Initialize : public State, DataProvider {
public:
	Initialize(StateParent* parent, StateContext* context);

	void accept(Event event);
	void entryAction();

	DisplayInfo getData();
};

#endif /* INITIALIZE_H_ */
