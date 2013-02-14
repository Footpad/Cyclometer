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

	unsigned int cachedPulse = 0;
	char even = 0;
	char fakeTimer = 0;

	// clear any lingering interrupts.
	out8(cmd_handle, (0b00001111));

	//while running...
	while (!killThread) {
		if (fakeTimer == MAX_FAKE_TIMEOUT) {

			if (pulseCount == 0) {
				setWheelLED(false);
				if(tripMode == TRIP_AUTO) {
					calcFlag = false;
				}
			} else if (pulseCount > 0) {
				if (even) {
					setWheelLED(true);
				} else {
					setWheelLED(false);
				}
			}
			cachedPulse = pulseCount;
			pulseCount = 0;
			fakeTimer = 0;

			//update the statistics here...
			if(calcFlag) {
				printf("CALCULATING COW: %d\n", &cachedPulse);
			}
		} else {
			if (pulseCount > 0) {
				if(tripMode == TRIP_AUTO) {
					calcFlag = true;
				}

				if (even) {
					setWheelLED(true);
				} else {
					setWheelLED(false);
				}
			} else if(pulseCount == 0) {
				if(tripMode == TRIP_AUTO) {
					calcFlag = false;
				}

				setWheelLED(false);
			}

			fakeTimer++;
		}
		cachedPulse = pulseCount;

		if(even) {
			setCalcLED(true);
		} else {
			setCalcLED(false);
		}

		usleep(PULSE_SCAN_POLL_RATE);
		//periodically clear the interrupt here so it can recover if the frequency changes too quickly
		out8(cmd_handle, (0b00001111));

		even = (even + 1) % 2;
	}

	return NULL;
}

//TODO: this calculation may need to be externalized and only done every so often and stored as an attribute
//      so that the display doesnt consume a metric ton of computation resources constantly fetching this.
double PulseScanner::averageSpeed() {

	//return the Units/Hour
	return (distance() / (clockCount / SECONDS_PER_HOUR));
}

//TODO: implement this?
double PulseScanner::currentSpeed() {
	return 0.0f;
}

// TODO: Implement this.
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
	updateUnitsLED();
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
	if(tripMode == TRIP_MANUAL) {
		if(calcFlag) {
			if (high) {
				out8(ledHandle, in8(ledHandle) | LED_MASK[1]);
			} else {
				out8(ledHandle, in8(ledHandle) & ~LED_MASK[1]);
			}
		} else {
			out8(ledHandle, in8(ledHandle) & ~LED_MASK[1]);
		}
	} else {
		if(calcFlag) {
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
