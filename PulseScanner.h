/*
 * PulseScanner.h
 *
 *  Created on: Feb 5, 2013
 *      Author: jpm8766
 */

#ifndef PULSESCANNER_H_
#define PULSESCANNER_H_

#include <unistd.h>       /* for sleep() */
#include <stdint.h>       /* for uintptr_t */
#include <hw/inout.h>     /* for in*() and out*() functions */
#include <sys/neutrino.h> /* for ThreadCtl() */
#include <stdio.h>
#include <stdlib.h>
#include "Thread.h"

/* DAQs interrupt vector */
#define DAQ_IRQ     (0x05)

#define KM_TO_MILES (0.621371)
#define SECONDS_PER_HOUR (3600)

enum DistanceUnit {
	KM = 1,
	MILES = 2
};

// Enumeration of the two trip modes for the cyclometer.
enum TripMode {
	TRIP_MANUAL = 0,
	TRIP_AUTO
};

class PulseScanner : public Thread {
public:
	PulseScanner(uintptr_t cmd);
	virtual ~PulseScanner();

	/**
	 * Continuously scans the magnetic sensor.
	 */
	void* run();

	static const struct sigevent * interruptReceived(void *arg, int id);

	float averageSpeed();

	float currentSpeed();

	float distance();

	unsigned int elapsedTime();

	void incrementCircumference();

	int getCircumference();

	void resetTripValues();

	void toggleTripMode();

	void toggleUnits();

	DistanceUnit getUnits();

	uintptr_t getCmdHandle();

	void incrementPulseCount();

	void scannerReset();

	void toggleCalculate();

private:
	//circumference in CM
	int circumference;

	//the trip distance in KM
	double tripDistKM;

	//count of the elapse time in seconds
	unsigned int clockCount;

	//the units being used.
	DistanceUnit units;

	//the number of pulses received via interrupt
	volatile unsigned int pulseCount;

	//interrupt vector ID
	int interruptID;

	//handle to the command port to clear the interrupt
	uintptr_t cmd_handle;

	//the mode; uses AUTO or MANUAL
	int tripMode;

	//the calculate flag
	bool calcFlag;
};

#endif /* PULSESCANNER_H_ */
