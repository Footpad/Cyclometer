/*
 * PulseScanner.cpp
 *
 *  Created on: Feb 5, 2013
 *      Author: jpm8766
 */

#include "PulseScanner.h"

PulseScanner::PulseScanner() {
	killThreads = false;
	circumference = 210;
	tripDistKM = 0;
	clockCount = 0;
	pulseCount = 0;
	units = KM;
}

PulseScanner::~PulseScanner() { }

void PulseScanner::start() {
	this->create(PulseScanner::running, this);
}

void PulseScanner::stop() {
	killThreads = true;
}

void* PulseScanner::running(void* args) {
	PulseScanner* self = (PulseScanner*)args;

	while(!self->killThreads) {

	}

	return NULL;
}

//TODO: this calculation may need to be externalized and only done every so often and stored as an attribute
//      so that the display doesnt consume a metric ton of computation resources constantly fetching this.
float PulseScanner::averageSpeed() {
	//set the scaleFactor to either be for KM or to MILES
	double scaleFactor = (units == KM ? 1 : KM_TO_MILES);

	//return the Units/Hour
	return (tripDistKM / (clockCount/SECONDS_PER_HOUR)) * scaleFactor;
}

//TODO: implement this?
float PulseScanner::currentSpeed() {
	return 0.0f;
}

void PulseScanner::incrementCircumference() {
	circumference = (circumference == 210 ? 190 : circumference + 1);
}

void PulseScanner::resetTripValues() {
	tripDistKM = 0;
	clockCount = 0;
	pulseCount = 0;
}

void PulseScanner::toggleUnits() {
	units = (units == KM ? MILES : KM);
}
