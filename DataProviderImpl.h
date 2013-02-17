/*
 * DataProviderImpl.h
 *
 *  Created on: Jan 31, 2013
 *      Author: jpm8766
 */

#ifndef DATAPROVIDERIMPL_H_
#define DATAPROVIDERIMPL_H_

#include "DataProvider.h"

/**
 * This is a fake object used to generate garbage data and to test the Display thread.
 */
class DataProviderImpl: public DataProvider {
public:
	DataProviderImpl(int val);
	virtual ~DataProviderImpl();

	DisplayInfo getData();

private:
	int val;
};

#endif /* DATAPROVIDERIMPL_H_ */
