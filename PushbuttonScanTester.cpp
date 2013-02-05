/*
 * PushbuttonScanTester.cpp
 *
 *  Created on: Feb 5, 2013
 *      Author: jpm8766
 */

#include "PushbuttonScanTester.h"

PushbuttonScanTester::PushbuttonScanTester() {}

PushbuttonScanTester::~PushbuttonScanTester() {}

void PushbuttonScanTester::start() {
	EventCenter::DefaultEventCenter()->registerContext(this);
	this->create(PushbuttonScanTester::running, this);
}

void* PushbuttonScanTester::running(void* args) {
	PushbuttonScanTester* self = (PushbuttonScanTester*)args;

	printf("PBST Running\n");
	while(true) {
		while(self->eventQueue.size() == 0) {
			usleep(5000);
		}
		while(self->eventQueue.size() > 0) {
			switch (self->eventQueue.front()) {
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

			self->eventQueue.pop();
		}
	}

	return NULL;
}
