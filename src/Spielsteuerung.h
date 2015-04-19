/*
 * SpielHeader.h
 *
 *  Created on: 08.03.2015
 *      Author: Eliott Kupferschmied
 */

#ifndef SRC_STEUERUNGSHEADER_H_
#define SRC_STEUERUNGSHEADER_H_

#include"Header.h"


//Strukturdeklarationen

//Spielball
typedef struct{
	int xpos;					//Aktuelle Position x Achse
	int ypos;					//Aktuelle Position y Achse
	int xnull;					//Aktueller x Koordinate xnull Vektor
	int ynull;					//Aktueller y Koordinate xnull Vektor
	int vx;						//Aktuelle x Koordinate Geschwindigkeitsvektor
	int vy;						//Aktuelle y Koordinate Geschwindigkeitsvektor
	int Zeit;					//Zeitparameter für die Bewegungsleichung
	int GeschwindigkeitsFaktor;	//Faktor um die Geschwindigkeit zu erhöhen nach einer bestimmten Zeit
}Ball;

//Schläger
typedef struct {
	int xpos;					//Aktuelle Position x Achse
	int	ypos;					//Aktuelle Position y Achse
	int yzonea;					//Aktuelle Position Ende der Zone A y Achse
	int yzoneb;					//Aktuelle Position Ende der Zone B y Achse
	int yzonec;					//Aktuelle Position Ende der Zone C y Achse
	int yzoned;					//Aktuelle Position Ende des Schlägers
	int GoUp;					//Steuerflag auf
	int GoDown;					//Steuerflag ab
}Schlaeger;

//Hinderniss
typedef struct {
	int xpos;					//Aktuelle Position x Achse
	int	ypos;					//Aktuelle Position y Achse
	int ymax;					//Unteres Ende des Hindernisses
}Hindernis;

//Zeit
typedef struct {
    int StartTimeMin;    		//Startzeit in Minuten
    int StartTimeSec;			//Startzeit in Sekunden
    int EndTimeMin;				//Endzeit in Minuten
    int EndTimeSec;				//Endzeit in Sekunden
}Timestamp;



//Funktionsdeklarationen

//Spielsteuerungsfunktionen


//Ballfunktionen
int BallPos(Ball *PtrB,
			Schlaeger *Ptr1,
			Schlaeger *Ptr2,
			int *XposBallPtr,int *YposBallPtr,
			SpielModus *ModusPtr,
			Hindernis *Hinderniss1Ptr,
			Hindernis *Hinderniss2Ptr,
			int *Gewinner);
void StartPosBall1(Ball *SpielballPtr, SpielModus *ModusPtr, int *GewinnerPtr);
void GeschwBallErhoehen(int *StartzeitPtr, SpielModus *ModusPtr, Ball *Spielball1Ptr,Schlaeger *Schlaeger2Ptr,Schlaeger *Schlaeger1Ptr);
void StartPosBall2(Ball *SpielballPtr);

//Schlaegerfunktionen
void BerechneSchlaegerdimension(Schlaeger *Ptr1, Schlaeger *Ptr2, SpielModus *ModusPtr, AnzeigeParameter *PtrA);
int SchlaegerPos(Schlaeger *Ptr1, Schlaeger *Ptr2, AnzeigeParameter *PtrA,SpielModus *ModusPtr);
void ComputerSchlaeger2(SpielModus *ModusPtr, Schlaeger *Schlaeger2Ptr, Ball *SpielballPtr, AnzeigeParameter *UebergabeAnzeigePtr);

//Hindernissfunktionen
void BerechneHindernisPos(Hindernis *Hinderniss1Ptr, Hindernis *Hinderniss2Ptr, AnzeigeParameter *UebergabeAnzeigePtr);

//Punktefunktionen
void PunkteGUI(SpielModus *ModusPtr, int *GewinnerPtr, AnzeigeParameter *UebergabeAnzeigePtr );
void Punkte(int Modus, int *GewinnerPtr, PunkteHighscore *PunkteAnwaerterPtr, Timestamp *ZeitPtr);


#endif /* SRC_STEUERUNGSHEADER_H_ */
