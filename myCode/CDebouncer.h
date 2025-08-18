/*
 * CDebouncer.h
 *
 *  Created on: 30.09.2020
 *      Author: mnl
 */

#ifndef CDEBOUNCER_H_
#define CDEBOUNCER_H_

#include "mbed.h"

/**
 * A class that debounces the input signals read from an object of
 * type BusIn. Debouncing is implemented by ignoring any changes of
 * input values for a given time after a change has been detected.
 */
class CDebouncer {
private:
	/**
	 * A helper method that returns the number of milliseconds since
	 * the start of the program.
	 */
	int64_t millisSinceStart();
	BusIn* m_busIn;
	int m_waitTime;
	int m_previousInputValue;
	int64_t m_lastChangeAt;

public:
	/**
	 * Create an instance that decorates the given object of type BusIn
	 * and provides debounced input values.
	 *
	 * @param busIn the underlying BusIn object
	 * @param waitTime the time (in milliseconds) to wait after a
	 * change of input values before reading new input values
	 */
	CDebouncer(BusIn* busIn, int waitTime = 20);

    /**
     * Read the value of the input bus
     *
     * @returns
     *   an integer with each bit corresponding to the value read
     *   from the associated DigitalIn pin
     */
    int read();

    /**
     * A shorthand for read().
     */
    operator int();
};

#endif /* CDEBOUNCER_H_ */
