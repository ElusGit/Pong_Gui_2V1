/*
 * header.h
 *
 *  Created on: 12.03.2015
 *      Author: Steve Allemann
 */

#ifndef HEADER_H_
#define HEADER_H_

//Strukturen

//Anzeigeparameter
typedef struct{
    int XPosBall1;              //Aktuelle Position Ball 1 x Achse
    int YPosBall1;              //Aktuelle Position Ball 1 y Achse
    int XPosBall2;              //Aktuelle Position Ball 2 x Achse
    int YPosBall2;              //Aktuelle Position Ball 2 y Achse
    int XPosPad1;              	//Aktuelle Position Schlaeger1 x Achse
    int YPosPad1;				//Aktuelle Position Schlaeger1 y Achse
    int XPosPad2;              	//Aktuelle Position Schlaeger2 x Achse
    int YPosPad2;				//Aktuelle Position Schlaeger2 y Achse
    int LaengePad;              //Laenge der beiden Schlaeger
    int Punkte1;                //Punkteanzeige Spieler1 GUI
    int Punkte2;				//Punkteanzeige Spieler2 GUI
    int XPosHindernis1;			//Aktuelle Position Hindernis 1 x Achse
    int YPosHindernis1;			//Aktuelle Position Hindernis 1 y Achse
    int XPosHindernis2;			//Aktuelle Position Hindernis 2 x Achse
    int YPosHindernis2;			//Aktuelle Position Hindernis 2 y Achse
}AnzeigeParameter;

//Punkte Highscore
typedef struct {
    int PunkteHighscore1;    	//Punkte Spieler1 fuer Highscore
    int PunkteHighscore2;     	//Punkte Spieler2 fuer Highscore
}PunkteHighscore;

//Spiel Modus
typedef struct {
    int SpielMod;    			//2: Levelspiel; 1: Einzelspiel
    int Schwierigkeitsgrad;     //1 bis 5
    int ZweiSpieler;			//0 bei Spiel gegen CPU
}SpielModus;

//Rangliste
typedef struct {
    int Position;    			//Position Rangliste
    char Spielername[15];		//Name Spieler
    int Punkte;					//Punktezahl Highscore
}Rangliste;

//Spieler Name
typedef struct {
    char Spieler1[15];    		//Name Spieler1
    char Spieler2[15];			//Name Spieler2
}SpielerName;

extern char SpielerName1[];
extern char SpielerName2[];


void OeffneGrafik();
void SchliesseGrafik();
void ZeichneSpielfeld();
void ZeichneHighscore();
void highscore();
void MenuVar();
void InfoVar();


// Deklaration der Funktionen Highscore
void RanglisteSpeichern (Rangliste *Highscore, char Dateiname[]);
int RanglistenEintragNeu ( int Spielerpunkte, Rangliste *Highscore );
void RanglisteNeuErstellen (int RangNeu, char SpielerName[], int Spielerpunkte, Rangliste *Highscore);
void RanglisteLoeschen (char Dateiname[]);
void RanglisteErstellen (PunkteHighscore *PunkteAnwaerterPtr, Rangliste *Highscore, SpielerName *SpielerNamenPtr, char Dateiname[]);
void RanglisteLesen (Rangliste *Highscore, char Dateiname[100]);

// Deklaration Spielsteuerung
void SpielSteuerung(SpielModus *ModusPtr,PunkteHighscore *PunkteAnwaerterPtr,SpielerName *SpielerNamePtr);
int Edit();

#endif /* HEADER_H_ */

