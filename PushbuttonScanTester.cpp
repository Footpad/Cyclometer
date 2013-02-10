/*
 * PushbuttonScanTester.cpp
 *
 *  Created on: Feb 5, 2013
 *      Author: jpm8766
 */

#include "PushbuttonScanTester.h"

PushbuttonScanTester::PushbuttonScanTester() :
StateContext() {}

PushbuttonScanTester::~PushbuttonScanTester() {}

void* PushbuttonScanTester::run() {
	printf("PBST Running\n");

	// Continuously pop events off our queue and accept them.
	while (!killThread) {
		pthread_sleepon_lock();

		// This thread should sleep until there is an event.
		while (eventQueue.empty()) {
			pthread_sleepon_wait(&eventQueue);
		}

		switch (eventQueue.front()) {
		// Used in anonymous transitions.
		case evNoEvent:
			printf("SCANTESTER: evNoEvent\n");
			break;
		case evFullReset:
			printf("SCANTESTER: evFullReset\n");
			break;
		case evSetDepressed:
			printf("SCANTESTER: evSetDepressed\n");
			break;
		case evSetReleased:
			printf("SCANTESTER: evSetReleased\n");
			break;
		case evModeDepressed:
			printf("SCANTESTER: evModeDepressed\n");
			break;
		case evModeReleased:
			printf("SCANTESTER: evModeReleased\n");
			break;
		case evStartStopDepressed:
			printf("SCANTESTER: evStartStopDepressed\n");
			break;
		case evStartStopReleased:
			printf("SCANTESTER: evStartStopReleased\n");
			break;
		case evModeStartStopDepressed:
			printf("SCANTESTER: evModeStartStopDepressed\n");
			break;
		case evModeStartStopReleased:
			printf("SCANTESTER: evModeStartStopReleased\n");
			break;
		case evAllDepressed:
			printf("SCANTESTER: evAllDepressed\n");
			break;
		case evAllReleased:
			printf("SCANTESTER: evAllReleased\n");
			break;
		default:
			printf("SCANTESTER: default???\n");
			break;
		}

		eventQueue.pop();

		pthread_sleepon_unlock();
	}

	return NULL;
}
