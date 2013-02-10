/*
 * DataProvider.h
 *
 *  Created on: Jan 31, 2013
 *      Author: jpm8766
 */

#ifndef DATAPROVIDER_H_
#define DATAPROVIDER_H_

#define NUM_DIGITS (4)

// Corresponds to the CATHODE_TABLE entry for a blank digit.
#define BLANK_DIGIT (10)

/*
 * typedef for a struct. DisplayInfo contains an array of values and bools.
 * The index of each (val and dp) corresponds to a single digit on the seven
 * segment display. val should be an array of ints between 0-9 which can
 * be validly looked up in the CATHODE_TABLE. dp is true iff the decimal point
 * for that digit should be on.
 */
typedef struct {
	int val[NUM_DIGITS];
	bool dp[NUM_DIGITS];
} DisplayInfo;

/**
 * This class defines a common interface for the display to obtain DisplayInfo
 * from. It also contains helper methods for converting floats and ints to
 * properly formatted DisplayInfo structs.
 */
class DataProvider {
public:

	/**
	 * Return a DisplayInfo struct which can be displayed on the 4 digit 7 segment displays.
	 *
	 * @return A DisplayInfo object which can be displayed on the 7 segment displays.
	 */
	virtual DisplayInfo getData() = 0;
};

#endif /* DATAPROVIDER_H_ */
