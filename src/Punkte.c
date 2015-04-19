
/*
 * Punkte.c
 *
 *  Created on: 23.03.2015
 *      Author: Eliott Kupferschmied
 */
/**
*****************************************************************************
**	Projekt Pong
**	BTE 5052	FS2015
*****************************************************************************
**
**	File        : Punkte.c
**
**	Funktion   	: Punkteberechnung
**
**	Parameter	: Initialisationswerte...
**
** 	Author		: kupfe1/alles1
**
**	Version		: 1V01
**
**	History		: .....
**
**	Pendenzen	: keine
**
**	Bugs		: keine bekannte Fehler
**
**	Tests		: Test von 1V01 am 23.03.2015
**
**
******************************************************************************/

#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include "Header.h"
#include "Spielsteuerung.h"


/**
*****************************************************************************
**	Projekt Pong
**	BTE 5052	FS2015
*****************************************************************************
**
**	Funktionsname   	: ...
**
**	Funktion   			: ..
**
**	Rückgabe			: ...
**
**	Input				: ....
**
**	Output				: ....
**
** 	Author				: alles1
**
******************************************************************************/

void PunkteGUI(SpielModus *ModusPtr, int *GewinnerPtr, AnzeigeParameter *UebergabeAnzeigePtr){

		//Struktur fuer Punkte GUI
/*		AnzeigeParameter PunkteGUI;
		AnzeigeParameter *PunkteGUIPtr;

		//Pointer initialisieren
		PunkteGUIPtr = &PunkteGUI;*/

		if(ModusPtr->Schwierigkeitsgrad == 1){
			//Punktestaende nullsetzen
			UebergabeAnzeigePtr->Punkte1=0;
			UebergabeAnzeigePtr->Punkte2=0;
		}
		else{

		switch(*GewinnerPtr){
			case 1: UebergabeAnzeigePtr->Punkte1 ++;	//Punkte von Spieler1 um 1 inkrementieren
					break;
			case 2: UebergabeAnzeigePtr->Punkte2 ++;	//Punkte von Spieler2 um 1 inkrementieren
					break;
			default: break;
			}
		}

	return;
}

/**
*****************************************************************************
**	Ende PunkteGUI
*****************************************************************************/
/**
*****************************************************************************
**	Projekt Pong
**	BTE 5052	FS2015
*****************************************************************************
**
**	Funktionsname   	: Punkte
**
**	Funktion   			: Punkteberechnung für den Highscore
**
**	Rückgabe			: ...
**
**	Input				: ....
**
**	Output				: ....
**
** 	Author				: alles1
**
******************************************************************************/


void Punkte(int Modus, int *GewinnerPtr, PunkteHighscore *PunkteAnwaerterPtr, Timestamp *ZeitPtr){

	//Struktur  time um Systemzeit auslesen zu koennen
	time_t t;
	struct tm * ts;

	t = time(NULL);
	ts = localtime(&t);

	//Variablen initialisieren
	int DiffMin, DiffSec, DifferenceSec;
	int Level;

	if(Modus == 1){									//Modus 1: Startzeit setzten und Level auf 1 setzten
			Level = 1;
			PunkteAnwaerterPtr->PunkteHighscore1 = 0;
			PunkteAnwaerterPtr->PunkteHighscore2 = 0;

			ZeitPtr->StartTimeMin = (ts->tm_min);		//Startzeit in Minuten
			ZeitPtr->StartTimeSec = (ts->tm_sec);		//Startzeit in Sekunden
	}


	if(Modus == 2){									//Modus 2: Endzeit setzen, Punkte fuer Highscore berechnen

		ZeitPtr->EndTimeMin = (ts->tm_min);			//Endzeit in Minuten
		ZeitPtr->EndTimeSec = (ts->tm_sec);			//Endzeit in Sekunden

		//Differenz in Sekunden berechnen
		DiffMin = ((ZeitPtr->EndTimeMin)*60)-((ZeitPtr->StartTimeMin)*60);
		DiffSec = (60-(ZeitPtr->StartTimeSec))+ZeitPtr->EndTimeSec;

		DifferenceSec = DiffMin+DiffSec;	//Fehler: Differenz betraegt 60, wenn keine Differenz besteht (real 0 sek.)



		//Gewinner abfragen und entsprechend Punkte berechnen
		switch(*GewinnerPtr){

		case 1: PunkteAnwaerterPtr->PunkteHighscore1 += (Level*100000)/(DifferenceSec);
				break;
		case 2: PunkteAnwaerterPtr->PunkteHighscore2 += (Level*100000)/(DifferenceSec);
				break;
		default: break;
		}

		//Level inkrementiren und neue Startzeit erfassen
		Level ++;

		ZeitPtr->StartTimeMin = ts->tm_min;		//Startzeit in Minuten
		ZeitPtr->StartTimeSec = ts->tm_sec;		//Startzeit in Sekunden

	}
	return;
}

