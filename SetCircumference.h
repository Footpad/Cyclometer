/*
 * SetCircumference.h
 *
 *  Created on: Feb 5, 2013
 *      Author: dam7633
 */

#ifndef SETCIRCUMFERENCE_H_
#define SETCIRCUMFERENCE_H_

#include "State.h"
#include "DataProvider.h"

class SetCircumference: public State, DataProvider {
public:
	SetCircumference(StateParent* parent, StateContext* context);

	void accept(Event event);

	DisplayInfo getData();
};

#endif /* SETCIRCUMFERENCE_H_ */
