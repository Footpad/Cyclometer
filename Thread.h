/*
 * Thread.h
 *
 *  Created on: Dec 27, 2012
 *      Author: jeff
 */

#ifndef THREAD_H_
#define THREAD_H_

#include <pthread.h>

#define POLL_PERIOD (500)

class Thread {
public:
	Thread();
	virtual ~Thread();

	/**
	 * Join on the underlying thread.
	 */
	void join();

	/**
	 * Implement with a call to the create protected function with the
	 * proper statically defined function.
	 */
	virtual void start() = 0;

protected:
	void create(void*(*function)(void*), void* args);

private:
	pthread_t thread;
};

#endif /* THREAD_H_ */
