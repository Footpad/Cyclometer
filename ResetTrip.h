/*
 * ResetTrip.h
 *
 *  Created on: Feb 3, 2013
 *      Author: dam7633
 */

#ifndef RESETTRIP_H_
#define RESETTRIP_H_

#include "TimeoutState.h"

class ResetTrip: public TimeoutState {
public:
	ResetTrip(StateParent* parent, StateContext* context);

	void accept(Event event);
	void timeout();
};

#endif /* RESETTRIP_H_ */
