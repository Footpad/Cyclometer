/*
 * PulseScanner.cpp
 *
 *  Created on: Feb 5, 2013
 *      Author: jpm8766
 */

#include "PulseScanner.h"

const struct sigevent * PulseScanner::interruptReceived(void *arg, int id) {
	PulseScanner* self = (PulseScanner*) arg;
	self->pulseCount++;

	//clear the interrupt.
	out8(self->cmd_handle, (0b00001111));
	return NULL;
}

PulseScanner::PulseScanner(uintptr_t cmd) :
	cmd_handle(cmd) {

	this->scannerReset();
}

PulseScanner::~PulseScanner() {
}

void PulseScanner::scannerReset() {
	circumference = MAX_WHEEL_CIRCUMFERENCE;
	tripDistKM = 0;
	clockCount = 0;
	pulseCount = 0;
	units = KM;
	tripMode = TRIP_MANUAL;
	calcFlag = false;
}

void* PulseScanner::run() {
	//try to associate our interrupt with the board...
	interruptID = InterruptAttach(DAQ_IRQ, interruptReceived, this,
			sizeof(this), 0);
	if (interruptID == -1) {
		fprintf(stderr, "can't attach to IRQ %d\n", DAQ_IRQ);
		perror(NULL);
		exit(-1);
	}

	// clear any lingering interrupts.
	out8(cmd_handle, (0b00001111));

	//while running...
	while (!killThread) {
		//we should obtain the pulse count and clear it out at regular intervals
		//we should also accrue timeElapsed when appropriate
		//and update other statistics when possible (calculations enabled and the interval expired)
		printf( "%d\n", pulseCount );
		out8(cmd_handle, (0b00001111));
		usleep(1000000);
	}

	return NULL;
}

//TODO: this calculation may need to be externalized and only done every so often and stored as an attribute
//      so that the display doesnt consume a metric ton of computation resources constantly fetching this.
float PulseScanner::averageSpeed() {
	//return the Units/Hour
	return (distance() / (clockCount / SECONDS_PER_HOUR));
}

//TODO: implement this?
float PulseScanner::currentSpeed() {
	return 0.0f;
}

float PulseScanner::distance() {
	//set the scaleFactor to either be for KM or to MILES
	double scaleFactor = (units == KM ? 1 : KM_TO_MILES);
    
	//return the Units/Hour
	return (tripDistKM * scaleFactor);
}

unsigned int PulseScanner::elapsedTime() {
	return clockCount;
}

void PulseScanner::incrementCircumference() {
	circumference = (circumference == MAX_WHEEL_CIRCUMFERENCE ? MIN_WHEEL_CIRCUMFERENCE : circumference + 1);
}

int PulseScanner::getCircumference() {
	return circumference;
}

void PulseScanner::resetTripValues() {
	tripDistKM = 0;
	clockCount = 0;
	pulseCount = 0;
}

void PulseScanner::toggleUnits() {
	units = (units == KM ? MILES : KM);
}

DistanceUnit PulseScanner::getUnits() {
	return units;
}

uintptr_t PulseScanner::getCmdHandle() {
	return cmd_handle;
}

void PulseScanner::incrementPulseCount() {
	pulseCount++;
}

void PulseScanner::toggleTripMode() {
	tripMode = (tripMode == TRIP_AUTO ? TRIP_MANUAL : TRIP_AUTO);
	calcFlag = false;
}

void PulseScanner::toggleCalculate() {
	if(tripMode == TRIP_MANUAL) {
		calcFlag = !calcFlag;
	}
}
