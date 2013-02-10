/*
 * PushbuttonScanTester.h
 *
 *  Created on: Feb 5, 2013
 *      Author: jpm8766
 */

#ifndef PUSHBUTTONSCANTESTER_H_
#define PUSHBUTTONSCANTESTER_H_

#include "StateContext.h"
#include "EventCenter.h"

#include <unistd.h>
#include <stdio.h>

class PushbuttonScanTester: public StateContext {
public:
	PushbuttonScanTester();
	virtual ~PushbuttonScanTester();

	/**
	 * Prints out events which are in the event queue.
	 */
	void* run();

private:
};

#endif /* PUSHBUTTONSCANTESTER_H_ */
