/*
 * Spielsteuerung.c
 *
 *  Created on: 12.03.2015
 *      Author: Michael
 */


/*
 * SpielSteuerung.c
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
**	File        : SpielSteuerung.c
**
**	Funktion   	: Hauptsteuermodul Spielsteuerung
**
**	Parameter	: Initialisationswerte...
**
**	Rückgabe	: Nichts
**
**	Input		: Zeiger auf den Spielmodus, Zeiger auf die Struktr der Punkte Anwärter
**
**	Output		: Welche Daten werden verändert...
**
** 	Author		: kupfe1/alles1
**
**	Version		: 1V07
**
**	History		: .....
**
**	Pendenzen	: Implementierung unterschiedliches Abprallverhalten wenn der Ball auf einen Schläger trifft, der in Bewegung ist.
**
**	Bugs		: Was geht noch nicht...
**
**	Tests		: Test von 1V00 am 10.03.2015
**				  Test von 1V01 am 12.03.2015
**				  Test von 1V02 am 16.03.2015
**				  Test von 1V03 am 18.03.2015
**				  Test von 1V04 am 22.03.2015
**				  Test von 1V05 am 23.03.2015
**				  Test von 1V06 am 01.04.2015
** 				  Test von 1V07 am 05.04.2015
**
*****************************************************************************
**
*/
/* imports */
#include "error.h"
#include "window.h"
#include "communication.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "Spielsteuerung.h"
#include "Header.h"

/**
*****************************************************************************
**	Projekt Pong
**	BTE 5052	FS2015
*****************************************************************************
**
**	Funktionsname   	: SpielSteuerung
**
**	Funktion   			: Hauptmodul der Spielsteuerung
**
**	Rückgabe			: Nichts
**
**	Input				: Zeiger auf die Spielparameter
**
**	Output				: Es wird direkt an die Adresse der Anzeigeparameter geschrieben.
**
** 	Author				: kupfe1/alles1
**
******************************************************************************/

//Hauptsteuerung
void SpielSteuerung(SpielModus *ModusPtr, PunkteHighscore *PunkteAnwaerterPtr,SpielerName *SpielernamePtr){

	//Struktur und deren Pointer definieren
	Ball Spielball1;								//Definieren des ersten Spielballs
	Ball *Spielball1Ptr;							//Zeiger für den Spielball 1
	Ball Spielball2;								//Definieren des zweiten Spielballs (ab Level 5 im Zweispielermodus)
	Ball *Spielball2Ptr;							//Zeiger für den Spielball 2 (ab Level 5 im Zweispielermodus)
	Schlaeger Schlaeger1;							//Definieren von Schlaeger1 (links)
	Schlaeger *Schlaeger1Ptr;						//Zeiger für Schlaeger1
	Schlaeger Schlaeger2;							//Definieren von Schlaeger2 (rechts)
	Schlaeger *Schlaeger2Ptr;						//Zeiger für Schlaeger2
	AnzeigeParameter UebergabeAnzeige;				//Definieren der Übergabeparameter für die Grafikfunktionen
	AnzeigeParameter *UebergabeAnzeigePtr;			//Definieren des Zeigers für die Übergabeparameter
	Hindernis Hinderniss1;							//Definieren von Hindernis 1 (links im Feld)
	Hindernis *Hinderniss1Ptr;						//Zeiger für Hindernis 1
	Hindernis Hinderniss2;							//Definieren von Hindernis 2 (r§echts im Feld)
	Hindernis *Hinderniss2Ptr;						//Zeiger für Hindernis 2
	Timestamp Zeit;									//Definieren der Zeitparameter
	Timestamp *ZeitPtr;								//Zeiger für Zeitparameter

	//Pointer initialisieren
	Spielball1Ptr=&Spielball1;
	Spielball2Ptr=&Spielball2;
	Schlaeger1Ptr=&Schlaeger1;
	Schlaeger2Ptr=&Schlaeger2;
	UebergabeAnzeigePtr=&UebergabeAnzeige;
	Hinderniss1Ptr=&Hinderniss1;
	Hinderniss2Ptr=&Hinderniss2;
	ZeitPtr = &Zeit;

	//Steuervariablen
	int Ball1ImSpiel;								//Abbruchflag wenn der Ball 1 ins Aus geht
	int Ball2ImSpiel;								//Abbruchflag wenn der Ball 2 ins Aus geht
	int EscGedrueckt;								//Abbruchflag wenn ESC gedrückt wird
	int Gewinner=0;									//Gewinner = 1 bei Sieg von Spieler 1, Gewinner = 2 bei Sieg von Spieler 2.
	int ZaehlerCountdown;							//Zählervariable für die Countdown Schleife
	int Startzeit;									//Startzeit des Spieles



	//Zeiger für Steuervariablen
	int *GewinnerPtr;								//Zeiger für die Gewinnervariable
	int *StartzeitPtr;								//Zeiger für die Startzeit

	//Zeiger für Steuervariablen initialisieren
	GewinnerPtr=&Gewinner;
	StartzeitPtr=&Startzeit;

	//Auswahl des Spielmodus
	if(ModusPtr->SpielMod==1){

		//Steuervariablen initialisieren
		Ball1ImSpiel=1;								//Abbruchflag wenn der Ball 1 ins Aus geht initialisieren
		Ball2ImSpiel=1;								//Abbruchflag wenn der Ball 2 ins Aus geht initialisieren
		EscGedrueckt=1;								//Abbruchflag wenn ESC gedrückt wird initialisieren



		//Schlägerdimension berechenen, Startpositionen definieren und Steuerflags setzen
		BerechneSchlaegerdimension(Schlaeger1Ptr, Schlaeger2Ptr, ModusPtr, UebergabeAnzeigePtr);

		//Startposition Ball berechnen
		StartPosBall1(Spielball1Ptr, ModusPtr, GewinnerPtr);

		//Wenn im Level 5 und im Zweispielermodus gespielt wird, zweiter Ball initialisieren
		if(ModusPtr->Schwierigkeitsgrad==5 && ModusPtr->ZweiSpieler==1){
		//Startparameter Ball	2
			StartPosBall2(Spielball2Ptr);
		}

		//Startzeit einlesen
		*StartzeitPtr=time(NULL);						//Startzeit setzen

		//Hindernissposition berechen falls im Level 4 oder 5 gespielt wird
		if(ModusPtr->Schwierigkeitsgrad>=4){
			BerechneHindernisPos(Hinderniss1Ptr, Hinderniss2Ptr,UebergabeAnzeigePtr);
		}

		//Countdown
		for(ZaehlerCountdown=1; ZaehlerCountdown<=3;ZaehlerCountdown++){
			InfoVar(ZaehlerCountdown);
			WaitMs(1000);
		}


			//Spielschleife
			while(Ball2ImSpiel !=0 && Ball1ImSpiel != 0 && EscGedrueckt !=0){

			//Vorfaktor der Geschwindigkeit erhöhen
			if(Spielball1Ptr->GeschwindigkeitsFaktor<8){							//Vorfaktor begrenzen um nicht eine zu hohe Geschwindigkeit zu erhalten
				GeschwBallErhoehen(StartzeitPtr,ModusPtr,Spielball1Ptr,Schlaeger2Ptr,Schlaeger1Ptr);
			}
			//printf("Geschwfak: %d\n",Spielball1Ptr->GeschwindigkeitsFaktor);

			//Ballposition von Ball 1 berechnen
			Ball1ImSpiel=BallPos(Spielball1Ptr,Schlaeger1Ptr,Schlaeger2Ptr, &(UebergabeAnzeigePtr->XPosBall1),&(UebergabeAnzeigePtr->YPosBall1), ModusPtr,Hinderniss1Ptr,Hinderniss2Ptr, GewinnerPtr);

			//Ballposition von Ball 2 berechnen
			if(ModusPtr->Schwierigkeitsgrad==5 && ModusPtr->ZweiSpieler==1){		//Nur im Zweispielermodus möglich
			Ball2ImSpiel=BallPos(Spielball2Ptr,Schlaeger1Ptr,Schlaeger2Ptr, &(UebergabeAnzeigePtr->XPosBall2),&(UebergabeAnzeigePtr->YPosBall2), ModusPtr,Hinderniss1Ptr,Hinderniss2Ptr, GewinnerPtr);
			}

			//Position Schläger 1 und 2 berechnen
			EscGedrueckt=SchlaegerPos(Schlaeger1Ptr,Schlaeger2Ptr,UebergabeAnzeigePtr, ModusPtr);

			//Position Schläger 2 bei Spiel gegen den Computer
			if(ModusPtr->ZweiSpieler==0){
				ComputerSchlaeger2(ModusPtr,Schlaeger2Ptr,Spielball1Ptr,UebergabeAnzeigePtr);
			}

			//Bild Zeichnen
			ZeichneSpielfeld(UebergabeAnzeigePtr,ModusPtr, SpielernamePtr);

			//Warten
			WaitMs(10);

			}

	}

	//Levelmodus
	else
	{
		//Steuervariablen initialisieren
		EscGedrueckt=1;								//Abbruchflag wenn ESC gedrückt wird

		//Punkte GUI initialisieren
		PunkteGUI(ModusPtr, GewinnerPtr, UebergabeAnzeigePtr);

		//Punkte Highscore initialisieren
		Punkte(1, GewinnerPtr, PunkteAnwaerterPtr, ZeitPtr);

		//Levelschleife
		while(ModusPtr->Schwierigkeitsgrad<6 && EscGedrueckt != 0){

			//Steuervariablen initialisieren
			Ball1ImSpiel=1;							//Abbruchflag wenn der Ball ins Aus geht
			Ball2ImSpiel=1;							//Abbruchflag wenn der Ball 2 ins Aus geht initialisieren


			//Schlägerdimension berechenen, Startpositionen definieren und Steuerflags setzen
			BerechneSchlaegerdimension(Schlaeger1Ptr, Schlaeger2Ptr, ModusPtr, UebergabeAnzeigePtr);

			//Hindernissposition berechen falls im Level 4 oder 5 gespielt wird
			if(ModusPtr->Schwierigkeitsgrad>=4){
				BerechneHindernisPos(Hinderniss1Ptr, Hinderniss2Ptr,UebergabeAnzeigePtr);
			}

			//Startposition Ball 1 berechnen
			StartPosBall1(Spielball1Ptr, ModusPtr, GewinnerPtr);

			//Wenn im Level 5 und im Zweispielermodus gespielt wird, zweiter Ball initialisieren
			if(ModusPtr->Schwierigkeitsgrad==5 && ModusPtr->ZweiSpieler==1){
			//Startparameter Ball	2
			StartPosBall2(Spielball2Ptr);
			}

			//Startzeit einlesen
			*StartzeitPtr=time(NULL);							//Startzeit setzen

			//Countdown
			for(ZaehlerCountdown=1; ZaehlerCountdown<=3;ZaehlerCountdown++){
				InfoVar(ZaehlerCountdown);
				WaitMs(1000);
			}

				//Spielschleife
				while(Ball2ImSpiel !=0 && Ball1ImSpiel != 0 && EscGedrueckt !=0){

				//Vorfaktor der Geschwindigkeit erhöhen
				if(Spielball1Ptr->GeschwindigkeitsFaktor<8){						//Vorfaktor begrenzen um nicht eine zu hohe Geschwindigkeit zu erhalten
					GeschwBallErhoehen(StartzeitPtr,ModusPtr,Spielball1Ptr,Schlaeger2Ptr,Schlaeger1Ptr);
				}
				//printf("Geschwfak: %d\n",Spielball1Ptr->GeschwindigkeitsFaktor);

				//Ballposition berechnen
				Ball1ImSpiel=BallPos(Spielball1Ptr,Schlaeger1Ptr,Schlaeger2Ptr,  &(UebergabeAnzeigePtr->XPosBall1), &(UebergabeAnzeigePtr->YPosBall1), ModusPtr, Hinderniss1Ptr, Hinderniss2Ptr, GewinnerPtr);

				//Ballposition von Ball 2 berechnen
				if(ModusPtr->Schwierigkeitsgrad==5 && ModusPtr->ZweiSpieler==1){	//Nur im Zweispielermodus möglich
				Ball2ImSpiel=BallPos(Spielball2Ptr,Schlaeger1Ptr,Schlaeger2Ptr, &(UebergabeAnzeigePtr->XPosBall2),&(UebergabeAnzeigePtr->YPosBall2), ModusPtr,Hinderniss1Ptr,Hinderniss2Ptr, GewinnerPtr);
				}

				//Position Schläger 1 und 2 berechnen
				EscGedrueckt=SchlaegerPos(Schlaeger1Ptr,Schlaeger2Ptr,UebergabeAnzeigePtr,ModusPtr);

				//Position Schläger 2 bei Spiel gegen den Computer
				if(ModusPtr->ZweiSpieler==0){
					ComputerSchlaeger2(ModusPtr,Schlaeger2Ptr,Spielball1Ptr,UebergabeAnzeigePtr);
				}

				//Bild Zeichnen (provisorisch)
				ZeichneSpielfeld(UebergabeAnzeigePtr,ModusPtr,SpielernamePtr);


				//Level Anzeigen (Provisorisch)
/*				if(ModusPtr->Schwierigkeitsgrad==1){
				DrawTextXY(1300,600, COL_GREEN, "Level 1");
				}
				if(ModusPtr->Schwierigkeitsgrad==2){
				DrawTextXY(1300,600, COL_GREEN, "Level 2");
				}
				if(ModusPtr->Schwierigkeitsgrad==3){
				DrawTextXY(1300,600, COL_GREEN, "Level 3");
				}
				if(ModusPtr->Schwierigkeitsgrad==4){
				DrawTextXY(1300,600, COL_GREEN, "Level 4");
				}

				if(ModusPtr->Schwierigkeitsgrad==5){
				DrawTextXY(1300,600, COL_GREEN, "Level 5");
				}*/

				//Warten
				WaitMs(10);

				}

			//Level inkrementieren
			ModusPtr->Schwierigkeitsgrad++;

			//PunkteGUI anpassen
			PunkteGUI(ModusPtr, GewinnerPtr, UebergabeAnzeigePtr);

			//Highscore Punkte berechnen
			Punkte(2, GewinnerPtr, PunkteAnwaerterPtr, ZeitPtr);
		}
	}
	return;
}
/*
**
*****************************************************************************
**	Ende
*****************************************************************************
*/


