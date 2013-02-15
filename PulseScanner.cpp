/*
 * PulseScanner.cpp
 *
 *  Created on: Feb 5, 2013
 *      Author: jpm8766
 */

#include "PulseScanner.h"

const struct sigevent * PulseScanner::interruptReceived(void *arg, int id) {
	PulseScanner* self = (PulseScanner*) arg;
	self->speedPulseCount++;

	if(self->calcFlag)
		self->distPulseCount++;

	//clear the interrupt.
	out8(self->cmd_handle, (0b00001111));
	return NULL;
}

PulseScanner::PulseScanner(uintptr_t cmd, uintptr_t led) :
	cmd_handle(cmd), ledHandle(led) {
	this->scannerReset();
}

PulseScanner::~PulseScanner() {
}

void PulseScanner::scannerReset() {
	circumference = MAX_WHEEL_CIRCUMFERENCE;
	tripDistKM = 0;
	clockCount = 0;
	speedPulseCount = 0;
	distPulseCount = 0;
	speed = 0;
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

	char even = 0;

	// clear any lingering interrupts.
	out8(cmd_handle, (0b00001111));

	// Timer for calculate functionality.
	timer_t timer;

	// Create a timeout for the push button hold.
	struct sigevent event;
	SIGEV_THREAD_INIT(&event, PulseScanner::calculate, this, NULL);

	// Configure the timeout spec.
	itimerspec timerSpec;
	timerSpec.it_value.tv_sec = MAX_TIME_CALC;
	timerSpec.it_value.tv_nsec = 0;
	timerSpec.it_interval.tv_sec = MAX_TIME_CALC;
	timerSpec.it_interval.tv_nsec = 0;

	// Create and set the timer.
	timer_create(CLOCK_REALTIME, &event, &timer);
	timer_settime(timer, 0, &timerSpec, NULL);

	char ledMask = 0;
	for(int i = 0; i < 3; i++) {
		ledMask |= LED_MASK[i];
	}

	out8(ledHandle, in8(ledHandle) & ~ledMask);

	unsigned int cachedPulse = 0;

	//while running...
	while (!killThread) {

		//so long as we have gotten pulses...keep flashing the LEDs for calculating (if applicable)
		// and the calculating LED (if applicable)
		flashLEDs(even);

		//increment the clock count and distance traveled (since our poll period is half a second)
		if (calcFlag && even == 0) {
			clockCount += 1;
			cachedPulse = distPulseCount;
			distPulseCount = 0;

			tripDistKM += (circumference * cachedPulse * METERS_PER_CM) * KM_PER_METER;
		}

		usleep(PULSE_SCAN_POLL_RATE);
		//periodically clear the interrupt here so it can recover if the frequency changes too quickly
		out8(cmd_handle, (0b00001111));

		even = (even + 1) % 2;
	}

	return NULL;
}

double PulseScanner::averageSpeed() {
	//return the Units/Hour
	return (distance() / ((double)clockCount / (double)SECONDS_PER_HOUR));
}

double PulseScanner::currentSpeed() {
	//set the scaleFactor to either be for KM or to MILES
	double scaleFactor = (units == KM ? 1 : KM_TO_MILES);

	return (speed * scaleFactor);
}

double PulseScanner::distance() {
	//set the scaleFactor to either be for KM or to MILES
	double scaleFactor = (units == KM ? 1 : KM_TO_MILES);

	//return the Units/Hour
	return (tripDistKM * scaleFactor);
}

unsigned int PulseScanner::elapsedTime() {
	return clockCount;
}

void PulseScanner::incrementCircumference() {
	circumference
			= (circumference == MAX_WHEEL_CIRCUMFERENCE ? MIN_WHEEL_CIRCUMFERENCE
					: circumference + 1);
}

int PulseScanner::getCircumference() {
	return circumference;
}

void PulseScanner::resetTripValues() {
	tripDistKM = 0;
	clockCount = 0;
	speedPulseCount = 0;
	distPulseCount = 0;
}

void PulseScanner::toggleUnits() {
	units = (units == KM ? MILES : KM);
	updateUnitsLED();
}

DistanceUnit PulseScanner::getUnits() {
	return units;
}

uintptr_t PulseScanner::getCmdHandle() {
	return cmd_handle;
}

void PulseScanner::toggleTripMode() {
	tripMode = (tripMode == TRIP_AUTO ? TRIP_MANUAL : TRIP_AUTO);
	calcFlag = false;
}

void PulseScanner::toggleCalculate() {
	if (tripMode == TRIP_MANUAL) {
		calcFlag = !calcFlag;
	}
}

void PulseScanner::setWheelLED(bool high) {
	if (high) {
		out8(ledHandle, in8(ledHandle) | LED_MASK[0]);
	} else {
		out8(ledHandle, in8(ledHandle) & ~LED_MASK[0]);
	}
}

void PulseScanner::setCalcLED(bool high) {
	if (tripMode == TRIP_MANUAL) {
		if (calcFlag) {
			if (high) {
				out8(ledHandle, in8(ledHandle) | LED_MASK[1]);
			} else {
				out8(ledHandle, in8(ledHandle) & ~LED_MASK[1]);
			}
		} else {
			out8(ledHandle, in8(ledHandle) & ~LED_MASK[1]);
		}
	} else {
		if (calcFlag) {
			if (high) {
				out8(ledHandle, in8(ledHandle) | LED_MASK[1]);
			} else {
				out8(ledHandle, in8(ledHandle) & ~LED_MASK[1]);
			}
		} else {
			out8(ledHandle, in8(ledHandle) | LED_MASK[1]);
		}
	}
}

void PulseScanner::updateUnitsLED() {
	// LED on for miles, LED off for km.
	if (units == MILES) {
		out8(ledHandle, in8(ledHandle) | LED_MASK[2]);
	} else {
		out8(ledHandle, in8(ledHandle) & ~LED_MASK[2]);
	}
}

void PulseScanner::flashLEDs(int even) {
	if (speedPulseCount > 0) {
		if (tripMode == TRIP_AUTO) {
			calcFlag = true;
		}

		if (even) {
			setWheelLED(true);
		} else {
			setWheelLED(false);
		}
	} else if (speedPulseCount == 0) {
		if (tripMode == TRIP_AUTO) {
			calcFlag = false;
		}
		setWheelLED(false);
	}

	if (even) {
		setCalcLED(true);
	} else {
		setCalcLED(false);
	}
}

void PulseScanner::calculate(sigval arg) {
	PulseScanner* self = (PulseScanner*)arg.sival_ptr;

	unsigned int cachedPulse = self->speedPulseCount;
	self->speedPulseCount = 0;

	double td = ((double)self->circumference * cachedPulse * METERS_PER_CM) * KM_PER_METER;
	double s = ((td) / MAX_TIME_CALC) * (SEC_PER_HOUR);
	self->speed = s;
}
