/*
 * highscore.c
 *
 *  Created on: 15.03.2015
 *      Author: Simon
 */
/**
*****************************************************************************
**	Projekt Pong
**	BTE 5052	FS2015
*****************************************************************************
**
**	File        : highscore.c
**
**	Funktion   	: Highscore Modul
**
**	Parameter	: Initialisationswerte...
**
**	Rückgabe	: Rangliste mit Rang, Namen und Punkte
**
**	Input		: Punktezahlen Spieler 1 und Spieler 2
**
**	Output		: Welche Daten werden verändert...
**
** 	Author		: sches8
**
**	Version		: 1V01
**
**	History		: 1V01, 	11.03.2015 	Modul erstellt
**				  1V02,		15.03.2015 	erste Codeversion erstellt
**				  1V03,		16.03.2025	Struktur definiert
**				  1V04,		19.03.2015	Struktur definiert
**				  1V05,		21.03.2015 	Funktionen definiert
**				  1V06,		22.03.2015 	Funktion RanglisteLesen, RanglisteSpeichern
**				  						1. Version erstellt
**				  1V07,		28.03.2015 	Funktion RanglistenEintragNeu, RanglisteNeuErstellen,
**				  						RanglisteLoeschen 1. Version erstellt
**				  1V08,		30.03.2015	Funktionen überarbeitet
**				  1V09,		01.04.2015
**
**	Pendenzen	: rechnen, punktübergabe (strukur hier definiert (bzw. header von highscore)
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
#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include "window.h"
#include <string.h>





	// Funktion Lesen der Rangliste
		void RanglisteLesen (Rangliste *Highscore, char Dateiname[100]){
			int i=0;

			FILE *DateiPtr;
			DateiPtr = fopen(Dateiname, "r");

			if (DateiPtr == NULL) {
				printf("Error - Fehler beim oeffnen der Ranglisten Datei %s ! \n", Dateiname);
			}
			else {
					while (!feof (DateiPtr)) {
						// Lesen
						fscanf(DateiPtr, "%3d %15s %6d \n",
										   &(Highscore[i].Position),
										   Highscore[i].Spielername,
										   &(Highscore[i].Punkte));
						i++;
					};
					// bis ans Ende der Datei
					fclose(DateiPtr);
				}
		}




	// Hauptfunktion
	// Ranglisteneintrag evaluieren und Rang 1-5 zuweisen
	void RanglisteErstellen (PunkteHighscore *PunkteAnwaerterPtr, Rangliste *Highscore, SpielerName *SpielerNamenPtr, char Dateiname[]){
		int RangNeu1=0;
		int RangNeu2=0;
		int SpielerAP[2]; // Array für SpielerAnwaerterPunkte
		SpielerAP[0]= PunkteAnwaerterPtr->PunkteHighscore1;
		printf("SpielerAP[0] = %d\n", SpielerAP[0]);
		SpielerAP[1]= PunkteAnwaerterPtr->PunkteHighscore2;
		printf("SpielerAP[1] = %d\n", SpielerAP[1]);
		char SpielerName1[16];
		strncpy( SpielerName1, SpielerNamenPtr->Spieler1, 15);
		printf("SpielerName1 = %s\n", SpielerName1);
		char SpielerName2[16];
		strncpy( SpielerName2, SpielerNamenPtr->Spieler2, 15);
		printf("SpielerName12 = %s\n", SpielerName2);

		RangNeu1 = RanglistenEintragNeu ( SpielerAP[0], Highscore );
		printf("RangNeu1 = %d\n", RangNeu1);

			if (RangNeu1 !=0 ){
				RanglisteNeuErstellen (RangNeu1,
											SpielerName1,
											SpielerAP[0],
											Highscore);

				RanglisteSpeichern (Highscore, Dateiname);
				RanglisteLesen(Highscore, Dateiname);

				//ZeichneHighscore(Highscore);		// Rangliste anzeigen (aktualisieren)

			}


		RangNeu2 = RanglistenEintragNeu ( SpielerAP[1], Highscore );
		printf("RangNeu2 = %d\n", RangNeu2);
			if (RangNeu2 !=0 ){

					RanglisteNeuErstellen (RangNeu2,
												SpielerName2,
												SpielerAP[1],
												Highscore);

					RanglisteSpeichern (Highscore, Dateiname);
					RanglisteLesen(Highscore, Dateiname);


					//ZeichneHighscore(Highscore);		// Rangliste anzeigen (aktualisieren)
				}


	}





	// Unterfunktionen
	// Funktion Spielerpunkte auswerten ob es einen Ranglisteneintrag gibt und wenn ja, an welcher Position
		int RanglistenEintragNeu ( int Spielerpunkte, Rangliste *Highscore ){
			// Variabel die den Spielerpunkten einen Rang zuordnet
			int i=0; 						// Zählvariabel für Schlaufe
			int RangNeu=0;
			// Schleife für Rangeinordnung der neuen Spielerpunkte
			for (i=5; i>0; i--){
				if (Spielerpunkte > (Highscore[i-1].Punkte)) {
					if(i==5){
						RangNeu=6;
					}
					RangNeu = (RangNeu-1);
				}
			}
			printf( "RangNeu = %d \n", RangNeu);
			return RangNeu;				// Rückgabe des neuen Rangs: 1-5 Ranglisteneintrag
										//							 0	 kein Ranglisteneintrag

		}





	// Funktion Rangliste aktualisieren mit neuem Ranglisteneintrag
		void RanglisteNeuErstellen (int RangNeu, char SpielerName[], int Spielerpunkte, Rangliste *Highscore){
			int i;
			printf("Beginn der Ranglistenerstellung vor Schlaufe");
			for (i=4; i>(RangNeu-1); i--){
				printf("in schlaufe, start");
				 strncpy(Highscore[i].Spielername, Highscore[i-1].Spielername, 15 );
				 Highscore[i].Punkte = Highscore[i-1].Punkte;

				printf( "Schleifendurchgangn %d, Pos: %1d \t name: %15s \t Pkt: %7d \n", i, Highscore[i].Position, Highscore[i].Spielername, Highscore[i].Punkte);

				 }

			strncpy(Highscore[RangNeu-1].Spielername, SpielerName, 15);
			Highscore[RangNeu-1].Punkte = Spielerpunkte;
			printf("ende Ranglistenerstellung");
		}







	// Funktion Speichern der Rangliste
		void RanglisteSpeichern (Rangliste *Highscore, char Dateiname[]){
			int i=0;
			FILE *DateiPtr;
			DateiPtr = fopen(Dateiname,"w");

			if (DateiPtr == NULL) {
				printf("Error - Fehler beim Öffnen der Ranglisten Datei %s !\n", Dateiname);
			}
			else {
					for(i = 1 ; i<6; i++) {
						fprintf(DateiPtr, "%3d \t %15s \t %6d \n",
								Highscore[i-1].Position,
								Highscore[i-1].Spielername,
								Highscore[i-1].Punkte);
					}
					fclose(DateiPtr);
				}
				fflush(stdout);

			//fclose(DateiPtr);
		}






	// Funktion Loeschen der Rangliste
		void RanglisteLoeschen (char Dateiname[]){
			int i=0;

			FILE *DateiPtr;
			DateiPtr = fopen(Dateiname,"w");

			if (DateiPtr == NULL) {
				printf("Error - Fehler beim Öffnen der Ranglisten Datei %s !\n", Dateiname);
			}
			else {
					for(i = 0 ; i < 5; i++) {
						fprintf(DateiPtr, "%3d %15s %6d \n", i+1, "-           " , 0 );
					}
					fclose(DateiPtr);
				}
			fflush(stdout);
		}

