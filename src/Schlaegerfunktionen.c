/*
 * Schlaegerfunktionen.c
 *Beschrieb einfügen
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
**	Funktion   	: Unterfunktionen für die Schlägerverschiebungen und für die Berechnung der Schlägerdimensionen.
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
static void Schlaeger2Ab(int ySpeedPad, Schlaeger *Schlaeger2Ptr, AnzeigeParameter *UebergabeAnzeigePtr);		//Nur in File Schlaegerfunktionen zur Verfügung stellen
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
**	Funktion   			: Aufwärtsbewegung des linken Schlägers ausführen.
**
**	Rückgabe			: Keine
**
**	Input				: Parameter der die Anzahl Inkremente pro Bewegung übergibt, Zeiger auf den Schläger 1, Zeiger auf die Anzeigeparameter.
**
**	Output				: Es wird direkt an die Adresse des Schlägers und der Anzeigeparameter geschrieben.
**
** 	Author				: kupfe1/alles1
**
******************************************************************************/

static void Schlaeger1Auf(int ySpeedPad, Schlaeger *Schlaeger1Ptr, AnzeigeParameter *UebergabeAnzeigePtr)
	{
	Schlaeger1Ptr->ypos -=ySpeedPad;			//Bewegung der Position direkt in Struktur verändern
	UebergabeAnzeigePtr->YPosPad1=Schlaeger1Ptr->ypos;		//Bewegung direkt in Struktur der Übergabeparameter fürs GUI verändern
	Schlaeger1Ptr->yzonea -=ySpeedPad;			//Bewegung unteren Grenze der Zone A direkt in Struktur verändern
	Schlaeger1Ptr->yzoneb -=ySpeedPad;			//Bewegung unteren Grenze der Zone B  direkt in Struktur verändern
	Schlaeger1Ptr->yzonec -=ySpeedPad;			//Bewegung unteren Grenze der Zone C direkt in Struktur verändern
	Schlaeger1Ptr->yzoned -=ySpeedPad;			//Bewegung der unteren Schlägergrenze direkt in Struktur verändern
	}

/**
*****************************************************************************
**	Projekt Pong
**	BTE 5052	FS2015
*****************************************************************************
**
**	Funktionsname   	: Schlaeger1Ab
**
**	Funktion   			: Abwärtsbewegung des linken Schlägers ausführen.
**
**	Rückgabe			: Keine
**
**	Input				: Parameter der die Anzahl Inkremente pro Bewegung übergibt, Zeiger auf den Schläger 1, Zeiger auf die Anzeigeparameter.
**
**	Output				: Es wird direkt an die Adresse des Schlägers und der Anzeigeparameter geschrieben.
**
** 	Author				: kupfe1/alles1
**
******************************************************************************/

static void Schlaeger1Ab(int ySpeedPad, Schlaeger *Schlaeger1Ptr, AnzeigeParameter *UebergabeAnzeigePtr)
	{
	Schlaeger1Ptr->ypos +=ySpeedPad;						//Bewegung der Position direkt in Struktur verändern
	UebergabeAnzeigePtr->YPosPad1=Schlaeger1Ptr->ypos;		//Bewegung direkt in Struktur der Übergabeparameter fürs GUI verändern
	Schlaeger1Ptr->yzonea +=ySpeedPad;						//Bewegung unteren Grenze der Zone A direkt in Struktur verändern
	Schlaeger1Ptr->yzoneb +=ySpeedPad;						//Bewegung unteren Grenze der Zone B  direkt in Struktur verändern
	Schlaeger1Ptr->yzonec +=ySpeedPad;						//Bewegung unteren Grenze der Zone C direkt in Struktur verändern
	Schlaeger1Ptr->yzoned +=ySpeedPad;						//Bewegung der unteren Schlägergrenze direkt in Struktur verändern
	}

/**
*****************************************************************************
**	Projekt Pong
**	BTE 5052	FS2015
*****************************************************************************
**
**	Funktionsname   	: Schlaeger2Auf
**
**	Funktion   			: Aufwärtsbewegung des rechten Schlägers ausführen.
**
**	Rückgabe			: Keine
**
**	Input				: Parameter der die Anzahl Inkremente pro Bewegung übergibt, Zeiger auf den Schläger 2, Zeiger auf die Anzeigeparameter.
**
**	Output				: Es wird direkt an die Adresse des Schlägers und der Anzeigeparameter geschrieben.
**
** 	Author				: kupfe1/alles1
**
******************************************************************************/

static void Schlaeger2Auf(int ySpeedPad, Schlaeger *Schlaeger2Ptr, AnzeigeParameter *UebergabeAnzeigePtr)
	{
	Schlaeger2Ptr->ypos -=ySpeedPad;				//Bewegung der Position direkt in Struktur verändern
	UebergabeAnzeigePtr->YPosPad2=Schlaeger2Ptr->ypos;		//Bewegung direkt in Struktur der Übergabeparameter fürs GUI verändern
	Schlaeger2Ptr->yzonea -=ySpeedPad;				//Bewegung unteren Grenze der Zone A direkt in Struktur verändern
	Schlaeger2Ptr->yzoneb -=ySpeedPad;				//Bewegung unteren Grenze der Zone B  direkt in Struktur verändern
	Schlaeger2Ptr->yzonec -=ySpeedPad;				//Bewegung unteren Grenze der Zone C direkt in Struktur verändern
	Schlaeger2Ptr->yzoned -=ySpeedPad;				//Bewegung der unteren Schlägergrenze direkt in Struktur verändern
	}

/**
*****************************************************************************
**	Projekt Pong
**	BTE 5052	FS2015
*****************************************************************************
**
**	Funktionsname   	: Schlaeger2Ab
**
**	Funktion   			: Abwärtsbewegung des rechten Schlägers ausführen.
**
**	Rückgabe			: Keine
**
**	Input				: Parameter der die Anzahl Inkremente pro Bewegung übergibt, Zeiger auf den Schläger 2, Zeiger auf die Anzeigeparameter.
**
**	Output				: Es wird direkt an die Adresse des Schlägers und der Anzeigeparameter geschrieben.
**
** 	Author				: kupfe1/alles1
**
******************************************************************************/

static void Schlaeger2Ab(int ySpeedPad, Schlaeger *Schlaeger2Ptr, AnzeigeParameter *UebergabeAnzeigePtr)
	{
	Schlaeger2Ptr->ypos +=ySpeedPad;						//Bewegung der Position direkt in Struktur verändern
	UebergabeAnzeigePtr->YPosPad2=Schlaeger2Ptr->ypos;		//Bewegung direkt in Struktur der Übergabeparameter fürs GUI verändern
	Schlaeger2Ptr->yzonea +=ySpeedPad;						//Bewegung unteren Grenze der Zone A direkt in Struktur verändern
	Schlaeger2Ptr->yzoneb +=ySpeedPad;						//Bewegung unteren Grenze der Zone B  direkt in Struktur verändern
	Schlaeger2Ptr->yzonec +=ySpeedPad;						//Bewegung unteren Grenze der Zone C direkt in Struktur verändern
	Schlaeger2Ptr->yzoned +=ySpeedPad;						//Bewegung der unteren Schlägergrenze direkt in Struktur verändern
	}

/**
*****************************************************************************
**	Projekt Pong
**	BTE 5052	FS2015
*****************************************************************************
**
**	Funktionsname   	: SchlaegerPos
**
**	Funktion   			: Hauptfunktion der Schlägersteuerung. Auslesen der Tastendrücke und einleiten der entsprechenden Bewegungen mit den Unterfunktionen.
**
**	Rückgabe			: Abbruchflag wenn die ESC Taste gedrückt wurde
**
**	Input				: Zeiger auf den Schläger 1, Zeiger auf den Schläger 2, Zeiger auf die Anzeigeparameter.
**
**	Output				: Es wird direkt an die Adresse des Schlägers 1, sowie des Schlägers 2 und der Anzeigeparameter geschrieben.
**
** 	Author				: kupfe1/alles1/michael.schmutz
**
******************************************************************************/

//Hauptfunktion Schlägerposition
int SchlaegerPos(Schlaeger *Schlaeger1Ptr, Schlaeger *Schlaeger2Ptr, AnzeigeParameter *UebergabeAnzeigePtr, SpielModus *ModusPtr){
	//Steuervariablen
	int ySpeedPad=7+ModusPtr->Schwierigkeitsgrad;				//Geschwindigkeit der Schläger mit zunemendem SChwierigkeitsgrad erhöhen
	int Key;

	//Funktion
	while(IsKeyEventReady() > 0){								//Nur wenn ein Tastendruck anliegt kann eine Anweisung folgen.

		Key = GetKeyEvent();									//Tastendruck auslesen

		//Schläger 1
		if(Key=='w')
			{
			Schlaeger1Ptr->GoUp = 1;							//Steuerflag Schläger 1 auf setzen
			}
		if (Key==('w' | W_KEY_RELEASED))
			{
			Schlaeger1Ptr->GoUp = 0;							//Steuerflag Schläger 1 auf rücksetzen
			}
		if(Key=='s')
			{
			Schlaeger1Ptr->GoDown= 1;							//Steuerflag Schläger 1 ab	setzen
			}
		if (Key==('s'| W_KEY_RELEASED))
			{
			Schlaeger1Ptr->GoDown = 0;							//Steuerflag Schläger 1 ab	rücksetzen
			}


		//Schläger 2 bei zwei Spieler
		if(ModusPtr->ZweiSpieler != 0){
			if(Key==W_KEY_CURSOR_UP)
				{
				Schlaeger2Ptr->GoUp = 1;						//Steuerflag Schläger 2 auf setzen
				}

			if (Key==(W_KEY_CURSOR_UP | W_KEY_RELEASED))
				{
				Schlaeger2Ptr->GoUp = 0;						//Steuerflag Schläger 2 auf rücksetzen
				}
			if(Key==W_KEY_CURSOR_DOWN)
				{
				Schlaeger2Ptr->GoDown = 1;						//Steuerflag Schläger 2 ab	setzen
				}
			if (Key==(W_KEY_CURSOR_DOWN | W_KEY_RELEASED))
				{
				Schlaeger2Ptr->GoDown = 0;						//Steuerflag Schläger 2 ab	rücksetzen
				}
		}


		//Abbruchfall
		if (Key==W_KEY_ESCAPE){																//Escape Taste verwerten
			return 0;
		}
	}

	//Auf und ab Funktionen ausführen
	if(Schlaeger1Ptr->GoUp==1 && Schlaeger1Ptr->GoDown == 0 && Schlaeger1Ptr->ypos>12 )  	//Nur wenn Steuerflags richtig gesetzt sind und sich der Schläger noch nicht am oberen Rand befindet
		{
		Schlaeger1Auf(ySpeedPad, Schlaeger1Ptr, UebergabeAnzeigePtr);						//Schläger 1 auf
		}
	if(Schlaeger1Ptr->GoDown==1 && Schlaeger1Ptr->GoUp == 0 && Schlaeger1Ptr->yzoned<750) 	//Nur wenn Steuerflags richtig gesetzt sind und sich der Schläger noch nicht am unteren Rand befindet
		{
		Schlaeger1Ab(ySpeedPad, Schlaeger1Ptr, UebergabeAnzeigePtr);						//Schläger 1 ab
		}
	if(Schlaeger2Ptr->GoUp==1 && Schlaeger2Ptr->GoDown ==0 && Schlaeger2Ptr->ypos>12)		//Nur wenn Steuerflags richtig gesetzt sind und sich der Schläger noch nicht am oberen Rand befindet
		{
		Schlaeger2Auf(ySpeedPad, Schlaeger2Ptr, UebergabeAnzeigePtr);						//Schläger 2 auf
		}
	if(Schlaeger2Ptr->GoDown==1 && Schlaeger2Ptr->GoUp==0 && Schlaeger2Ptr->yzoned<750) 	//Nur wenn Steuerflags richtig gesetzt sind und sich der Schläger noch nicht am unteren Rand befindet
		{
		Schlaeger2Ab(ySpeedPad, Schlaeger2Ptr, UebergabeAnzeigePtr);						//Schläger 2 ab
		}


	return 1;

}
/**
*****************************************************************************
**	Ende der Funktionen Schlägerpositionen
*****************************************************************************
**
*****************************************************************************
**	Projekt Pong
**	BTE 5052	FS2015
*****************************************************************************
**
**	Funktionsname   	: BerechneSchlaegerdimension
**
**	Funktion   			: Berechnen der Schlägerdimensionen und den verschiedenen Schlägerzonen aus den Modus Parametern
**
**	Rückgabe			: Nichts
**
**	Input				: Zeiger auf den Schläger 1, Zeiger auf den Schläger 2, Zeiger auf die Anzeigeparameter, Zeiger auf die ModusParameter.
**
**	Output				: Es wird direkt an die Adresse des Schlägers 1, sowie des Schlägers 2 und der Anzeigeparameter geschrieben.
**
** 	Author				: kupfe1/alles1
**
******************************************************************************/

void BerechneSchlaegerdimension(Schlaeger *Schlaeger1Ptr, Schlaeger *Schlaeger2Ptr, SpielModus *ModusPtr, AnzeigeParameter *UebergabeAnzeigePtr){
	//Steuerflag für die Zoneneinteilung
	int Levelanpassung=1;

	//Startpositionen
	Schlaeger1Ptr->xpos=25;										//Schläger 1
	Schlaeger1Ptr->ypos=500;

	Schlaeger2Ptr->xpos=1254;									//Schläger 2
	Schlaeger2Ptr->ypos=500;

	//Positionen in Anzeigeparameter schreiben
	UebergabeAnzeigePtr->YPosPad1=Schlaeger1Ptr->ypos;			//Schläger 1
	UebergabeAnzeigePtr->YPosPad2=Schlaeger2Ptr->ypos;			//Schläger 2

	//Schlägerlänge berechnen
	if(ModusPtr->Schwierigkeitsgrad > 1){
		UebergabeAnzeigePtr->LaengePad=100;						//Länge bei Level 1
		Levelanpassung=2;
	}
	else
	{
		UebergabeAnzeigePtr->LaengePad=200;						//Länge bei Level 2
		Levelanpassung=1;
	}

	//Steuerflags initialisieren
	//Schläger 1
	Schlaeger1Ptr->GoDown=0;
	Schlaeger1Ptr->GoUp=0;

	//Schläger 2
	Schlaeger2Ptr->GoDown=0;
	Schlaeger2Ptr->GoUp=0;

	//Zoneneinteilung Schläger 1
	Schlaeger1Ptr->yzonea=(Schlaeger1Ptr->ypos)+(50)/Levelanpassung;		//Zone A untere Beschränkung
	Schlaeger1Ptr->yzoneb=(Schlaeger1Ptr->yzonea)+(50)/Levelanpassung;		//Zone B untere Beschränkung
	Schlaeger1Ptr->yzonec=(Schlaeger1Ptr->yzoneb)+(50)/Levelanpassung;		//Zone C untere Beschränkung
	Schlaeger1Ptr->yzoned=(Schlaeger1Ptr->yzonec)+(50)/Levelanpassung;		//Zone D untere Beschränkung und unteres Schlägerende

	//Zoneneinteilung Schläger 2
	Schlaeger2Ptr->yzonea=(Schlaeger2Ptr->ypos)+(50)/Levelanpassung;		//Zone A untere Beschränkung
	Schlaeger2Ptr->yzoneb=(Schlaeger2Ptr->yzonea)+(50)/Levelanpassung;		//Zone B untere Beschränkung
	Schlaeger2Ptr->yzonec=(Schlaeger2Ptr->yzoneb)+(50)/Levelanpassung;		//Zone C untere Beschränkung
	Schlaeger2Ptr->yzoned=(Schlaeger2Ptr->yzonec)+(50)/Levelanpassung;		//Zone D untere Beschränkung und unteres Schlägerende

}

/*****************************************************************************
**	Ende Schlägerdimensionen
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
**	Rückgabe			: Nichts
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
	int	xPosZufallskonstante=0;						//Zufallskonstante um die Hindernisse zufällig auf der X Achse in der jeweiligen Zone zu positionieren
	int yPosZufallskonstante=0;						//Zufallskonstante um die Hindernisse zufällig auf der Y Achse in der jeweiligen Zone zu positionieren
	int xPosBeginnZoneHinderniss1=325;				//Anfang der möglichen Position auf der X Achse für Hinderniss 1
	int xPosBeginnZoneHinderniss2=650;				//Anfang der möglichen Position auf der X Achse für Hinderniss 2
	int yPosBeginnZoneHinderniss1=0;				//Anfang der möglichen Position auf der Y Achse für Hinderniss 1
	int yPosBeginnZoneHinderniss2=365;				//Anfang der möglichen Position auf der Y Achse für Hinderniss 2
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
**	Funktion   			: Computersteuerung für Schläger 2
**
**	Rückgabe			: Nichts
**
**	Input				: Zeiger auf Schlaeger 2 und Zeiger auf die Anzeigeparameter.
**
**	Output				: Es wird direkt an die Adresse von Schläger 2 und der Anzeigeparameter geschrieben.
**
** 	Author				: kupfe1
**
******************************************************************************/
void ComputerSchlaeger2(SpielModus *ModusPtr, Schlaeger *Schlaeger2Ptr, Ball *SpielballPtr, AnzeigeParameter *UebergabeAnzeigePtr){


	//Variablen deklarieren
	int ySpeedPad;

	//Schnelligkeit der Schlägerbewegung in Abhängigkeit des Schwierigkeitsgrades
	ySpeedPad=3+3*(ModusPtr->Schwierigkeitsgrad);

	//Ist der Schläger unterhalb des Balles
	if((SpielballPtr->ypos <= Schlaeger2Ptr->yzonea+2) && (Schlaeger2Ptr->ypos>12)){
		Schlaeger2Auf(ySpeedPad, Schlaeger2Ptr, UebergabeAnzeigePtr);						//Schläger aufwärts bewegen
	}
	//Ist der Schläger oberhalb des Balles
	if((SpielballPtr->ypos >= Schlaeger2Ptr->yzonec-2) &&  (Schlaeger2Ptr->yzoned<750)){
		Schlaeger2Ab(ySpeedPad, Schlaeger2Ptr, UebergabeAnzeigePtr);						//Schläger abwärts bewegen
	}

	return;

}

/*****************************************************************************
**	Ende BerechneHindernissPos
*****************************************************************************/


