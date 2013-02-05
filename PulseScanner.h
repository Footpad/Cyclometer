/*
 * PulseScanner.h
 *
 *  Created on: Feb 5, 2013
 *      Author: jpm8766
 */

#ifndef PULSESCANNER_H_
#define PULSESCANNER_H_

#include <unistd.h>
#include "Thread.h"

#define KM_TO_MILES (0.621371)

#define SECONDS_PER_HOUR (3600)

enum DistanceUnit {
	KM = 1,
	MILES = 2
};

class PulseScanner : public Thread {
public:
	PulseScanner();
	virtual ~PulseScanner();

	void start();

	void stop();

	static void* running(void* args);

	float averageSpeed();

	float currentSpeed();

	void incrementCircumference();

	void resetTripValues();

	void toggleUnits();
private:
	bool killThreads;

	//circumference in CM
	int circumference;

	//the trip distance in KM
	double tripDistKM;

	//count of the elapse time in seconds
	unsigned int clockCount;

	//pulseCount since the last read.
	unsigned int pulseCount;

	//the units being used.
	DistanceUnit units;
};

#endif /* PULSESCANNER_H_ */
