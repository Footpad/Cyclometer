/*
 * DisplayTime.h
 *
 *  Created on: Feb 5, 2013
 *      Author: dam7633
 */

#ifndef DISPLAYTIME_H_
#define DISPLAYTIME_H_

#include "State.h"

class DisplayTime: public State {
public:
	DisplayTime(StateParent* parent, StateContext* context);

	/**
	 * Accepts the events this state reacts to.
	 *
	 * @param event - the event which has occurred in the system.
	 */
	void accept(Event event);

	/**
	 * Formats and displays the time elapsed in the form "MM.ss" with all
	 * leading 0's present.
	 *
	 * @return the DisplayInfo representing the current time elapsed.
	 */
	DisplayInfo getData();
};

#endif /* DISPLAYTIME_H_ */
