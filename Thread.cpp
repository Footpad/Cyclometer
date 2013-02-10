/*
 * Thread.cpp
 *
 *  Created on: Dec 27, 2012
 *      Author: jeff
 */

#include "Thread.h"

Thread::Thread() :
killThread(false),
thread(NULL) {}

Thread::~Thread() {}

void Thread::join() {
	pthread_join(thread, NULL);
}

void Thread::start() {
	pthread_create(&thread, NULL, pthread_entry, this);
}

void Thread::stop() {
	killThread = true;
}

void* Thread::pthread_entry(void* arg) {
	Thread* threadedObject = (Thread*)arg;
	return threadedObject->run();
}
