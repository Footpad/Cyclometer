/*
 * PushbuttonScanTester.h
 *
 *  Created on: Feb 5, 2013
 *      Author: jpm8766
 */

#ifndef PUSHBUTTONSCANTESTER_H_
#define PUSHBUTTONSCANTESTER_H_

#include "Thread.h"
#include "StateContext.h"
#include "EventCenter.h"

#include <unistd.h>
#include <stdio.h>

class PushbuttonScanTester: public Thread, StateContext {
public:
	PushbuttonScanTester();
	virtual ~PushbuttonScanTester();

	virtual void start();

	static void* running(void* args);

private:
};

#endif /* PUSHBUTTONSCANTESTER_H_ */
