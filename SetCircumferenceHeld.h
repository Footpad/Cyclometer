/*
 * SetCircumferenceHeld.h
 *
 *  Created on: Feb 5, 2013
 *      Author: dam7633
 */

#ifndef SETCIRCUMFERENCEHELD_H_
#define SETCIRCUMFERENCEHELD_H_

#include "TimeoutState.h"

class SetCircumferenceHeld: public TimeoutState {
public:
	SetCircumferenceHeld(StateParent* parent, StateContext* context);

	void accept(Event event);
	void entryAction();
	void timeout();
};

#endif /* SETCIRCUMFERENCEHELD_H_ */
