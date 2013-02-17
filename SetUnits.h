/*
 * SetUnits.h
 *
 *  Created on: Feb 5, 2013
 *      Author: dam7633
 */

#ifndef SETUNITS_H_
#define SETUNITS_H_

#include "State.h"
#include "DataProvider.h"
#include "Initialize.h"


class SetUnits: public State {
public:
	SetUnits(StateParent* parent, StateContext* context);

	/**
	 * Accepts the events this state reacts to.
	 *
	 * @param event - the event which has occurred in the system.
	 */
	void accept(Event event);

	/**
	 * Return 3 blanks and either a 1 when kilometers or 2 when miles
	 *
	 * @return a proper DisplayInfo instance to display
	 */
	DisplayInfo getData();
};

#endif /* SETUNITS_H_ */
