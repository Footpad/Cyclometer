/*
 * StateContext.h
 *
 *  Created on: Jan 31, 2013
 *      Author: dam7633
 */

#ifndef STATECONTEXT_H_
#define STATECONTEXT_H_

#include <queue>
#include "State.h"
#include "StateParent.h"

class StateContext : public StateParent {
public:
	StateContext();
	virtual ~StateContext();

	/**
	 * Accept an event which is passed to the states.
	 *
	 * @param event - the event that the context is accepting.
	 */
	void accept(Event event);

private:
	/**
	 * Accept an even which has been enqueued to the context.
	 */
	void accept();

protected:
	std::queue<Event> eventQueue;
};

#endif /* STATECONTEXT_H_ */
