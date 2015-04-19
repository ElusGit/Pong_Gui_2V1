/*
 * main.c
 *
 *  Created on: 12.03.2015
 *      Author: Simon
 */
/**
*****************************************************************************
**	Projekt Pong
**	BTE 5052	FS2015
*****************************************************************************
**
**	File        : main.c
**
**	Funktion   	: Menu State Machine
**
**	Parameter	: Initialisationswerte...
**
**	Rückgabe	: nichts
**
**	Input		: Tastatur stdin
**
**	Output		: Highscore, Spielmodus,
**
** 	Author		: sches8
**
**	Version		: 0V08
**
**	History		: 0V01,  	12.03.2015	Modul erstellt
**				  0V02,		16.03.2015	erste Codeversion erstellt
**				  0V03,		19.03.2015	Switch Anweisung definiert
**				  0V04,		21.03.2015	Switch Anweisung für Modus ohne Computer erstellt
**				  0V05,		23.03.2015	Switch Anweisung überarbeitet
**				  0V06,		29.03.2015	Funktionsaufruf für Spielsteuerung eingebaut
**				  0V07,		30.03.2015	Funktionsaufrufe in die Switch Anweisung eingebaut
**				  0V08,		01.04.2015	Neue Definition von MenuVar, Edit und SpielModus
**				  0V09,
**				  0V10,
**				  0V12,		08.04.2015
**
**	Pendenzen	: Was gibts noch zu tun...
**
**	Bugs		: Was geht noch nicht...
**
**	Tests		: Was wurde wann getestet...
**
**
*****************************************************************************
**
*/

/* imports */
#include "error.h"
#include "Header.h"
#include <stdio.h>
#include <stdlib.h>
#include "window.h"
#include "Spielsteuerung.h"
#include <string.h>


int gfxmain(int argc, char* argv []){


	// Strukturen definieren

	// Spielmodus
		SpielModus Modus;
		SpielModus *ModusPtr;
		ModusPtr=&Modus;
	//Level setzen provisorisch


	// Struktur der Rangliste definieren (Klasse erstellt)
		Rangliste Highscore[5] = {
									[0].Position = 1,
									[0].Spielername="Schafs1",
									[0].Punkte=1000,
									[1].Position = 2,
									[1].Spielername="00",
									[1].Punkte=500,
									[2].Position = 3,
									[2].Spielername="kupfe",
									[2].Punkte=300,
									[3].Position = 4,
									[3].Spielername="steve",
									[3].Punkte=200,
									[4].Position = 5,
									[4].Spielername="asdf123",
									[4].Punkte=10,
				   				 	};
		Rangliste *HighscorePtr;
		HighscorePtr = &Highscore;

	// 	Variablen deklarieren

		char Dateiname[100] = "Rangliste.txt";	// Datei Rangliste Highscore

	// Struktur für Spielernamen definieren
		SpielerName SpielerNamen;
		SpielerName *SpielerNamenPtr;
		SpielerNamenPtr = &SpielerNamen;


	// Struktur für neue Punktestaende
		PunkteHighscore PunkteAnwaerter;
		PunkteHighscore *PunkteAnwaerterPtr = &PunkteAnwaerter;


/*

// TEST HIGHSCORE
		int i;
		PunkteAnwaerterPtr->PunkteHighscore1=5000;
		PunkteAnwaerterPtr->PunkteHighscore2=5001;
		strncpy(SpielerNamenPtr->Spieler1, "test1",15);
		strncpy(SpielerNamenPtr->Spieler2, "test2", 15);
		int a = 502;
		int b = 2000;
		char name[15] = "anton3";
		int r=0;
		//for(i=0; i<5; i++){
		//printf( "%1d \t %15s \t %7d \n", Highscore[i].Position, Highscore[i].Spielername, Highscore[i].Punkte);
		//}
		//RanglisteSpeichern (HighscorePtr, Dateiname);
		//RanglisteLesen (HighscorePtr, Dateiname);
		//for(i=0; i<5; i++){
		//printf( "%1d \t %15s \t %7d \n", Highscore[i].Position, Highscore[i].Spielername, Highscore[i].Punkte);
		//}
		r=RanglistenEintragNeu ( a, HighscorePtr );
		//RanglisteNeuErstellen ( r, name, a, HighscorePtr);
		//r=RanglistenEintragNeu( a,HighscorePtr );
		RanglisteErstellen (PunkteAnwaerterPtr, HighscorePtr, SpielerNamenPtr, Dateiname);
		//RanglisteSpeichern (HighscorePtr, Dateiname);
		//RanglisteLoeschen (Dateiname);
		//RanglisteLesen (HighscorePtr, Dateiname);
		for(i=0; i<5; i++){
		printf( "%1d \t %15s \t %7d \n", Highscore[i].Position, Highscore[i].Spielername, Highscore[i].Punkte);
		}
		//RanglisteSpeichern (HighscorePtr, Dateiname);
		//RanglisteLesen (HighscorePtr, Dateiname);
		//for(i=0; i<5; i++){
		//printf( "%1d \t %15s \t %7d \n", Highscore[i].Position, Highscore[i].Spielername, Highscore[i].Punkte);
		//}
		//RanglisteErstellen (PunkteAnwaerterPtr, HighscorePtr, SpielerNamenPtr, Dateiname);
		//RanglisteSpeichern (HighscorePtr, Dateiname);

*/



	// Deklaration der Variablen
	// Textdateiname für Highscore Speicher

	// Variablendeklaration für das Menü
		int MenuEingabe;							//Variable um die Tastendrücke zu verwerten
		int Abbruch1=1;								//Abbruchflag für Untermenu im Case 1
		int Abbruch2=1; 							//Abbruchflag für Untermenu im Case 2
		int Abbruch3=1;								//Abbruchflag für Untermenu im Case 3
		int Abbruch4=1;								//Abbruchflag für Auswahl Schwierigkeitsgrad
		int AbbruchHauptmenu=1;						//Abbruchflag für das Hauptmenu

	int Rueckgabe;	// Rückgabe für die Funktionsauswertung im Menu
	char Name1Buffer[]="Spieler 1";
	char Name2Buffer[]="Computer";

	// Funktionen
	// Schwierigkeitsgrad-Auswahl Funktion
	strncpy(SpielerNamenPtr->Spieler1,Name1Buffer,15);
	strncpy(SpielerNamenPtr->Spieler2,Name2Buffer,15);

	int SchwierigkeitsgradAuswahl(SpielModus *ModusPtr){
				//int Rueckgabe=0;	// lokale Variabel für Rückgabe initialisieren

				Abbruch4 = 1;
				while(Abbruch4 != 0){
					MenuVar(4); 	// Bild Schwierigkeitsgradauswahl-Menü zeichnen
					MenuEingabe = GetKeyEvent();

						switch(MenuEingabe){		// Switch Auswahl für Schwierigkeitsgrad 1-5
								case '1': 	ModusPtr->Schwierigkeitsgrad=1;
											return 1;
											break;
								case '2': 	ModusPtr->Schwierigkeitsgrad=2;
											return 1;
											break;
								case '3':	ModusPtr->Schwierigkeitsgrad=3;
											return 1;
											break;
								case '4': 	ModusPtr->Schwierigkeitsgrad=4;
											return 1;
											break;
								case '5': 	ModusPtr->Schwierigkeitsgrad=5;
											return 1;
											break;
								//  Zurück ins Hauptmenu
								case '0':	Abbruch4=0;												//Abbruchflag für Untermenu im Case 1 setzen
											return 0;
											break;

								default: 	break;
								case W_KEY_ESCAPE:  printf("case ESC in Schwierigkeitsgrad Menu\n");
													Abbruch4=0;
													break;
						}
				}
				return 0; 			// Rueckgabe 1: Schwierigkeitsgrad gewählt, 0: Retour ins vorherige Menu
		}							// Funktion Schwierigkeitsgradauswahl Ende






	// Fenster Öffnen
		OeffneGrafik();

	// Highscore laden
		//RanglisteLesen (HighscorePtr, Dateiname);
		//ZeichneHighscore(HighscorePtr);

	// Schleife State Machine der Menustruktur
		while(AbbruchHauptmenu != 0){	//Solange im Hauptmenu nicht geschlossen wird (ESC-Taste)
			MenuVar(1);		//Hauptmenu zeichnen


			MenuEingabe = GetKeyEvent();		// Tastendruck auslesen
			printf("%d\n",MenuEingabe);

			// State Machine der Menustruktur

			switch(MenuEingabe){
				// Hauptmenustruktur
				// 1 Levelmodus
				case '1': printf("case 1 levelmodus\n");
							//Abbruchflag für Untermenu initialisieren
							Abbruch1=1;
							while(Abbruch1 != 0 ){
								MenuVar(2);						// Bild Levelmodus-Menü zeichnen
								MenuEingabe = GetKeyEvent();	// Tastendruck auslesen
								switch(MenuEingabe){			// Switch Auswahl Levelmodus-Menü
										// 1.1 Levelmodus gegen Computer
										case '1':	//Spielparameter setzenstrncpy(SpielerNamenPtr->Spieler2,Name2Buffer,15);
													ModusPtr->Schwierigkeitsgrad=1;
													ModusPtr->SpielMod=2;
													ModusPtr->ZweiSpieler=0;
													SpielSteuerung(ModusPtr, PunkteAnwaerterPtr, SpielerNamenPtr);
													break;


										// 1.2 Levelmodus Zweispieler
										case '2':	// Spielernamen eingeben
													Rueckgabe=Edit(SpielerNamenPtr);
													if ( Rueckgabe > 0) {
													//Spielparameter setzen
													ModusPtr->Schwierigkeitsgrad=1;
													ModusPtr->SpielMod=2;
													ModusPtr->ZweiSpieler=1;
													//Punkte initialisieren
													PunkteAnwaerterPtr->PunkteHighscore1=0;
													PunkteAnwaerterPtr->PunkteHighscore2=0;
													SpielSteuerung(ModusPtr, PunkteAnwaerterPtr, SpielerNamenPtr);			 // Spiel starten
													} // if Edit Ende
													//RanglisteErstellen (PunkteAnwaerterPtr, HighscorePtr, SpielerNamenPtr, Dateiname);
													//RanglisteSpeichern(HighscorePtr, Dateiname);
													//ZeichneHighscore(HighscorePtr);
													//printf("Spieler 1: %d\n", PunkteAnwaerterPtr->PunkteHighscore1);
													//printf("Spieler 2: %d\n", PunkteAnwaerterPtr->PunkteHighscore2);
													//Spielernamen zurücksetzen
													strncpy(SpielerNamenPtr->Spieler1,Name1Buffer,15);
													strncpy(SpielerNamenPtr->Spieler2,Name2Buffer,15);
													break;

										// 1.0 zurück ins Hauptmenu
										case '0':			Abbruch1=0;		//Abbruchflag für Untermenu im Case 1 setzen
															break;
										case W_KEY_ESCAPE:  Abbruch1=0;
															break;
										default: break;
								}
							}

							break;			//Break Case 1

				// 2 Einzelspiel
				case '2': 	Abbruch2=1;	//Abbruchflag für Untermenu initialisieren
							while(Abbruch2 != 0){
								MenuVar(3);	// Bild Einzelspiel-Menü zeichnen
								MenuEingabe = GetKeyEvent();	// Tastendruck auslesen
								switch(MenuEingabe){	// Switch Auswahl Einzelspiel Menü
										// 2.1 Einzelspiel gegen den Computer
										case '1':	ModusPtr->SpielMod=1;
													ModusPtr->ZweiSpieler=0;
													Rueckgabe=SchwierigkeitsgradAuswahl(ModusPtr);

													if (Rueckgabe > 0) {
													SpielSteuerung(ModusPtr, PunkteAnwaerterPtr, SpielerNamenPtr);
													}

													break;

										// 2.2 Einzelspiel Zweispieler
										case '2':	// Spielernamen Eingabe
													Rueckgabe=Edit(SpielerNamenPtr);
													if ( Rueckgabe > 0) {
													ModusPtr->SpielMod=1;
													ModusPtr->ZweiSpieler=1;
													Rueckgabe=SchwierigkeitsgradAuswahl(ModusPtr);
													if ( Rueckgabe > 0) {
													SpielSteuerung(ModusPtr, PunkteAnwaerterPtr, SpielerNamenPtr);
													// SpielerName zurücksetzen
													strncpy(SpielerNamenPtr->Spieler1,Name1Buffer,15);
													strncpy(SpielerNamenPtr->Spieler2,Name2Buffer,15);
													} // if Schwierigkeitsgrad Ende
													} // if Edit Ende
													break;

										// 2.0 Zurück ins Hauptmenu
										case '0':			Abbruch2=0;												//Abbruchflag für Untermenu im Case 1 setzen
															break;
										case W_KEY_ESCAPE:  Abbruch2=0;
															break;
										default: break;
								}
							}
							break;


				// 3 Highscore
				case '3':	MenuVar(5); // Highscore-menu
							//Abbruchflag für Untermenu initialisieren
							Abbruch3=1;
							while(Abbruch3 != 0){
								MenuEingabe = GetKeyEvent();
								// Auswahl Levelmodus
								switch(MenuEingabe){
										//Einträge löschen
										case '1': 			//RanglisteLoeschen (Dateiname);

															//RanglisteLesen (HighscorePtr,Dateiname);

															//ZeichneHighscore(HighscorePtr);
															break;
										//Beenden
										case '0':			Abbruch3=0;			//Abbruchflag für Untermenu im Case 1 setzen
															break;
										case W_KEY_ESCAPE:  Abbruch3=0;
															break;
										default: break;
								}

							}
							break; // Break Case 3


				//0 Beenden
				//case '0': 		AbbruchHauptmenu=0;
				//					break;
				case W_KEY_ESCAPE:	AbbruchHauptmenu=0;										//Wird die Esc Taste im Hauptmenu gedrückt, Abbruchflag auf 0 setzen
							break;

				default: 	break;
			}

		}


	//Testprint Highscore
		//printf("Spieler 1: %d\n", PunkteAnwaerterPtr->PunkteHighscore1);
		//printf("Spieler 2: %d\n", PunkteAnwaerterPtr->PunkteHighscore2);

		//Schliessen des Fensters
		SchliesseGrafik();


		return 0;
}


