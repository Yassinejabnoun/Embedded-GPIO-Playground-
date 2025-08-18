/*
 * CPolledTimer.h
 *
 *  Created on: 01.10.2020
 *      Author: mnl
 */

#ifndef CPOLLEDTIMER_H_
#define CPOLLEDTIMER_H_

#include <stdint.h>

/**
 * Ein Zeittaktgeber, bei dem über eine Abfrage ermittelt werden kann,
 * ob der (periodische) Zielzeitpunkt erreicht wurde.
 */
class CPolledTimer {
private:
	/**
	 * Eine Hilfsmethode, die die seit Start des Programms vergangene
	 * Zeit in Millisekunden liefert.
	 */
	int64_t millisSinceStart();
	int32_t m_waitTime;
	int64_t m_targetTime;
public:
	/**
	 * Erzeugt ein neues Objekt mit einer Zielzeit, die sich aus
	 * der aktuellen Zeit plus der angegebenen Wartezeit ergibt.
	 *
	 * @param waitTime Wartezeit in Millisekunden
	 */
	CPolledTimer(int32_t waitTime = 1000);

	/**
	 * Prüft, ob die Zielzeit erreicht wurde. Falls nein, wird
	 * false zurückgegeben. Falls ja, wird eine neue Zielzeit berechnet,
	 * indem der Wert von waitTime zur aktuellen Zielzeit addiert wird.
	 * Anschließend wird true zurückgegeben.
	 *
	 * @return true, wenn die Zielzeit beim Aufruf erreicht war
	 */
	bool timeReached();
	/**
	 * aktualisiert das waittime mit addieren des WaitTime an der TargetTime
	 * @param waitTime Wartezeit in Millisekunden
	 */
	void updateWaitTime(int32_t waitTime);
};

#endif /* CPOLLEDTIMER_H_ */
