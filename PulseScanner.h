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
#include <time.h>
#include <sys/siginfo.h>

#include "Thread.h"

//the time to wait between calculations in seconds
#define MAX_TIME_CALC (5)

/* DAQs interrupt vector */
#define DAQ_IRQ     (0x05)

#define KM_TO_MILES (0.621371)
#define SECONDS_PER_HOUR (3600)

//defined as the poll rate in microseconds
#define PULSE_SCAN_POLL_RATE (500000)

#define SEC_PER_HOUR (3600)

#define METERS_PER_CM (.01)
#define KM_PER_METER (.001)

const char LED_MASK[] =
{
	// Wheel LED mask
	(0b10000000),
	// Auto LED mask
	(0b01000000),
	// Units LED mask
	(0b00100000)
};

// The range of wheel circumference values in centimeters.
#define MAX_WHEEL_CIRCUMFERENCE 220
#define MIN_WHEEL_CIRCUMFERENCE 190


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
	PulseScanner(uintptr_t cmd, uintptr_t led);
	virtual ~PulseScanner();

	/**
	 * Continuously scans the magnetic sensor.
	 */
	void* run();

	/**
	 * This is called when an interrupt is received on the DAQ; it increments
	 * the proper fields to update current speed, distance etc. when appropriate.
	 */
	static const struct sigevent * interruptReceived(void *arg, int id);

	/**
	 * Returns the average speed; this is a function of distance()
	 * and elapsedTime().
	 *
	 * @return the average speed attained while calculations were running.
	 */
	double averageSpeed();

	/**
	 * Returns the current speed of the bike; this is based on the number of
	 * pulses over the last MAX_TIME_CALC seconds and the circumference of the wheel.
	 *
	 * @return the current speed of the bike
	 */
	double currentSpeed();

	/**
	 * Returns the distance traveled during the trip (while calculations are on).
	 *
	 * @return Distance traveled.
	 */
	double distance();

	/**
	 * Returns the time elapsed while calculations are on.
	 *
	 * @return the elapsed time
	 */
	unsigned int elapsedTime();

	/**
	 * Increments the current circumference of the wheel.
	 */
	void incrementCircumference();

	/**
	 * Returns either the current circumference or the currently
	 * selected circumference to be set if increment has been called.
	 *
	 * @return the current circumference or the currently selected circumference
	 */
	int getCircumference();

	/**
	 * Saves the currently selected circumference to be used in calculations.
	 */
	void setCircumference();

	/**
	 * Resets all trip information.
	 */
	void resetTripValues();

	/**
	 * toggles the current mode from AUTO to MANUAL calculation modes or
	 * vice versa.
	 */
	void toggleTripMode();

	/**
	 * Toggles the current units from KM to miles or vice versa.
	 */
	void toggleUnits();

	/**
	 * Returns the units currently in use.
	 */
	DistanceUnit getUnits();

	/**
	 * Resets all information on the scanner including circumference, units
	 * and speed.
	 */
	void scannerReset();

	/**
	 * Toggles the calculate flag for MANUAL calculation mode.
	 */
	void toggleCalculate();

private:
	/**
	 * This method is called at 1 second intervals by a timer to calculate
	 * the current speed and accumulate time/distance when calculations are on.
	 */
	static void calculate(sigval arg);

	/**
	 * Sets the wheel LED on or off according to input
	 *
	 * @param high - true if the LED should be turned on.
	 */
	void setWheelLED(bool high);

	/**
	 * Sets the calculate LED either high, low or the bool value
	 * depending on the current calculating mode of the scanner.
	 *
	 * @param high if the LED should be turned on.
	 */
	void setCalcLED(bool high);

	/**
	 * Sets the units in use LED based on the current value of the units variable
	 */
	void updateUnitsLED();

	/**
	 * Flashes the proper LEDs based on even. Even occurs every other cycle of a .5 second wait time.
	 * This function also sets the calcFlag when in AUTO mode if pulses are detected or not.
	 *
	 * @param even - 0 if even, 1 otherwise
	 */
	void flashLEDs(int even);

	//circumference in CM (used for calculations)
	int calcCircumference;

	//circumference in CM (used for setting)
	int circumference;

	//boolean to say whether we are setting the circumference or not
	bool settingCir;

	//the trip distance in KM
	double tripDistKM;

	//count of the elapse time in seconds
	unsigned int clockCount;

	//the units being used.
	DistanceUnit units;

	//the array of speedPulses we are looking at.
	volatile unsigned int speedPulses[MAX_TIME_CALC];

	//the index in the array to be writing to
	volatile int speedPulseIndex;

	//the number of pulses received via interrupt used to calculate trip distance (1 second when calculating)
	volatile unsigned int distPulseCount;

	//interrupt vector ID
	int interruptID;

	//handle to the command port to clear the interrupt
	uintptr_t cmd_handle;

	//the mode; uses AUTO or MANUAL
	int tripMode;

	//the calculate flag
	bool calcFlag;

	//the current speed as based on the pulses received over the last time interval
	double speed;

	//LED handle
	uintptr_t ledHandle;
};

#endif /* PULSESCANNER_H_ */
