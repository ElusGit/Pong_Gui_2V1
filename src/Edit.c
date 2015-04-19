/**
*****************************************************************************
**	Projekt Pong
**	BTE 5052	FS2015
*****************************************************************************
**
**	File        	: Edit.c
**
**	Funktion   	: Grundmodul für das Einlesen der Spielernamen
**
**	Parameter	: struct SpielerNamen
**
**	Rückgabe	: Returnwert 1 für erfolgreich, 0 für abbruch
**
**	Input		:
**
**	Output		:
**
** 	Author		: Michael Schmutz
**
**	Version		: 0.4
**
**	History		: 	27.03.2015: Erstellt
**					29.03.2015:	Löschfunktion implementiert
**					02.04.2015: Test mit Main, anpassungen (Returnwerte)
**					10.04.2015: Löschfunktion zeichenweise angepasst
**
**	Pendenzen	: -
**
**	Bugs		: -
**
**	Tests		:
**
**
*****************************************************************************
**/
#include "error.h"
#include "window.h"
#include "Spielsteuerung.h"
#include "Header.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

int Edit(SpielerName *Spieler)
{

	// Buffervariablen definieren

	char spielername1[15]; //lokaler string name1
	char spielername2[15];	// Lokaler string name2
	char spielerbuffer[15];	// Name buffer fuer loeschfunktion

	int key;
	int i=0;			//Countervariable



	// Buffervariablen "leeren"

	strncpy(spielername1,"              ",15);
	strncpy(spielername2,"              ",15);

	// Grundbild zeichen

	DrawFilledRectangle(0, 0, 1300, 750, COL_BLACK,1) ;		// Hintergrund
	DrawEmptyRectangle(0, 0, 1300, 750, COL_GREEN, 4) ;		// Umrandung
	DrawTextXY(550,51,COL_GREEN,"Level-Modus");
	DrawEmptyRectangle(150,90,1000,50, COL_GREEN, 2) ;
	DrawTextXY(350,130,COL_GREEN,"Name von Spieler 1 eingeben");
	DrawTextXY(550,200,COL_GREEN,spielername1);
	DrawEmptyRectangle(150, 440,1000,50, COL_GREEN, 2) ;
	DrawTextXY(550,480,COL_GREEN,"0: Beenden");
	// Spieler 1

	// Durchlauf 14 mal, bis das array voll ist

	for(i=0;i<14;i++)
	{
		key=GetKeyPress(); // Tastendruck auslesen

		if((key>=32) && (key<=128)) // Nur Gross- und Kleinbuchstaben beruecksichtigen
		{
			// Hintergrundbild aktualisieren
			DrawFilledRectangle(0, 0, 1300, 750, COL_BLACK,1) ;
			DrawEmptyRectangle(0, 0, 1300, 750, COL_GREEN, 4) ;
			DrawTextXY(550,51,COL_GREEN,"Level-Modus");
			DrawEmptyRectangle(150,90,1000,50, COL_GREEN, 2) ;
			DrawTextXY(350,130,COL_GREEN,"Name von Spieler 1 eingeben");

			spielername1[i]=key;	// Zeichenzuweisung
			DrawTextXY(550,200,COL_GREEN,spielername1);
			DrawEmptyRectangle(150, 440,1000,50, COL_GREEN, 2) ;
			DrawTextXY(550,480,COL_GREEN,"0: Beenden");
		}


		if (key==8) // 8 entspricht backspace
		{
			DrawFilledRectangle(0, 0, 1300, 750, COL_BLACK,1) ;
			strncpy(spielerbuffer,spielername1,15);		// aktueller Name zwischenspeichern
			strncpy(spielername1,"              ",15); 	// Spielername reseten
			strncpy(spielername1,spielerbuffer,i-1);	// Name zurückschreiben mit länge -1
			strncpy(spielerbuffer,"              ",15);	// Buffer löschen
			DrawEmptyRectangle(0, 0, 1300, 750, COL_GREEN, 4) ;
			DrawTextXY(550,51,COL_GREEN,"Level-Modus");
			DrawEmptyRectangle(150,90,1000,50, COL_GREEN, 2) ;
			DrawTextXY(350,130,COL_GREEN,"Name von Spieler 1 eingeben");
			DrawEmptyRectangle(150, 440,1000,50, COL_GREEN, 2) ;
			DrawTextXY(550,200,COL_GREEN,spielername1);	// Name erneut schreiben
			DrawTextXY(550,480,COL_GREEN,"0: Beenden");
			i=i-2; // Counter auf Start reseten
		}
		if (key== 13)// wenn Enter gedrückt wird (Enter = ASCII 13)
		{	i=14;		// Counter auf "voll" setzten, Schlaufe wird verlassen
		}

		if (key== '0') // Abbruch
		{
			return 0;
		}

	}





	// Spieler 2

	i=0; //Zähler reseten

	//Hintergrund zeichen
	DrawFilledRectangle(0, 0, 1300, 750, COL_BLACK,1) ;
	DrawEmptyRectangle(0, 0, 1300, 750, COL_GREEN, 4) ;
	DrawTextXY(550,51,COL_GREEN,"Level-Modus");
	DrawEmptyRectangle(150,90,1000,50, COL_GREEN, 2) ;
	DrawTextXY(350,130,COL_GREEN,"Name von Spieler 1 eingeben");
	DrawEmptyRectangle(150,250,1000,50, COL_GREEN, 2) ;
	DrawTextXY(350,290,COL_GREEN,"Name von Spieler 2 eingeben");
	DrawEmptyRectangle(150, 440,1000,50, COL_GREEN, 2) ;
	DrawTextXY(550,480,COL_GREEN,"0: Beenden");


	spielername2[i]=key;	// Zeichenzuweisung
	DrawTextXY(550,200,COL_GREEN,spielername1);
	DrawTextXY(550,360,COL_GREEN,spielername2);

	// durchlaufen bis array voll
	for(i=0;i<14;i++)
	{
		key=GetKeyPress(); // Tastendruck auslesen
		if((key>=32) && (key<=128)) // Nur Gross- und Kleinbuchstaben beruecksichtigen
		{
			//Hintergrund aktualisieren
			DrawFilledRectangle(0, 0, 1300, 750, COL_BLACK,1) ;
			DrawEmptyRectangle(0, 0, 1300, 750, COL_GREEN, 4) ;
			DrawTextXY(550,51,COL_GREEN,"Level-Modus");
			DrawEmptyRectangle(150,90,1000,50, COL_GREEN, 2) ;
			DrawTextXY(350,130,COL_GREEN,"Name von Spieler 1 eingeben");
			DrawEmptyRectangle(150,250,1000,50, COL_GREEN, 2) ;
			DrawTextXY(350,290,COL_GREEN,"Name von Spieler 2 eingeben");
			DrawEmptyRectangle(150, 440,1000,50, COL_GREEN, 2) ;
			DrawTextXY(550,480,COL_GREEN,"0: Beenden");


			spielername2[i]=key;	// Zeichenzuweisung
			DrawTextXY(550,200,COL_GREEN,spielername1);
			DrawTextXY(550,360,COL_GREEN,spielername2);
		}

		if (key==8) // 8 entspricht backspace
		{
			DrawFilledRectangle(0, 0, 1300, 750, COL_BLACK,1) ;
			strncpy(spielerbuffer,spielername2,15);		// aktueller Name zwischenspeichern
			strncpy(spielername2,"              ",15); 	// Spielername reseten
			strncpy(spielername2,spielerbuffer,i-1);	// Name zurückschreiben mit länge -1
			strncpy(spielerbuffer,"              ",15);	// Buffer löschen
			DrawEmptyRectangle(0, 0, 1300, 750, COL_GREEN, 4) ;
			DrawTextXY(550,51,COL_GREEN,"Level-Modus");
			DrawEmptyRectangle(150,90,1000,50, COL_GREEN, 2) ;
			DrawTextXY(350,130,COL_GREEN,"Name von Spieler 1 eingeben");
			DrawEmptyRectangle(150,250,1000,50, COL_GREEN, 2) ;
			DrawTextXY(350,290,COL_GREEN,"Name von Spieler 2 eingeben");
			DrawTextXY(550,200,COL_GREEN,spielername1);
			DrawTextXY(550,360,COL_GREEN,spielername2);
			DrawEmptyRectangle(150, 440,1000,50, COL_GREEN, 2) ;
			DrawTextXY(550,480,COL_GREEN,"0: Beenden");

			i=i-2; // Counter reseten
		}

		if (key== 13) // Wenn Enter, counter auf "voll", schlaufe wird verlassen
		{
			i=14;
		}

		if (key== '0') // Abbruch
		{
			return 0;
		}

	}


	// Übertrag aus buffer auf Counter übertragen

	strncpy(Spieler->Spieler1,spielername1,15);
	strncpy(Spieler->Spieler2,spielername2,15);

	return 1;
}
