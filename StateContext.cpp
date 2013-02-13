/*
 * StateContext.cpp
 *
 *  Created on: Jan 31, 2013
 *      Author: dam7633
 */

#include "StateContext.h"
#include <pthread.h>
#include "EventCenter.h"

StateContext::StateContext() {
	// Register the context with the event center.
	EventCenter::DefaultEventCenter()->registerContext(this);

	// Start the run loop of the context.
	start();
}

void StateContext::accept(Event event) {
	pthread_sleepon_lock();

	// Push the event into the state context's queue.
	eventQueue.push(event);

	// Signal that we can process an event from the queue.
	pthread_sleepon_signal(&eventQueue);

	pthread_sleepon_unlock();
}

void StateContext::handle(Event event) {
    childState->accept(event);
}

void* StateContext::run() {
	// Continuously pop events off our queue and accept them.
	while (!killThread) {
		pthread_sleepon_lock();

		// This thread should sleep until there is an event.
		while (eventQueue.empty()) {
			pthread_sleepon_wait(&eventQueue);
		}
        
        // Dequeue the next event and accept it.
        Event event = eventQueue.front();
        eventQueue.pop();
        handle(event);

		pthread_sleepon_unlock();
	}

	return NULL;
}

StateContext* StateContext::getStateContext() {
	return this;
}
