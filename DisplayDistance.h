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

class DisplayDistance: public State, DataProvider {
public:
	DisplayDistance(StateParent* parent, StateContext* context);

	void accept(Event event);

	DisplayInfo getData();

private:
	// Writes the speed as specified in the requirements to
	// the given two digits and two decimal points.
	void formatSpeed(float speed, int* digits, bool* decimals);
};

#endif /* DISPLAYDISTANCE_H_ */
