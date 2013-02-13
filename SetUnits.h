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

	void accept(Event event);

	DisplayInfo getData();
};

#endif /* SETUNITS_H_ */
