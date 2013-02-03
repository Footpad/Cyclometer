/*
 * Common.h
 *
 *  Created on: Jan 31, 2013
 *      Author: dam7633
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <cassert>

// Abstracting the type of system events.
typedef int Event;

// Function pointer for transition actions.
typedef void (*Action)(void);

#endif /* COMMON_H_ */
