/*
 * Thread.cpp
 *
 *  Created on: Dec 27, 2012
 *      Author: jeff
 */

#include "Thread.h"

Thread::Thread() {
	thread = NULL;
}

Thread::~Thread() {}

void Thread::join() {
	pthread_join(thread, NULL);
}

void Thread::create(void*(function)(void*), void* args) {
	pthread_create(&thread, NULL, function, args);
}
