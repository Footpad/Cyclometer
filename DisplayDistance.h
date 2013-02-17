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

	/**
	 * Accepts the events this state reacts to.
	 *
	 * @param event - the event which has occurred in the system.
	 */
	void accept(Event event);

	/**
	 * Formats the distance traveled as "DDD.D" with 1 leading 0 if < 1.
	 *
	 * @return the formatted distance.
	 */
	DisplayInfo getData();
};

#endif /* DISPLAYDISTANCE_H_ */
