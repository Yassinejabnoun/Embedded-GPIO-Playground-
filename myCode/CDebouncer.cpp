/*
 * CDebouncer.cpp
 *
 *  Created on: 30.09.2020
 *      Author: mnl
 */

#include "CDebouncer.h"

CDebouncer::CDebouncer(BusIn *busIn, int waitTime) {
	m_busIn = busIn;
	m_waitTime = waitTime;
	m_previousInputValue = 0;
	m_lastChangeAt = -1;
}

int64_t CDebouncer::millisSinceStart() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(
			HighResClock::now().time_since_epoch()).count();
}

int CDebouncer::read() {
	if (m_lastChangeAt >= 0) {
		if (millisSinceStart() < m_lastChangeAt + m_waitTime) {
			return m_previousInputValue;
		}
		m_lastChangeAt = -1;
	}
	int newInputValue = m_busIn->read();
	if (newInputValue != m_previousInputValue) {
		m_lastChangeAt = millisSinceStart();
		m_previousInputValue = newInputValue;
	}
	return newInputValue;
}

CDebouncer::operator int() {
	return read();
}
