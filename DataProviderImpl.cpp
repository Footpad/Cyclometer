/*
 * DataProviderImpl.cpp
 *
 *  Created on: Jan 31, 2013
 *      Author: jpm8766
 */

#include "DataProviderImpl.h"

DataProviderImpl::DataProviderImpl(int val) {
	this->val = val;
}

DataProviderImpl::~DataProviderImpl() {}

/**
 * generate some garbage to display
 */
DisplayInfo DataProviderImpl::getData() {
	DisplayInfo d;
	for(int i = 0; i < NUM_DIGITS; i++) {
		d.val[i] = i*val;
		d.dp[i] = (d.val[i] % 2 == 0);
	}

	return d;
}
