#include "mbed.h"
#include"CDebouncer.h"
#include "breadboard.h"
#include "CPolledTimer.h"
#include "stdint.h"
#include "iostream"
using namespace std;

// anlegen der globalen Objekte, die die Peripheriekomponenten
// repräsentieren,

//Modellierung des Leds

BusOut leds(BB_LED_0, BB_LED_1, BB_LED_2, BB_LED_3, BB_LED_4, BB_LED_5,
BB_LED_6, BB_LED_7);

//Modellierung des Taster

BusIn keys(BB_BTN_0, BB_BTN_1, BB_BTN_2, BB_BTN_3, BB_BTN_4, BB_BTN_5, BB_BTN_6,
BB_BTN_7);


/**
 * die 8 Leds werden jedes 1s an und wieder ausgeschaltet
 */
void task1() {
	while (true) {
		leds = 0b11111111;
		thread_sleep_for(1000); // system wird fuer 1s puasiert
		leds = 0b00000000;
		thread_sleep_for(1000);
	}
} //end der Task1 ;


/**
 * anschalten eines leds beim drueken des taster drunter
 */
void task2(){
	while(true){
		leds = keys; // leds bekommt die value von Keys
	}
}//end der task 2


/**
 * ermoeglicht das toggeln von Leds durch druecken des Tasters drunter
 * An-/Ausschalten der LEDs beim drueken der taster drunter
 */
void task3(){
	uint8_t previousKeyState = keys.read();
	while(true){
		uint8_t newKeyState = keys.read();
		uint8_t bitmuster = (previousKeyState^newKeyState)& ~previousKeyState;
		leds = leds ^ bitmuster ;
		newKeyState = previousKeyState ;
	}
}//ende der task 3


/**
 * ermoeglicht das toggeln(An-/Ausschalten der LEDs) von Leds
 * durch debouncedKeys.
 * nach dem druecken einer Taster, wird 200ms gewarte bevor das lesen
 * der keys Eingang (200ms gewartet bevor das an/ausschalten des leds)
 */
void task4(){
	CDebouncer debouncedKeys(&keys,200); //objekt von type CDebounncer
	uint8_t previousKeyState = debouncedKeys.read();
	while(true){
		uint8_t newKeyState = debouncedKeys.read();
		uint8_t bitmuster = (previousKeyState^newKeyState)& ~previousKeyState;
		leds = leds ^ bitmuster ;
		newKeyState = previousKeyState ;
	}
}//ende der task 4


/**
 * ermoeglicht ein einfaches lauflicht
 * die leds werden nacheinander angeschltet mit ein zeitraum dazwischen von 1s
 */
void task5(){
	leds = 0b00000001;
	while(true){
		thread_sleep_for(1000); //pausiert das system für 1s
		leds = leds << 1; //nächste bit ist an
		if(leds == 0b00000000){ //wenn alle bits gleich 0
			leds = 0b00000001; //wird die erste led bit an
		}
	}
} // ende der task5


/**
 * den Task ist aehnlich wie Task 5, allerdings kann in die zeitspanne dt = 2s
 * ein beliebiges verhalten getan werden
 * in unserem fall : anschalten des Leds mit drücken des Tastern drunter
 */
void task6() {
	int64_t waitTime = 2000; // zeitspanne des Lauflichts
	int8_t bitmuster = 0b00000001; //bitmuster

	//targetTime = aktuelTime + waitTime
	int64_t targetTime = std::chrono::duration_cast <
			std::chrono::milliseconds> (HighResClock::
			now().time_since_epoch()).count() + waitTime ;
	while (true) {
		leds = bitmuster ;
		int64_t aktualTime = std::chrono::duration_cast <
				std::chrono::milliseconds> (HighResClock::
						now().time_since_epoch()).count(); //aktuelles Zeit

		//wenn der Aktuel zeit < als die Target Time kann ein belibiges
		//gefuehrt werden
		if (aktualTime < targetTime) {
			leds.write(keys);
		}

		//wenn der Aktuel zeit = oder > target time lauft das lauflicht
	    else {
			bitmuster = bitmuster << 1;
			if (bitmuster == 0b00000000) {
				bitmuster = 0b00000001;
			}

			//targetTime um waitTime erhoeht
			targetTime += waitTime ;
		}
	}
} //ende der Task6


/**
 * Im task7 , durch die classe CPolledTimer bestimmen wir die frquenz
 * des blinken des leds
 * die 3 definierte objekte der classe CPolledTimer geben uns jeweils
 *  die waitTime für blibken , mit der methode timeReached bestimmen wir ob
 *  der zielpunkt für nächste blick erreicht ist (ob der waitTime vorbei ist)
 * in den fall
 * blinkt led3 4mal/s
 * blinkt led2 3mal/s
 * blinkt led1 2mal/s
 */
void task7() {
	CPolledTimer twoHz(500); //objekt twoHz von type CPolledTimer
	CPolledTimer threeHz(333); //objekt threeHz von type CPolledTimer
	CPolledTimer fourHz(250); //objekt fourHz von type CPolledTimer
	while (true) {

		//wenn 500ms erreicht wird , blinkt led 1
		if (twoHz.timeReached()) {
			leds = leds ^ (1 << 0);
		}

		//wenn 333ms erreicht wird , blinkt led 2
		if (threeHz.timeReached()) {
			leds = leds ^ (1 << 1);
		}

		//wenn 250ms erreicht wird , blinkt led 3
		if (fourHz.timeReached()) {
			leds = leds ^ (1 << 2);
		}
	}
}


/**
 * im task 8 wird ein lauflicht geschaft aehnlich wie im task 6
 * mit einer Zeitspanne von 2s.
 * statt die implementierung von der zeit funktionalitaet
 * habne wir ein Objekt "waitTime" der Klasse CPolledTimer verwendet.
 */
void task8(){
	CPolledTimer waitTime(1000); //objekt waitTime von type CPolledTimer
	int8_t bitmuster = 0b00000001;
	while(true){
		leds = bitmuster ;

		//ist waitTime erreicht lauft das lauflicht
		if(waitTime.timeReached()){
			bitmuster = bitmuster << 1;
			if(bitmuster == 0b00000000)
				bitmuster = 0b00000001;
		}

		//waittime nicht erreicht wird ein beliebiges aktion durchgefuehrt
		else {

			//das belibiges aktion ist in der fall einschalten
			//des Leds mit drueken des taster drunter
			leds = keys;
		}
	}
}//ende der Task8


/**
 * Implementierung der Funktion task9
 * diese Funktion realisiert die Anwendung „konfigurierbares Lauflicht“ realisiert.
 * das Verhalten eines Lauflichts kann über den Wert einer Variablen gesteuert werden.
 * diese Variable kann die Werte -7 bis +7 annehmmen.
 * ein negativer Wert bedeutet, dass das Lauflicht von rechts nach links läuft,
 * und ein positiver Wert bedeutet, dass Lauflicht von links nach rechts läuft.
 * der absolute Wert der Variablen bestimmt die Zeit zwischen
 * zwei Zustandswechseln nach der Formel „absoluter Wert * 250 ms“
 * und damit bestimmt die Geschwindigkeit des Lauflichts.

 * die LED-Gruppe (Lauflicht) stellt das Lauflicht dar.
 * Die Gruppe (Geschwindigkeit/Richung) stellt den Wert der Steuervariablen
 * als vorzeichenbehaftete 4-bit Binärzahl (Zweierkomplement) dar.
 * Mit den Tastern der Gruppe (Direkteinstellung) können
 * die darüber liegenden LEDs getoggelt werden.
 *  Die Taste (+) erhöht den Wert der Steuervariablen um 1,
 *  und die Taste (-) vermindert den um 1.
 * wenn die Variable bereits den Minimal- oder Maximalwert hat,
 * dann hat ein weiterer Tastendruck keine Wirkung.
 *  Die Taste (↔) wechselt die Laufrichtung, ohne die Geschwindigkeit zu verändern.
 */
void task9() {
	CDebouncer keys_Debouncer(&keys, 100);

    // Steuervariable, durch die sowohl die Richtung als auch die
	// Geschwindigkeit des Lauflichtes geändert wird.
	int8_t Controler = 0;

	// Timer für das Lauflicht, seine Zeit wird durch
	// die Steuervariable aktualiesiert.
	CPolledTimer WaitTime(250);

	// Wartezeit von 150 mS, damit den Steuervariable beim Tastendruck
	// nicht zu schnell geändert wird.
	CPolledTimer WaitTime_Boutton(150);

	// Hilfsobjekte für Implementierung des Lauflichtes
	int Left_to_Right = 0;
	int Right_to_Left = 3;
	uint8_t ChasingLight=0;

    // aktueller Zusatnd der Taster
	uint8_t previousKeyStates;

	// Durch dieses Objekt, wird „Produktionsmodus“ akktiviert oder deaktiviert
    bool Produktionsmodus=0;

    // Timer zur Realiesierung einer Wartezeit beim Wechseln des Modus
    CPolledTimer ChangeModeTimer(3000);

    // Dieses Objekt ist dafür, um beim Drücken des 8.Tasters den Timer
    // "ChangeModeTimer" nur einmal zu aktualiesieren.
    bool uebergand=1;

    // Hilfsobjekte zur Implementierung des Lauflichtes im Produktionsmodus
    	int Left_to_Right_PM = 0;
    	int Right_to_Left_PM= 7;

	// Wiederholt ausgeführte Anweisungen
	while (true) {
		// Wenn den 8.Taster gedrückt wird
		if((keys_Debouncer.read()&0x80) && (uebergand))
		{
			// Wartezeit von 3 Sekunden wird erstellt
			ChangeModeTimer.updateWaitTime(3000);

			// Aktualiesierung der Wartezeit wird gesperrt
			uebergand=0;
		}

		// Die 3 Sekunden sind vorbei, und den 8.Taster ist immer noch betätigt
		if ((ChangeModeTimer.timeReached())&& (keys_Debouncer.read()==0x80))
		{
			// Modus wird geändert
			Produktionsmodus=!Produktionsmodus;

			// Aktualiesierung der Wartezeit wird entsperrt.
			uebergand=1;
		}

		// „Einstellungsmodus“ ist aktiviert
	 if(!Produktionsmodus)
		{
		// aktueller Zustand der 4 rechten Taster
		uint8_t newKeyStates = keys_Debouncer.read() & 0x0f ;

		// Bitmaske zur Dierekteinstellung von der Steuervariable
		int8_t keysPushed = (newKeyStates & ~previousKeyStates) & 0x0f;

		// Steuervariable wird durch den Tasterwert umgeschaltet
		// (dierekte Einstellung)
			Controler = Controler ^ keysPushed;

		// Dem alten zustand der Taster wird den neuen Zustand zugewiessen
		previousKeyStates = newKeyStates;

	   // Alle linken 4 Bits werden an das vierte Bit der Steuervariable  von
	   // rechts angeglichen, da nur vier Bit in einem int8 dargestellt werden
			if (Controler & 0x8)
			{
				Controler = (0xf0 | (Controler & 0x0f));
			}
			else
			{
				Controler = Controler & 0xf;
			}

		// Es wird 150ms gewartet, bevor die Steuervariable geändert wird.
		if (WaitTime_Boutton.timeReached())
		{
			// "+" Taster wird gedrückt
			if (keys_Debouncer & 0x10)
			{
				// Die Steuervariable wird um eins erhöht
				++Controler;

				// Steuervariable darf nicht größer 7 sein
				if (Controler > 7)
				{
					Controler = 7;
				}
			}

			// "-" Taster wird gedrückt
			if (keys_Debouncer & 0x20)
			{
				// Die Steuervariable wird um eins erniedrigt
				--Controler;
			}

			// Die Steuervariable darf nicht kleiner -7 sein
			if (Controler < -7)
			{
				Controler = -7;
			}

		    // "<->" Toggle Taster wird gedrückt
			if (keys_Debouncer & 0x40)
			{
			// Die richtung des Lauflichtes wird geändert
				Controler=(Controler +1 )* -1;
			}
			     }

		// Implementierung des Lauflichtes:
		if (WaitTime.timeReached())
		{
			// Richtung des Lauflichts ist von Links nach Rechts,
			// wenn der wert des Steuervariable größer null ist.
			if (Controler > 0) {
				ChasingLight = 1 << (7 - Left_to_Right);
				Left_to_Right++;

			// wenn die 4.Led eingeschaltet wurde, wird der Vorgang wiederholt
				if (Left_to_Right == 4) {
					Left_to_Right = 0;
				}
			}

			// Richtung des Lauflichts ist von Rechts nach Links,
			// wenn wert des Steuervariable kleiner null ist.
			if (Controler <0)
			{
				ChasingLight = 1 << (7 - Right_to_Left);
				Right_to_Left--;

			// wenn die 4.Led eingeschaltet wurde, wird der Vorgang wiederholt
				if (Right_to_Left == -1) {
					Right_to_Left = 3;
				}
			}
		}

		// Bei jedem Tastendruck wird die Geschwindigkeit des Lauflichtes
		// aktualisiert.
		if(keys_Debouncer.read()& 0xff)
		{
			WaitTime.updateWaitTime(250 * abs(Controler));
		}

		// leds lechten, solange der Steuervariable ungleich null ist
		if(Controler!=0)
		{
		// Werte von der Steuervariable und dem Lauflicht Werden
		// auf die Leds dargestellt.
		leds = (ChasingLight & 0xf0 ) | (Controler & 0x0f );
	     }
		else
		{
		// Wenn Steuervariable null ist, sind die Leds ausgeschaltet.
			leds=0;
		}
		}

		// „Produktionsmodus“ ist aktiviert
		else if (Produktionsmodus) {
			// Richtung des Lauflichts ist von Links nach Rechts,
			// wenn der wert des Steuervariable größer null ist.
			if (Controler > 0) {
				if (WaitTime.timeReached()) {
					// Leds werden nacheinander geschaltet
					leds = 1 << (7 - Left_to_Right_PM);
					Left_to_Right_PM++;

					// nachdem die letzte Led eingeschaltet wurde,
					// wird der Vorgang wiederholt.
					if (Left_to_Right_PM == 8) {
						Left_to_Right_PM = 0;
					}
				}
			}

			// Richtung des Lauflichts ist von Rechts nach Links,
			// wenn der wert des Steuervariable kleiner null ist.
			else if (Controler < 0) {
				if (WaitTime.timeReached()) {
					leds = 1 << (7 - Right_to_Left_PM);
					Right_to_Left_PM--;

					// wenn die letzte Led eingeschaltet wurde, wird
					// der Vorgang wiederholt
					if (Right_to_Left_PM == -1) {
						Right_to_Left_PM = 7;
					}
				}
			}
		}
	}
} // ende der Task9



int main() {

	keys.mode(PullDown);

	//task1();

	//task2();

	//task3();

	//task4();

    //task5();

	//task6();

	//task7();

	//task8();

	task9();











}

