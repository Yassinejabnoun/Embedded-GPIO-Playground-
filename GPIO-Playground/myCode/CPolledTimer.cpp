/*
 * CPolledTimer.cpp
 *
 *  Created on: 01.10.2020
 *      Author: mnl
 */

#include "mbed.h"
#include "CPolledTimer.h"

CPolledTimer::CPolledTimer(int32_t waitTime) {
	m_waitTime = waitTime ;
	m_targetTime = waitTime + millisSinceStart() ;
}

int64_t CPolledTimer::millisSinceStart() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(
			HighResClock::now().time_since_epoch()).count();
}
/**
	 * Prüft, ob die Zielzeit erreicht wurde. Falls nein, wird
	 * false zurückgegeben. Falls ja, wird eine neue Zielzeit berechnet,
	 * indem der Wert von waitTime zur aktuellen Zielzeit addiert wird.
	 * Anschließend wird true zurückgegeben.
	 *
	 * @return true, wenn die Zielzeit beim Aufruf erreicht war
	 */
bool CPolledTimer::timeReached() {
	if( m_targetTime <= millisSinceStart()){
		m_targetTime+=m_waitTime ;
		return true ;}
		else{
			return false ;
	}
}
void CPolledTimer::updateWaitTime(int32_t waitTime){
	m_waitTime = waitTime;
	m_targetTime = m_waitTime + millisSinceStart();
}
