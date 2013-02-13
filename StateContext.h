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
#include "Thread.h"

class StateContext : public StateParent, public Thread {
public:
	StateContext();

	/**
	 * Accept an event which is passed to the states.
	 *
	 * @param event - the event that the context is accepting.
	 */
	void accept(Event event);

	/**
	 * Dequeues events from the event queue when there are events available.
	 */
	virtual void* run();

	StateContext* getStateContext();

protected:
    /**
     * Tell the child state to handle the event.
     *
     * @param event - the event that the child state is accepting.
     */
    virtual void handle(Event event);
    
	std::queue<Event> eventQueue;
};

#endif /* STATECONTEXT_H_ */
