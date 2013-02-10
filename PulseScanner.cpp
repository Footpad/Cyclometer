/*
 * PulseScanner.cpp
 *
 *  Created on: Feb 5, 2013
 *      Author: jpm8766
 */

#include "PulseScanner.h"

const struct sigevent *
interruptReceived(void *arg, int id) {
	((PulseScanner*) arg)->incrementPulseCount();

	//clear the interrupt.
	out8(((PulseScanner*) arg)->getCmdHandle(), (0b00001111));
	return NULL;
}

PulseScanner::PulseScanner(uintptr_t cmd) :
	cmd_handle(cmd) {
	circumference = 210;
	tripDistKM = 0;
	clockCount = 0;
	pulseCount = 0;
	units = KM;


}

PulseScanner::~PulseScanner() {
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
	//set the scaleFactor to either be for KM or to MILES
	double scaleFactor = (units == KM ? 1 : KM_TO_MILES);

	//return the Units/Hour
	return (tripDistKM / (clockCount / SECONDS_PER_HOUR)) * scaleFactor;
}

//TODO: implement this?
float PulseScanner::currentSpeed() {
	return 0.0f;
}

void PulseScanner::incrementCircumference() {
	circumference = (circumference == 210 ? 190 : circumference + 1);
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
