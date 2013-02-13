/*
 * DisplayDistance.h
 *
 *  Created on: Feb 5, 2013
 *      Author: dam7633
 */

#ifndef DISPLAYDISTANCE_H_
#define DISPLAYDISTANCE_H_

#include "State.h"
#include "DataProvider.h"

class DisplayDistance: public State {
public:
	DisplayDistance(StateParent* parent, StateContext* context);

	void accept(Event event);

	DisplayInfo getData();
};

#endif /* DISPLAYDISTANCE_H_ */
