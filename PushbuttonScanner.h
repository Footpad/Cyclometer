/*
 * PushbuttonScanner.h
 *
 *  Created on: Feb 3, 2013
 *      Author: jpm8766
 */

#ifndef PUSHBUTTONSCANNER_H_
#define PUSHBUTTONSCANNER_H_

#include <unistd.h>
#include <stdint.h>       /* for uintptr_t */
#include <hw/inout.h>     /* for in*() and out*() functions */

#include <stdio.h>

#include "Thread.h"
#include "Common.h"
#include "EventCenter.h"

#define POLL_PERIOD (5000)
#define DEBOUNCE_PERIOD (200000)

#define LOW_MASK (0b00001111)

#define MASK_ARRAY_SIZE (3)
static const char MASK_ARRAY[] = {
		//SET button
		(0b00000001),
		//START/STOP button
		(0b00000010),
		//MODE button
		(0b00000100),
};


class PushbuttonScanner: public Thread {
public:
	PushbuttonScanner(uintptr_t input_port);
	virtual ~PushbuttonScanner();

	static void* running(void* args);

	void start();

	void stop();

private:
	bool killThread;
	uintptr_t input_port_handle;
};

#endif /* PUSHBUTTONSCANNER_H_ */
