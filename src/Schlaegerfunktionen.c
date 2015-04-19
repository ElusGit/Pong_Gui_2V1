/*
 * Schlaegerfunktionen.c
 *Beschrieb einf�gen
 *  Created on: 14.03.2015
 *      Author: Eliott Kupferschmied
 */
/**
*****************************************************************************
**	Projekt Pong
**	BTE 5052	FS2015
*****************************************************************************
**
**	File        : Schlaegerfunktionen.c
**
**	Funktion   	: Unterfunktionen f�r die Schl�gerverschiebungen und f�r die Berechnung der Schl�gerdimensionen.
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
**	Bugs		: keine bekannte Fehler
**
**	Tests		: Test von 1V01 am 10.03.2015
**				  Test von 1V02 am 12.03.2015
**				  Test von 1V03 am 14.03.2015
**				  Test von 1V04 am 16.03.2015
**				  Test von 1V05 am 28.03.2015
**
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
static void Schlaeger2Ab(int ySpeedPad, Schlaeger *Schlaeger2Ptr, AnzeigeParameter *UebergabeAnzeigePtr);		//Nur in File Schlaegerfunktionen zur Verf�gung stellen
static void Schlaeger2Auf(int ySpeedPad, Schlaeger *Schlaeger2Ptr, AnzeigeParameter *UebergabeAnzeigePtr);
static void Schlaeger1Ab(int ySpeedPad, Schlaeger *Schlaeger1Ptr, AnzeigeParameter *UebergabeAnzeigePtr);
static void Schlaeger1Auf(int ySpeedPad, Schlaeger *Schlaeger1Ptr, AnzeigeParameter *UebergabeAnzeigePtr);

/**
*****************************************************************************
**	Projekt Pong
**	BTE 5052	FS2015
*****************************************************************************
**
**	Funktionsname   	: Schlaeger1Auf
**
**	Funktion   			: Aufw�rtsbewegung des linken Schl�gers ausf�hren.
**
**	R�ckgabe			: Keine
**
**	Input				: Parameter der die Anzahl Inkremente pro Bewegung �bergibt, Zeiger auf den Schl�ger 1, Zeiger auf die Anzeigeparameter.
**
**	Output				: Es wird direkt an die Adresse des Schl�gers und der Anzeigeparameter geschrieben.
**
** 	Author				: kupfe1/alles1
**
******************************************************************************/

static void Schlaeger1Auf(int ySpeedPad, Schlaeger *Schlaeger1Ptr, AnzeigeParameter *UebergabeAnzeigePtr)
	{
	Schlaeger1Ptr->ypos -=ySpeedPad;			//Bewegung der Position direkt in Struktur ver�ndern
	UebergabeAnzeigePtr->YPosPad1=Schlaeger1Ptr->ypos;		//Bewegung direkt in Struktur der �bergabeparameter f�rs GUI ver�ndern
	Schlaeger1Ptr->yzonea -=ySpeedPad;			//Bewegung unteren Grenze der Zone A direkt in Struktur ver�ndern
	Schlaeger1Ptr->yzoneb -=ySpeedPad;			//Bewegung unteren Grenze der Zone B  direkt in Struktur ver�ndern
	Schlaeger1Ptr->yzonec -=ySpeedPad;			//Bewegung unteren Grenze der Zone C direkt in Struktur ver�ndern
	Schlaeger1Ptr->yzoned -=ySpeedPad;			//Bewegung der unteren Schl�gergrenze direkt in Struktur ver�ndern
	}

/**
*****************************************************************************
**	Projekt Pong
**	BTE 5052	FS2015
*****************************************************************************
**
**	Funktionsname   	: Schlaeger1Ab
**
**	Funktion   			: Abw�rtsbewegung des linken Schl�gers ausf�hren.
**
**	R�ckgabe			: Keine
**
**	Input				: Parameter der die Anzahl Inkremente pro Bewegung �bergibt, Zeiger auf den Schl�ger 1, Zeiger auf die Anzeigeparameter.
**
**	Output				: Es wird direkt an die Adresse des Schl�gers und der Anzeigeparameter geschrieben.
**
** 	Author				: kupfe1/alles1
**
******************************************************************************/

static void Schlaeger1Ab(int ySpeedPad, Schlaeger *Schlaeger1Ptr, AnzeigeParameter *UebergabeAnzeigePtr)
	{
	Schlaeger1Ptr->ypos +=ySpeedPad;						//Bewegung der Position direkt in Struktur ver�ndern
	UebergabeAnzeigePtr->YPosPad1=Schlaeger1Ptr->ypos;		//Bewegung direkt in Struktur der �bergabeparameter f�rs GUI ver�ndern
	Schlaeger1Ptr->yzonea +=ySpeedPad;						//Bewegung unteren Grenze der Zone A direkt in Struktur ver�ndern
	Schlaeger1Ptr->yzoneb +=ySpeedPad;						//Bewegung unteren Grenze der Zone B  direkt in Struktur ver�ndern
	Schlaeger1Ptr->yzonec +=ySpeedPad;						//Bewegung unteren Grenze der Zone C direkt in Struktur ver�ndern
	Schlaeger1Ptr->yzoned +=ySpeedPad;						//Bewegung der unteren Schl�gergrenze direkt in Struktur ver�ndern
	}

/**
*****************************************************************************
**	Projekt Pong
**	BTE 5052	FS2015
*****************************************************************************
**
**	Funktionsname   	: Schlaeger2Auf
**
**	Funktion   			: Aufw�rtsbewegung des rechten Schl�gers ausf�hren.
**
**	R�ckgabe			: Keine
**
**	Input				: Parameter der die Anzahl Inkremente pro Bewegung �bergibt, Zeiger auf den Schl�ger 2, Zeiger auf die Anzeigeparameter.
**
**	Output				: Es wird direkt an die Adresse des Schl�gers und der Anzeigeparameter geschrieben.
**
** 	Author				: kupfe1/alles1
**
******************************************************************************/

static void Schlaeger2Auf(int ySpeedPad, Schlaeger *Schlaeger2Ptr, AnzeigeParameter *UebergabeAnzeigePtr)
	{
	Schlaeger2Ptr->ypos -=ySpeedPad;				//Bewegung der Position direkt in Struktur ver�ndern
	UebergabeAnzeigePtr->YPosPad2=Schlaeger2Ptr->ypos;		//Bewegung direkt in Struktur der �bergabeparameter f�rs GUI ver�ndern
	Schlaeger2Ptr->yzonea -=ySpeedPad;				//Bewegung unteren Grenze der Zone A direkt in Struktur ver�ndern
	Schlaeger2Ptr->yzoneb -=ySpeedPad;				//Bewegung unteren Grenze der Zone B  direkt in Struktur ver�ndern
	Schlaeger2Ptr->yzonec -=ySpeedPad;				//Bewegung unteren Grenze der Zone C direkt in Struktur ver�ndern
	Schlaeger2Ptr->yzoned -=ySpeedPad;				//Bewegung der unteren Schl�gergrenze direkt in Struktur ver�ndern
	}

/**
*****************************************************************************
**	Projekt Pong
**	BTE 5052	FS2015
*****************************************************************************
**
**	Funktionsname   	: Schlaeger2Ab
**
**	Funktion   			: Abw�rtsbewegung des rechten Schl�gers ausf�hren.
**
**	R�ckgabe			: Keine
**
**	Input				: Parameter der die Anzahl Inkremente pro Bewegung �bergibt, Zeiger auf den Schl�ger 2, Zeiger auf die Anzeigeparameter.
**
**	Output				: Es wird direkt an die Adresse des Schl�gers und der Anzeigeparameter geschrieben.
**
** 	Author				: kupfe1/alles1
**
******************************************************************************/

static void Schlaeger2Ab(int ySpeedPad, Schlaeger *Schlaeger2Ptr, AnzeigeParameter *UebergabeAnzeigePtr)
	{
	Schlaeger2Ptr->ypos +=ySpeedPad;						//Bewegung der Position direkt in Struktur ver�ndern
	UebergabeAnzeigePtr->YPosPad2=Schlaeger2Ptr->ypos;		//Bewegung direkt in Struktur der �bergabeparameter f�rs GUI ver�ndern
	Schlaeger2Ptr->yzonea +=ySpeedPad;						//Bewegung unteren Grenze der Zone A direkt in Struktur ver�ndern
	Schlaeger2Ptr->yzoneb +=ySpeedPad;						//Bewegung unteren Grenze der Zone B  direkt in Struktur ver�ndern
	Schlaeger2Ptr->yzonec +=ySpeedPad;						//Bewegung unteren Grenze der Zone C direkt in Struktur ver�ndern
	Schlaeger2Ptr->yzoned +=ySpeedPad;						//Bewegung der unteren Schl�gergrenze direkt in Struktur ver�ndern
	}

/**
*****************************************************************************
**	Projekt Pong
**	BTE 5052	FS2015
*****************************************************************************
**
**	Funktionsname   	: SchlaegerPos
**
**	Funktion   			: Hauptfunktion der Schl�gersteuerung. Auslesen der Tastendr�cke und einleiten der entsprechenden Bewegungen mit den Unterfunktionen.
**
**	R�ckgabe			: Abbruchflag wenn die ESC Taste gedr�ckt wurde
**
**	Input				: Zeiger auf den Schl�ger 1, Zeiger auf den Schl�ger 2, Zeiger auf die Anzeigeparameter.
**
**	Output				: Es wird direkt an die Adresse des Schl�gers 1, sowie des Schl�gers 2 und der Anzeigeparameter geschrieben.
**
** 	Author				: kupfe1/alles1/michael.schmutz
**
******************************************************************************/

//Hauptfunktion Schl�gerposition
int SchlaegerPos(Schlaeger *Schlaeger1Ptr, Schlaeger *Schlaeger2Ptr, AnzeigeParameter *UebergabeAnzeigePtr, SpielModus *ModusPtr){
	//Steuervariablen
	int ySpeedPad=7+ModusPtr->Schwierigkeitsgrad;				//Geschwindigkeit der Schl�ger mit zunemendem SChwierigkeitsgrad erh�hen
	int Key;

	//Funktion
	while(IsKeyEventReady() > 0){								//Nur wenn ein Tastendruck anliegt kann eine Anweisung folgen.

		Key = GetKeyEvent();									//Tastendruck auslesen

		//Schl�ger 1
		if(Key=='w')
			{
			Schlaeger1Ptr->GoUp = 1;							//Steuerflag Schl�ger 1 auf setzen
			}
		if (Key==('w' | W_KEY_RELEASED))
			{
			Schlaeger1Ptr->GoUp = 0;							//Steuerflag Schl�ger 1 auf r�cksetzen
			}
		if(Key=='s')
			{
			Schlaeger1Ptr->GoDown= 1;							//Steuerflag Schl�ger 1 ab	setzen
			}
		if (Key==('s'| W_KEY_RELEASED))
			{
			Schlaeger1Ptr->GoDown = 0;							//Steuerflag Schl�ger 1 ab	r�cksetzen
			}


		//Schl�ger 2 bei zwei Spieler
		if(ModusPtr->ZweiSpieler != 0){
			if(Key==W_KEY_CURSOR_UP)
				{
				Schlaeger2Ptr->GoUp = 1;						//Steuerflag Schl�ger 2 auf setzen
				}

			if (Key==(W_KEY_CURSOR_UP | W_KEY_RELEASED))
				{
				Schlaeger2Ptr->GoUp = 0;						//Steuerflag Schl�ger 2 auf r�cksetzen
				}
			if(Key==W_KEY_CURSOR_DOWN)
				{
				Schlaeger2Ptr->GoDown = 1;						//Steuerflag Schl�ger 2 ab	setzen
				}
			if (Key==(W_KEY_CURSOR_DOWN | W_KEY_RELEASED))
				{
				Schlaeger2Ptr->GoDown = 0;						//Steuerflag Schl�ger 2 ab	r�cksetzen
				}
		}


		//Abbruchfall
		if (Key==W_KEY_ESCAPE){																//Escape Taste verwerten
			return 0;
		}
	}

	//Auf und ab Funktionen ausf�hren
	if(Schlaeger1Ptr->GoUp==1 && Schlaeger1Ptr->GoDown == 0 && Schlaeger1Ptr->ypos>12 )  	//Nur wenn Steuerflags richtig gesetzt sind und sich der Schl�ger noch nicht am oberen Rand befindet
		{
		Schlaeger1Auf(ySpeedPad, Schlaeger1Ptr, UebergabeAnzeigePtr);						//Schl�ger 1 auf
		}
	if(Schlaeger1Ptr->GoDown==1 && Schlaeger1Ptr->GoUp == 0 && Schlaeger1Ptr->yzoned<750) 	//Nur wenn Steuerflags richtig gesetzt sind und sich der Schl�ger noch nicht am unteren Rand befindet
		{
		Schlaeger1Ab(ySpeedPad, Schlaeger1Ptr, UebergabeAnzeigePtr);						//Schl�ger 1 ab
		}
	if(Schlaeger2Ptr->GoUp==1 && Schlaeger2Ptr->GoDown ==0 && Schlaeger2Ptr->ypos>12)		//Nur wenn Steuerflags richtig gesetzt sind und sich der Schl�ger noch nicht am oberen Rand befindet
		{
		Schlaeger2Auf(ySpeedPad, Schlaeger2Ptr, UebergabeAnzeigePtr);						//Schl�ger 2 auf
		}
	if(Schlaeger2Ptr->GoDown==1 && Schlaeger2Ptr->GoUp==0 && Schlaeger2Ptr->yzoned<750) 	//Nur wenn Steuerflags richtig gesetzt sind und sich der Schl�ger noch nicht am unteren Rand befindet
		{
		Schlaeger2Ab(ySpeedPad, Schlaeger2Ptr, UebergabeAnzeigePtr);						//Schl�ger 2 ab
		}


	return 1;

}
/**
*****************************************************************************
**	Ende der Funktionen Schl�gerpositionen
*****************************************************************************
**
*****************************************************************************
**	Projekt Pong
**	BTE 5052	FS2015
*****************************************************************************
**
**	Funktionsname   	: BerechneSchlaegerdimension
**
**	Funktion   			: Berechnen der Schl�gerdimensionen und den verschiedenen Schl�gerzonen aus den Modus Parametern
**
**	R�ckgabe			: Nichts
**
**	Input				: Zeiger auf den Schl�ger 1, Zeiger auf den Schl�ger 2, Zeiger auf die Anzeigeparameter, Zeiger auf die ModusParameter.
**
**	Output				: Es wird direkt an die Adresse des Schl�gers 1, sowie des Schl�gers 2 und der Anzeigeparameter geschrieben.
**
** 	Author				: kupfe1/alles1
**
******************************************************************************/

void BerechneSchlaegerdimension(Schlaeger *Schlaeger1Ptr, Schlaeger *Schlaeger2Ptr, SpielModus *ModusPtr, AnzeigeParameter *UebergabeAnzeigePtr){
	//Steuerflag f�r die Zoneneinteilung
	int Levelanpassung=1;

	//Startpositionen
	Schlaeger1Ptr->xpos=25;										//Schl�ger 1
	Schlaeger1Ptr->ypos=500;

	Schlaeger2Ptr->xpos=1254;									//Schl�ger 2
	Schlaeger2Ptr->ypos=500;

	//Positionen in Anzeigeparameter schreiben
	UebergabeAnzeigePtr->YPosPad1=Schlaeger1Ptr->ypos;			//Schl�ger 1
	UebergabeAnzeigePtr->YPosPad2=Schlaeger2Ptr->ypos;			//Schl�ger 2

	//Schl�gerl�nge berechnen
	if(ModusPtr->Schwierigkeitsgrad > 1){
		UebergabeAnzeigePtr->LaengePad=100;						//L�nge bei Level 1
		Levelanpassung=2;
	}
	else
	{
		UebergabeAnzeigePtr->LaengePad=200;						//L�nge bei Level 2
		Levelanpassung=1;
	}

	//Steuerflags initialisieren
	//Schl�ger 1
	Schlaeger1Ptr->GoDown=0;
	Schlaeger1Ptr->GoUp=0;

	//Schl�ger 2
	Schlaeger2Ptr->GoDown=0;
	Schlaeger2Ptr->GoUp=0;

	//Zoneneinteilung Schl�ger 1
	Schlaeger1Ptr->yzonea=(Schlaeger1Ptr->ypos)+(50)/Levelanpassung;		//Zone A untere Beschr�nkung
	Schlaeger1Ptr->yzoneb=(Schlaeger1Ptr->yzonea)+(50)/Levelanpassung;		//Zone B untere Beschr�nkung
	Schlaeger1Ptr->yzonec=(Schlaeger1Ptr->yzoneb)+(50)/Levelanpassung;		//Zone C untere Beschr�nkung
	Schlaeger1Ptr->yzoned=(Schlaeger1Ptr->yzonec)+(50)/Levelanpassung;		//Zone D untere Beschr�nkung und unteres Schl�gerende

	//Zoneneinteilung Schl�ger 2
	Schlaeger2Ptr->yzonea=(Schlaeger2Ptr->ypos)+(50)/Levelanpassung;		//Zone A untere Beschr�nkung
	Schlaeger2Ptr->yzoneb=(Schlaeger2Ptr->yzonea)+(50)/Levelanpassung;		//Zone B untere Beschr�nkung
	Schlaeger2Ptr->yzonec=(Schlaeger2Ptr->yzoneb)+(50)/Levelanpassung;		//Zone C untere Beschr�nkung
	Schlaeger2Ptr->yzoned=(Schlaeger2Ptr->yzonec)+(50)/Levelanpassung;		//Zone D untere Beschr�nkung und unteres Schl�gerende

}

/*****************************************************************************
**	Ende Schl�gerdimensionen
*****************************************************************************/
/**
*****************************************************************************
**	Projekt Pong
**	BTE 5052	FS2015
*****************************************************************************
**
**	Funktionsname   	: BerechneHindernissPosition
**
**	Funktion   			: Berechnen der Hindernisspositionen
**
**	R�ckgabe			: Nichts
**
**	Input				: Zeiger auf Hinderniss 1, Zeiger auf Hinderniss 2, Zeiger auf die Anzeigeparameter.
**
**	Output				: Es wird direkt an die Adresse des Hindernisses 1, sowie des Hindernisses 2 und der Anzeigeparameter geschrieben.
**
** 	Author				: kupfe1
**
******************************************************************************/

void BerechneHindernisPos(Hindernis *Hinderniss1Ptr, Hindernis *Hinderniss2Ptr, AnzeigeParameter *UebergabeAnzeigePtr){

	//Variablen deklarieren
	int	xPosZufallskonstante=0;						//Zufallskonstante um die Hindernisse zuf�llig auf der X Achse in der jeweiligen Zone zu positionieren
	int yPosZufallskonstante=0;						//Zufallskonstante um die Hindernisse zuf�llig auf der Y Achse in der jeweiligen Zone zu positionieren
	int xPosBeginnZoneHinderniss1=325;				//Anfang der m�glichen Position auf der X Achse f�r Hinderniss 1
	int xPosBeginnZoneHinderniss2=650;				//Anfang der m�glichen Position auf der X Achse f�r Hinderniss 2
	int yPosBeginnZoneHinderniss1=0;				//Anfang der m�glichen Position auf der Y Achse f�r Hinderniss 1
	int yPosBeginnZoneHinderniss2=365;				//Anfang der m�glichen Position auf der Y Achse f�r Hinderniss 2
	int LaengeHinderniss=150;						//Vertikale Laenge des Hindernisses
	int Zeit;										//Zeit in Sekunden

	//2 Zufallszahlen generiern um die Positionen zu bestimmen
	Zeit=time(NULL);

	//Zufallskonstanten berechnen
	xPosZufallskonstante=Zeit%315;
	yPosZufallskonstante=Zeit%215;

	//Koordinaten berechnen Hinderniss 1
	Hinderniss1Ptr->xpos=xPosBeginnZoneHinderniss1+xPosZufallskonstante;
	Hinderniss1Ptr->ypos=yPosBeginnZoneHinderniss1+yPosZufallskonstante;

	//Koordinaten berechnen Hinderniss 2
	Hinderniss2Ptr->xpos=xPosBeginnZoneHinderniss2+xPosZufallskonstante;
	Hinderniss2Ptr->ypos=yPosBeginnZoneHinderniss2+yPosZufallskonstante;

	//Unteres Ende des Hindernisses berechnen
	Hinderniss1Ptr->ymax=Hinderniss1Ptr->ypos+LaengeHinderniss;
	Hinderniss2Ptr->ymax=Hinderniss2Ptr->ypos+LaengeHinderniss;

	// Uebergabe Hindernisspointer auf Anzeigeparameter
	UebergabeAnzeigePtr->XPosHindernis1=Hinderniss1Ptr->xpos;
	UebergabeAnzeigePtr->YPosHindernis1=Hinderniss1Ptr->ypos;
	UebergabeAnzeigePtr->XPosHindernis2=Hinderniss2Ptr->xpos;
	UebergabeAnzeigePtr->YPosHindernis2=Hinderniss2Ptr->ypos;

}

/*****************************************************************************
**	Ende BerechneHindernissPos
*****************************************************************************/

/**
*****************************************************************************
**	Projekt Pong
**	BTE 5052	FS2015
*****************************************************************************
**
**	Funktionsname   	: ComputerSchlaeger2
**
**	Funktion   			: Computersteuerung f�r Schl�ger 2
**
**	R�ckgabe			: Nichts
**
**	Input				: Zeiger auf Schlaeger 2 und Zeiger auf die Anzeigeparameter.
**
**	Output				: Es wird direkt an die Adresse von Schl�ger 2 und der Anzeigeparameter geschrieben.
**
** 	Author				: kupfe1
**
******************************************************************************/
void ComputerSchlaeger2(SpielModus *ModusPtr, Schlaeger *Schlaeger2Ptr, Ball *SpielballPtr, AnzeigeParameter *UebergabeAnzeigePtr){


	//Variablen deklarieren
	int ySpeedPad;

	//Schnelligkeit der Schl�gerbewegung in Abh�ngigkeit des Schwierigkeitsgrades
	ySpeedPad=3+3*(ModusPtr->Schwierigkeitsgrad);

	//Ist der Schl�ger unterhalb des Balles
	if((SpielballPtr->ypos <= Schlaeger2Ptr->yzonea+2) && (Schlaeger2Ptr->ypos>12)){
		Schlaeger2Auf(ySpeedPad, Schlaeger2Ptr, UebergabeAnzeigePtr);						//Schl�ger aufw�rts bewegen
	}
	//Ist der Schl�ger oberhalb des Balles
	if((SpielballPtr->ypos >= Schlaeger2Ptr->yzonec-2) &&  (Schlaeger2Ptr->yzoned<750)){
		Schlaeger2Ab(ySpeedPad, Schlaeger2Ptr, UebergabeAnzeigePtr);						//Schl�ger abw�rts bewegen
	}

	return;

}

/*****************************************************************************
**	Ende BerechneHindernissPos
*****************************************************************************/


