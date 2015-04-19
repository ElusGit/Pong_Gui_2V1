/*
 * Ballfunktionen.c
 *
 *  Created on: 08.03.2015
 *      Author: Eliott Kupferschmied
 */
/**
*****************************************************************************
**	Projekt Pong
**	BTE 5052	FS2015
*****************************************************************************
**
**	File        : Ballfunktionen.c
**
**	Funktion   	: Unterfunktionen der Ballpositionsberechnung. Hauptfunktion für die Ballpositionsberechnung
**
**	Parameter	: Initialisationswerte...
**
** 	Author		: kupfe1/alles1
**
**	Version		: 1V05
**
**	History		: .....
**
**	Pendenzen	: Levelvariationen
**
**	Bugs		: Abprallverhalten optimieren
**
**	Tests		: Test von 1V00 am 12.03.2015
**				  Test von 1V01 am 15.03.2015
**				  Test von 1V02 am 16.03.2015
**				  Test von 1V03 am 22.03.2015
**				  Test von 1V04 am 01.04.2015
**				  Test von 1V05 am 05.04.2015
**
******************************************************************************/


/* imports */
#include "error.h"
#include "window.h"
#include "communication.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "Spielsteuerung.h"
#include "Header.h"
#include <time.h>


//Funktionsdeklarationen der Unterfunktionen
static void UntereObereWand(Ball *SpielballPtr);
static void Schlaeger1Abprall(Ball *SpielballPtr, Schlaeger *Schlaeger1Ptr);
static void Schlaeger2Abprall(Ball *SpielballPtr, Schlaeger *Schlaeger2Ptr);
static void HindernisAbprall(Ball *SpielballPtr);

/**
*****************************************************************************
**	Projekt Pong
**	BTE 5052	FS2015
*****************************************************************************
**
**	Funktionsname   	: UntereObereWand
**
**	Funktion   			: Verhalten des Balles steuern, wenn er auf eine Wand auftrifft.
**
**	Rückgabe			: Keine
**
**	Input				: Zeiger auf den Spielball
**
**	Output				: Es wird direkt an die Adresse des Spielballes geschrieben
**
** 	Author				: kupfe1/alles1

**
******************************************************************************/

static void UntereObereWand(Ball *SpielballPtr){

		//Neuer Geschwindigkeitsvektor, Vorzeichen ändern der Y Komponente
		SpielballPtr->vy=-1*(SpielballPtr->vy);

		//Bewegungsgleichung neu aufsetzen
		SpielballPtr->xnull=SpielballPtr->xpos;							//Neuer Nullvektor Zuweisen
		SpielballPtr->ynull=SpielballPtr->ypos;
		SpielballPtr->Zeit=1;											//Zeit zurücksetzen
}

/**
*****************************************************************************
**	Projekt Pong
**	BTE 5052	FS2015
*****************************************************************************
**
**	Funktionsname   	: UntereObereWand
**
**	Funktion   			: Verhalten des Balles steuern, wenn er auf eine Wand auftrifft.
**
**	Rückgabe			: Keine
**
**	Input				: Zeiger auf den Spielball
**
**	Output				: Es wird direkt an die Adresse des Spielballes geschrieben
**
** 	Author				: kupfe1/alles1
**
**	Tests				: Test von 1V02 am 13.03.2015
**
******************************************************************************/

static void HindernisAbprall(Ball *SpielballPtr){

		//Neuer Geschwindigkeitsvektor, Vorzeichen ändern der Y Komponente
		SpielballPtr->vx=-1*(SpielballPtr->vx);

		//Bewegungsgleichung neu aufsetzen
		SpielballPtr->xnull=SpielballPtr->xpos;							//Neuer Nullvektor Zuweisen
		SpielballPtr->ynull=SpielballPtr->ypos;
		SpielballPtr->Zeit=1;											//Zeit zurücksetzen
}

/**
*****************************************************************************
**	Projekt Pong
**	BTE 5052	FS2015
*****************************************************************************
**
**	Funktionsname   	: Schlaeger1
**
**	Funktion   			: Verhalten des Balles steuern, wenn er auf den linken Schläger auftrifft.
**
**	Rückgabe			: Keine
**
**	Input				: Zeiger auf den Spielball, Zeiger auf den Schläger 1
**
**	Output				: Es wird direkt an die Adresse des Spielballes geschrieben
**
** 	Author				: kupfe1/alles1
**
**	Tests				: Test von 1V02 am 13.03.2015
**
******************************************************************************/

static void Schlaeger1Abprall(Ball *SpielballPtr, Schlaeger *Schlaeger1Ptr){

	//Ist der Ball innerhalb der Zone A des Schlägers
	if(SpielballPtr->ypos>=Schlaeger1Ptr->ypos && SpielballPtr->ypos<Schlaeger1Ptr->yzonea){
		//Abprallverhalten durch Änderung des Geschwindigkeitsvektores
		SpielballPtr->vx=abs(SpielballPtr->vx-1);					//X Komponente invertieren (SpielballPtr->vx-1)
		SpielballPtr->vy=-1*((abs(SpielballPtr->vy)+2));				//Nach oben ablenken und Geschwindigkeit erhöhen (abs(SpielballPtr->vy)+2)
	}

	//Ist der Ball innerhalb der Zone B des Schlägers
	if(SpielballPtr->ypos>=Schlaeger1Ptr->yzonea && SpielballPtr->ypos<Schlaeger1Ptr->yzoneb){
		//Abprallverhalten durch Änderung des Geschwindigkeitsvektores
		SpielballPtr->vx=(abs(SpielballPtr->vx));					//X Komponente invertieren und Geschwindigkeit erhöhen
		SpielballPtr->vy=-1;										//Ablenken mit Y-Komponente = -1, zwingender Abprall leicht nach oben
	}

	//Ist der Ball innerhalb der Zone C des Schlägers
	if(SpielballPtr->ypos>=Schlaeger1Ptr->yzoneb && SpielballPtr->ypos<Schlaeger1Ptr->yzonec){
		//Abprallverhalten durch Änderung des Geschwindigkeitsvektores
		SpielballPtr->vx=(abs(SpielballPtr->vx));					//X Komponente invertieren und Geschwindigkeit erhöhen
		SpielballPtr->vy=1;											//Ablenken mit Y-Komponente = 1, zwingender Abprall leicht nach unten
	}

	//Ist der Ball innerhalb der Zone D des Schlägers
	if(SpielballPtr->ypos>=Schlaeger1Ptr->yzonec && SpielballPtr->ypos<Schlaeger1Ptr->yzoned){
		//Abprallverhalten durch Änderung des Geschwindigkeitsvektores
		SpielballPtr->vx=abs((SpielballPtr->vx-1));					//X Komponente invertieren(SpielballPtr->vx-1)
		SpielballPtr->vy=abs(SpielballPtr->vy)+2;						//Nach unten ablenken und Geschwindigkeit erhöhenabs((SpielballPtr->vy)+2)
	}


	//Bewegungsgleichung neu aufsetzen
	SpielballPtr->xnull=SpielballPtr->xpos;							//Neuer Nullvektor zuweisen
	SpielballPtr->ynull=SpielballPtr->ypos;
	SpielballPtr->Zeit=1;											//Zeitkomponente rücksetzen										//Zeit zurücksetzen
}

/**
*****************************************************************************
**	Projekt Pong
**	BTE 5052	FS2015
*****************************************************************************
**
**	Funktionsname   	: Schlaeger2
**
**	Funktion   			: Verhalten des Balles steuern, wenn er auf den rechten Schläger auftrifft.
**
**	Rückgabe			: Keine
**
**	Input				: Zeiger auf den Spielball, Zeiger auf den Schläger 2
**
**	Output				: Es wird direkt an die Adresse des Spielballes geschrieben
**
** 	Author				: kupfe1/alles1
**
**	Tests				: Test von 1V02 am 13.03.2015
**
******************************************************************************/

static void Schlaeger2Abprall(Ball *SpielballPtr, Schlaeger *Schlaeger2Ptr){

	//Ist der Ball innerhalb der Zone A des Schlägers
	if(SpielballPtr->ypos>=Schlaeger2Ptr->ypos && SpielballPtr->ypos<Schlaeger2Ptr->yzonea){
	//Abprallverhalten durch Änderung des Geschwindigkeitsvektores
		SpielballPtr->vx=-1*abs(SpielballPtr->vx-1);					//X Komponente invertieren
		SpielballPtr->vy=-1*(abs(SpielballPtr->vy)+2);			//Nach oben ablenken und Geschwindigkeit erhöhen
	}

	//Ist der Ball innerhalb der Zone B des Schlägers
	if(SpielballPtr->ypos>=Schlaeger2Ptr->yzonea && SpielballPtr->ypos<Schlaeger2Ptr->yzoneb){
		//Abprallverhalten durch Änderung des Geschwindigkeitsvektores
		SpielballPtr->vx=-1*(abs(SpielballPtr->vx));			//X Komponente invertieren und Geschwindigkeit erhöhen
		SpielballPtr->vy=-1;									//Ablenken mit Y-Komponente = -1, zwingender Abprall leicht nach oben
	}

	//Ist der Ball innerhalb der Zone C des Schlägers
	if(SpielballPtr->ypos>=Schlaeger2Ptr->yzoneb && SpielballPtr->ypos<Schlaeger2Ptr->yzonec){
		//Abprallverhalten durch Änderung des Geschwindigkeitsvektores
		SpielballPtr->vx=-1*(abs(SpielballPtr->vx));			//X Komponente invertieren und Geschwindigkeit erhöhen
		SpielballPtr->vy=1;										//Ablenken mit Y-Komponente = 1, zwingender Abprall leicht nach unten
	}

	//Ist der Ball innerhalb der Zone D des Schlägers
	if(SpielballPtr->ypos>=Schlaeger2Ptr->yzonec && SpielballPtr->ypos<Schlaeger2Ptr->yzoned){
		//Abprallverhalten durch Änderung des Geschwindigkeitsvektores
		SpielballPtr->vx=-1*abs(SpielballPtr->vx-1);			//X Komponente invertieren
		SpielballPtr->vy=(abs(SpielballPtr->vy)+2);				//Nach unten ablenken und Geschwindigkeit erhöhen
	}


	//Bewegungsgleichung neu aufsetzen
	SpielballPtr->xnull=SpielballPtr->xpos;						//Neuer Nullvektor zuweisen
	SpielballPtr->ynull=SpielballPtr->ypos;
	SpielballPtr->Zeit=1;										//Zeitkomponente rücksetzen
}

/*****************************************************************************
**	Ende der Unterfnuktionen zur Ballpositionsbestimmungen
*****************************************************************************/
/**
*****************************************************************************
**	Projekt Pong
**	BTE 5052	FS2015
*****************************************************************************
**
**	Funktionsname   	: BallPos
**
**	Funktion   			: Berechnug der nächsten Ballposition und je nach Ort das entsprechende Abprallverhalten ausführen.
**
**	Rückgabe			: Abbruchmeldung für die Spielschleife
**
**	Input				: Zeiger auf den Spielball, Zeiger auf den Schläger 1, Zeiger auf Schläger 2, Zeiger auf die Anzeigeparameter, Zeiger auf den Modus.
**
**	Output				: Es wird direkt an die jeweilige Adresse geschrieben.
**
** 	Author				: kupfe1/alles1
**
**	Tests				: Test von 1V02 am 13.03.2015
**
******************************************************************************/
//Ballposition
int BallPos(Ball *SpielballPtr,
			Schlaeger *Schlaeger1Ptr,
			Schlaeger *Schlaeger2Ptr,
			int *XposBall,int *YposBall,				//Zeiger auf die Positionen in der Anzeigestruktur
			SpielModus *ModusPtr,
			Hindernis *Hinderniss1Ptr,
			Hindernis *Hinderniss2Ptr,
			int *GewinnerPtr)
{
	//Feldbeschränkung für die Berechnungen
	int xmin=25,xmax=1275,ymin=10,ymax=730;

	//Um an den Spielfeldgrenzen ein "Festkleben" des Balles zu verhindern, wird für eine gewisse Anzahl Zeitdurchläufe
	//die Steuerung deaktiviert.
	if((SpielballPtr->Zeit)>6){

		//Abprallfälle durchtesten

		//Obere Wand und untere Wand
		if(SpielballPtr->ypos <= ymin || SpielballPtr->ypos >=ymax){
			//Funktion Verhalten bei Abprall an der unteren und oberen Wand
			UntereObereWand(SpielballPtr);
		}

		//Ist der Ball auf Höhe des Schlägers 1 auf der X Achse
		if(SpielballPtr->xpos<=Schlaeger1Ptr->xpos){
			//Ist der Ball innerhalb des Schlägers
			if(SpielballPtr->ypos>=Schlaeger1Ptr->ypos && SpielballPtr->ypos<=Schlaeger1Ptr->yzoned){
				//Funktion Verhalten bei Abprall am linken Schläger aufrufen
				Schlaeger1Abprall(SpielballPtr,Schlaeger1Ptr);
			}
		}

		//Ist der Ball auf Höhe des Schlägers 2 auf der X Achse
		if(SpielballPtr->xpos>=Schlaeger2Ptr->xpos){
			//Ist der Ball innerhalb des Schlägers
			if(SpielballPtr->ypos>=Schlaeger2Ptr->ypos && SpielballPtr->ypos<=Schlaeger2Ptr->yzoned){
				//Funktion Verhalten bei Abprall am rechten Schläger aufrufen
				Schlaeger2Abprall(SpielballPtr,Schlaeger2Ptr);
			}
		}

		//Hindernisse ab Level 4
		if(ModusPtr->Schwierigkeitsgrad>=4){
			//Prallt der Ball auf Hindeniss 1 (links)
			//Fliegt der Ball gegen rechts
			if(SpielballPtr->vx>0){
				//Ist der Ball auf Höhe des Hindernisses auf der X Achse
				if(SpielballPtr->xpos >= Hinderniss1Ptr->xpos && SpielballPtr->xpos < (Hinderniss1Ptr->xpos)+25){		//Um Abpraller hinter dem Hinderniss zu unterdrücken
					//Ist der Ball auf der Höhe des Hindernisses auf der Y Achse										//wird die Aufprallzone hinter dem Hinderniss begrenzt
					if(SpielballPtr->ypos >= Hinderniss1Ptr->ypos && SpielballPtr->ypos <= Hinderniss1Ptr->ymax){
						HindernisAbprall(SpielballPtr);
					}
				}
			}
			//Fliegt der Ball nach links
			else
			{
				//Ist der Ball auf Höhe des Hindernisses auf der X Achse
				if(SpielballPtr->xpos <= (Hinderniss1Ptr->xpos+15) && SpielballPtr->xpos > (Hinderniss1Ptr->xpos)-15){		//Um Abpraller hinter dem Hinderniss zu unterdrücken
					//Ist der Ball auf der Höhe des Hindernisses auf der Y Achse											//wird die Aufprallzone hinter dem Hinderniss begrenzt
					if(SpielballPtr->ypos >= Hinderniss1Ptr->ypos && SpielballPtr->ypos <= Hinderniss1Ptr->ymax){
						HindernisAbprall(SpielballPtr);
					}
				}
			}

			//Prallt der Ball auf Hinderniss 2 (rechts)
			//Fliegt der Ball nach rechts
			if(SpielballPtr->vx>0){
				//Ist der Ball auf Höhe des Hindernisses auf der X Achse
				if(SpielballPtr->xpos >= Hinderniss2Ptr->xpos && SpielballPtr->xpos < (Hinderniss2Ptr->xpos)+25){		//Um Abpraller hinter dem Hinderniss zu unterdrücken
					//Ist der Ball auf der Höhe des Hindernisses auf der Y Achse										//wird die Aufprallzone hinter dem Hinderniss begrenzt
					if(SpielballPtr->ypos >= Hinderniss2Ptr->ypos && SpielballPtr->ypos <= Hinderniss2Ptr->ymax){
						HindernisAbprall(SpielballPtr);
					}
				}
			}
			//Fliegt der Ball nach links
			else
			{
				//Ist der Ball auf Höhe des Hindernisses auf der X Achse
				if(SpielballPtr->xpos <= (Hinderniss2Ptr->xpos+15) && SpielballPtr->xpos > (Hinderniss2Ptr->xpos)-15){		//Um Abpraller hinter dem Hinderniss zu unterdrücken
					//Ist der Ball auf der Höhe des Hindernisses auf der Y Achse											//wird die Aufprallzone hinter dem Hinderniss begrenzt
					if(SpielballPtr->ypos >= Hinderniss2Ptr->ypos && SpielballPtr->ypos <= Hinderniss2Ptr->ymax){
						HindernisAbprall(SpielballPtr);
					}
				}
			}
		}

		//Geht der Ball ins Aus bei Spieler 1
		if(SpielballPtr->xpos<=xmin && !(SpielballPtr->ypos>=Schlaeger1Ptr->ypos && SpielballPtr->ypos<=Schlaeger1Ptr->yzoned)){		// Ball darf nicht innerhalb des Schlägers 1 sein
			//Sieger bestimmen
			*GewinnerPtr=2;
			SpielballPtr->Zeit=1;									//Zeitkomponente rücksetzen
			return 0;												//Abbruchrückmeldung
		}

		//Geht der Ball ins Aus bei Spieler 2
		if(SpielballPtr->xpos>=xmax && !(SpielballPtr->ypos>=Schlaeger2Ptr->ypos && SpielballPtr->ypos<=Schlaeger2Ptr->yzoned)){		// Ball darf nicht innerhalb des Schlägers 2 sein
			//Sieger bestimmen
			*GewinnerPtr=1;
			SpielballPtr->Zeit=1;									//Zeitkomponente rücksetzen
			return 0;												//Abbruchrückmeldung
		}

	}

	//Berechnug der neuen Koordinaten des Balles mit der Bewegungsgleichung
	SpielballPtr->xpos=(SpielballPtr->xnull) + (SpielballPtr->GeschwindigkeitsFaktor)*(SpielballPtr->Zeit)*(SpielballPtr->vx);
	SpielballPtr->ypos=(SpielballPtr->ynull) + (SpielballPtr->GeschwindigkeitsFaktor)*(SpielballPtr->Zeit)*(SpielballPtr->vy);

	//Speicherung der Ballposition in der Anzeigestruktur
	*XposBall=SpielballPtr->xpos;
	*YposBall=SpielballPtr->ypos;

	//Zeit inkrementieren und zwischenspeichern
	SpielballPtr->Zeit += 1;

	return 1;														//Keine Abbruchrückmeldung
}

/*****************************************************************************
**	Ende BallPos
*****************************************************************************/

/**
*****************************************************************************
**	Projekt Pong
**	BTE 5052	FS2015
*****************************************************************************
**
**	Funktionsname   	: StartPosBall1
**
**	Funktion   			: Berechnug der Startposition des Balles am Anfang eines Spiels
**
**	Rückgabe			: Nichts
**
**	Input				: Zeiger auf den Spielball, Zeiger auf den Modus und Zeiger auf den Gewinner
**
**	Output				: Es wird direkt an die Adresse des Spielball geschrieben.
**
** 	Author				: kupfe1/alles1
**
******************************************************************************/
void StartPosBall1(Ball *SpielballPtr, SpielModus *ModusPtr, int *GewinnerPtr){

		//Variablen
		int Zufallszahl;										//Zufallszahl um die erste Startposition zu bestimmen
		int FaktorStartgeschwindigkeit=1;						//Faktor um die Startgeschwindigkeit levelabhängig zu machen

		//Zufallszahl generieren
		Zufallszahl=time(NULL)%2;

		//Faktor Startgeschwindigkeit anpassen
		if(ModusPtr->Schwierigkeitsgrad==1){
			FaktorStartgeschwindigkeit=4;
		}
		if(ModusPtr->Schwierigkeitsgrad==2){
			FaktorStartgeschwindigkeit=5;
		}
		if(ModusPtr->Schwierigkeitsgrad>=3){
			FaktorStartgeschwindigkeit=6;
		}


		printf("Zufallszahl: %d\n", Zufallszahl);
		printf("Gewinner: %d\n", *GewinnerPtr);

		switch(*GewinnerPtr){

			case 0:	if(Zufallszahl==1){
						SpielballPtr->xnull=25;
						SpielballPtr->ynull=420;
						SpielballPtr->vx=2;
						SpielballPtr->vy=0;
						SpielballPtr->Zeit=1;
						SpielballPtr->GeschwindigkeitsFaktor=FaktorStartgeschwindigkeit;
					}
					else{
						SpielballPtr->xnull=1250;
						SpielballPtr->ynull=420;
						SpielballPtr->vx=-2;
						SpielballPtr->vy=0;
						SpielballPtr->Zeit=1;
						SpielballPtr->GeschwindigkeitsFaktor=FaktorStartgeschwindigkeit;
					}

					break;

			case 1:		SpielballPtr->xnull=1250;
						SpielballPtr->ynull=420;
						SpielballPtr->vx=-2;
						SpielballPtr->vy=0;
						SpielballPtr->Zeit=1;
						SpielballPtr->GeschwindigkeitsFaktor=FaktorStartgeschwindigkeit;

					break;

			case 2:		SpielballPtr->xnull=25;
						SpielballPtr->ynull=420;
						SpielballPtr->vx=2;
						SpielballPtr->vy=0;
						SpielballPtr->Zeit=1;
						SpielballPtr->GeschwindigkeitsFaktor=FaktorStartgeschwindigkeit;

					break;

			default:
					break;
		}
}

/*****************************************************************************
**	Ende StartPosBall1
*****************************************************************************/

/**
*****************************************************************************
**	Projekt Pong
**	BTE 5052	FS2015
*****************************************************************************
**
**	Funktionsname   	: StartPosBall2
**
**	Funktion   			: Berechnug der Startposition des Balles am Anfang eines Spiels
**
**	Rückgabe			: Nichts
**
**	Input				: Zeiger auf den Spielball, Zeiger auf den Modus und Zeiger auf den Gewinner
**
**	Output				: Es wird direkt an die Adresse des Spielball geschrieben.
**
** 	Author				: kupfe1/alles1
**
******************************************************************************/
void StartPosBall2(Ball *SpielballPtr){

	//Startparameter Ball	2
	SpielballPtr->xnull=650;
	SpielballPtr->ynull=500;
	SpielballPtr->vx=-2;
	SpielballPtr->vy=1;
	SpielballPtr->Zeit=1;
	SpielballPtr->GeschwindigkeitsFaktor=2;

	return;
}

/*****************************************************************************
**	Ende StartPosBall2
*****************************************************************************/

/**
*****************************************************************************
**	Projekt Pong
**	BTE 5052	FS2015
*****************************************************************************
**
**	Funktionsname   	: GeschwBallErhoehen
**
**	Funktion   			: Erhöhung der Ballgeschwindigkeit nach einer bestimmten Spielzeit
**
**	Rückgabe			: Nichts
**
**	Input				: Zeiger auf die Spielparameter, Zeiger auf die Startzeit, Zeiger auf den Spielball, Zeiger auf die Schläger
**
**	Output				: Es wird direkt an die Adresse des Spielballes geschrieben.
**
** 	Author				: kupfe1
**
******************************************************************************/

void GeschwBallErhoehen(int *Startzeit, SpielModus *ModusPtr, Ball *Spielball1Ptr,Schlaeger *Schlaeger2Ptr,Schlaeger *Schlaeger1Ptr){

		//Variablen deklarieren
		int Zeitdiff;												//Variable um die Zeitdifferenz in Sekunden zu speichern

		Zeitdiff=time(NULL)-(*Startzeit);

		switch(ModusPtr->Schwierigkeitsgrad){
					//Geschwindikeitserhöhung im Level 1
			case 1:	if(Zeitdiff>20 && ((Spielball1Ptr->xpos<=Schlaeger1Ptr->xpos) || (Spielball1Ptr->xpos>=Schlaeger2Ptr->xpos))){			//Geschwindigkeit wird nur erhöht, wenn der Ball auf einen Schläger trifft
						Spielball1Ptr->GeschwindigkeitsFaktor++;
						*Startzeit=time(NULL);
					}
					//Testprint
					//printf("Zeitdiff: %d\t Geschwindigkeitsfaktor: %d\n",Zeitdiff,Spielball1Ptr->GeschwindigkeitsFaktor);
					break;

					//Geschwindikeitserhöhung im Level 2
			case 2:	if(Zeitdiff>16 && ((Spielball1Ptr->xpos<=Schlaeger1Ptr->xpos) || (Spielball1Ptr->xpos>=Schlaeger2Ptr->xpos))){			//Geschwindigkeit wird nur erhöht, wenn der Ball auf einen Schläger trifft
						Spielball1Ptr->GeschwindigkeitsFaktor++;
						*Startzeit=time(NULL);
					}
					break;

					//Geschwindikeitserhöhung im Level 3
			case 3:	if(Zeitdiff>12 && ((Spielball1Ptr->xpos<=Schlaeger1Ptr->xpos) || (Spielball1Ptr->xpos>=Schlaeger2Ptr->xpos))){			//Geschwindigkeit wird nur erhöht, wenn der Ball auf einen Schläger trifft
						Spielball1Ptr->GeschwindigkeitsFaktor++;
						*Startzeit=time(NULL);
					}
					break;

					//Geschwindikeitserhöhung im Level 4
			case 4:	if(Zeitdiff>12 && ((Spielball1Ptr->xpos<=Schlaeger1Ptr->xpos) || (Spielball1Ptr->xpos>=Schlaeger2Ptr->xpos))){			//Geschwindigkeit wird nur erhöht, wenn der Ball auf einen Schläger trifft
						Spielball1Ptr->GeschwindigkeitsFaktor++;
						*Startzeit=time(NULL);
					}
					break;

					//Geschwindikeitserhöhung im Level 5
			case 5:	if(Zeitdiff>12 && ((Spielball1Ptr->xpos<=Schlaeger1Ptr->xpos) || (Spielball1Ptr->xpos>=Schlaeger2Ptr->xpos))){			//Geschwindigkeit wird nur erhöht, wenn der Ball auf einen Schläger trifft
						Spielball1Ptr->GeschwindigkeitsFaktor++;
						*Startzeit=time(NULL);
					}
					break;

			default: break;
		}
}

/*****************************************************************************
**	Ende GeschwBallErhoehen
*****************************************************************************/



