/*
 * PulseScanner.cpp
 *
 *  Created on: Feb 5, 2013
 *      Author: jpm8766
 */

#include "PulseScanner.h"

const struct sigevent * PulseScanner::interruptReceived(void *arg, int id) {
	PulseScanner* self = (PulseScanner*) arg;

	//update the value at the current position in the buffer
	self->speedPulses[self->speedPulseIndex]++;

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
	calcCircumference = MAX_WHEEL_CIRCUMFERENCE;
	circumference = MAX_WHEEL_CIRCUMFERENCE;
	tripDistKM = 0;
	clockCount = 0;
	speedPulseIndex = 0;
	distPulseCount = 0;
	speed = 0;
	units = KM;
	tripMode = TRIP_MANUAL;
	calcFlag = false;
	settingCir = false;

	for(int i = 0; i < MAX_TIME_CALC; i++) {
		speedPulses[i] = 0;
	}
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
	timer_t oneSecTimer;

	// Create a timeout for the push button hold.
	struct sigevent event;
	SIGEV_THREAD_INIT(&event, PulseScanner::calculate, this, NULL);

	// Configure the timeout spec.
	itimerspec oneSecondTimerSpec;
	oneSecondTimerSpec.it_value.tv_sec = 1;
	oneSecondTimerSpec.it_value.tv_nsec = 0;
	oneSecondTimerSpec.it_interval.tv_sec = 1;
	oneSecondTimerSpec.it_interval.tv_nsec = 0;

	// Create and set the timer.
	timer_create(CLOCK_REALTIME, &event, &oneSecTimer);
	timer_settime(oneSecTimer, 0, &oneSecondTimerSpec, NULL);

	char ledMask = 0;
	for(int i = 0; i < 3; i++) {
		ledMask |= LED_MASK[i];
	}

	out8(ledHandle, in8(ledHandle) & ~ledMask);

	//while running...
	while (!killThread) {

		//so long as we have gotten pulses...keep flashing the LEDs for calculating (if applicable)
		// and the calculating LED (if applicable)
		flashLEDs(even);

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
	settingCir = true;
	circumference
			= (circumference == MAX_WHEEL_CIRCUMFERENCE ? MIN_WHEEL_CIRCUMFERENCE
					: circumference + 1);
}

void PulseScanner::setCircumference() {
	settingCir = false;
	calcCircumference = circumference;
}

int PulseScanner::getCircumference() {
	if(settingCir) {
		return circumference;
	}
	return calcCircumference;
}

void PulseScanner::resetTripValues() {
	tripDistKM = 0;
	clockCount = 0;
	distPulseCount = 0;
}

void PulseScanner::toggleUnits() {
	units = (units == KM ? MILES : KM);
	updateUnitsLED();
}

DistanceUnit PulseScanner::getUnits() {
	return units;
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
	int cachedPulse = 0;
	for(int i = 0; i < MAX_TIME_CALC; i++) {
		cachedPulse += speedPulses[i];
	}

	if (cachedPulse > 0) {
		if (tripMode == TRIP_AUTO) {
			calcFlag = true;
		}

		if (even) {
			setWheelLED(true);
		} else {
			setWheelLED(false);
		}
	} else if (cachedPulse == 0) {
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

	//iterate over the available pulses and accumulate the total.
	unsigned int cachedPulse = 0;
	for(int i = 0; i < MAX_TIME_CALC; i++) {
		cachedPulse += self->speedPulses[i];
	}
	//move to the next index and reset it (reset the oldest count in the array
	self->speedPulseIndex = (self->speedPulseIndex + 1) % MAX_TIME_CALC;
	self->speedPulses[self->speedPulseIndex] = 0;

	//calculate the distance travelled in that time and the speed based on that distance.
	double td = ((double)self->calcCircumference * cachedPulse * METERS_PER_CM) * KM_PER_METER;
	double s = ((td) / MAX_TIME_CALC) * (SEC_PER_HOUR);

	self->speed = s;

	if (self->calcFlag) {
		self->clockCount += 1;
		cachedPulse = self->distPulseCount;
		self->distPulseCount = 0;

		self->tripDistKM += (self->calcCircumference * cachedPulse * METERS_PER_CM) * KM_PER_METER;
	}
}
