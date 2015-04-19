/*
 * MenuVar.c
 *
 *  Created on: 01.04.2015
 *      Author: Michael
 */
/**
*****************************************************************************
**	Projekt Pong
**	BTE 5052	FS2015
*****************************************************************************
**
**	File        : MenuVar.c
**
**	Funktion   	: Grundmodul zur Anzeige der Menufenster
**
**	Parameter	: MenuVar
**
**	Rückgabe	: void
**
**	Input		: struct AnzeigeParameter
**
**	Output		: -
**
** 	Author		: Michael Schmutz
**
**	Version		: 1.0
**
**	History		: 2.4.2015: 	Erstellt
**
**
**	Pendenzen	:
**
**	Bugs		:
**
**	Tests		: 9.4.2015: 	Test durch Zusammenführung mit main
**
**
*****************************************************************************
**/

#include "window.h"
#include "Spielsteuerung.h"
#include "Header.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

void MenuVar(int i) // i = Menuvar
{
// Switch Auswertung
switch(i){

case 1:		//Hauptmenu Fenster
	SelectFont("LCD", 30, FONT_BOLD);
	DrawFilledRectangle(0, 0, 1300, 750, COL_BLACK, 2) ;
	DrawEmptyRectangle(0, 0, 1300, 750, COL_GREEN, 4) ;
	DrawTextXY(550,51,COL_GREEN,"Hauptmenu");

	DrawEmptyRectangle(150,90,1000,50, COL_GREEN, 2) ;
	DrawTextXY(550,130,COL_GREEN,"1: Level-Modus");

	DrawEmptyRectangle(150, 160,1000,50, COL_GREEN, 2) ;
	DrawTextXY(550,200,COL_GREEN,"2: Einzelspiel");

	DrawEmptyRectangle(150, 230,1000,50, COL_GREEN, 2) ;
	DrawTextXY(550,270,COL_GREEN,"3: Highscore");

	DrawEmptyRectangle(150, 440,1000,50, COL_GREEN, 2) ;
	DrawTextXY(550,480,COL_GREEN,"ESC: Beenden");

	break;

case 2: //Levelmodus Fenster
	SelectFont("LCD", 30, FONT_BOLD);
	DrawFilledRectangle(0, 0, 1300, 750, COL_BLACK, 1) ;
	DrawEmptyRectangle(0, 0, 1300, 750, COL_GREEN, 4) ;
	DrawTextXY(550,51,COL_GREEN,"Levelmodus");

	DrawEmptyRectangle(150, 90,1000,50, COL_GREEN, 1) ;
	DrawTextXY(350,130,COL_GREEN,"1: Ein Spieler (gegen Computer)");

	DrawEmptyRectangle(150, 160,1000,50, COL_GREEN, 1) ;
	DrawTextXY(535,200,COL_GREEN,"2: Zwei Spieler");


	DrawEmptyRectangle(150, 440,1000,50, COL_GREEN, 1) ;
	DrawTextXY(400,480,COL_GREEN,"0: zurueck zum hauptmenu");

	break;

case 3: //Einzelspiel Fenster
	SelectFont("LCD", 30, FONT_BOLD);
	DrawFilledRectangle(0, 0, 1300, 750, COL_BLACK, 1) ;
	DrawEmptyRectangle(0, 0, 1300, 750, COL_GREEN, 4) ;
	DrawTextXY(550,51,COL_GREEN,"Einzelspiel");

	DrawEmptyRectangle(150, 90,1000,50, COL_GREEN, 1) ;
		DrawTextXY(350,130,COL_GREEN,"1: Ein Spieler (gegen Computer)");

		DrawEmptyRectangle(150, 160,1000,50, COL_GREEN, 1) ;
		DrawTextXY(535,200,COL_GREEN,"2: Zwei Spieler");


		DrawEmptyRectangle(150, 440,1000,50, COL_GREEN, 1) ;
		DrawTextXY(400,480,COL_GREEN,"0: zurueck zum hauptmenu");


break;

case 4: //Schwierigkeit Fenster
	SelectFont("LCD", 30, FONT_BOLD);
	DrawFilledRectangle(0, 0, 1300, 750, COL_BLACK, 1) ;
	DrawEmptyRectangle(0, 0, 1300, 750, COL_GREEN, 4) ;
	DrawTextXY(550,51,COL_GREEN,"Schwierigkeit");

	DrawEmptyRectangle(150,90,1000,50, COL_GREEN, 1) ;
	DrawTextXY(450,130,COL_GREEN,"1: Schwierigkeitsgrad 1");

	DrawEmptyRectangle(150, 160,1000,50, COL_GREEN, 1) ;
	DrawTextXY(450,200,COL_GREEN,"2: Schwierigkeitsgrad 2");

	DrawEmptyRectangle(150, 230,1000,50, COL_GREEN, 1) ;
	DrawTextXY(450,270,COL_GREEN,"3: Schwierigkeitsgrad 3");

	DrawEmptyRectangle(150, 300,1000,50, COL_GREEN, 1) ;
	DrawTextXY(450,340,COL_GREEN,"4: Schwierigkeitsgrad 4");

	DrawEmptyRectangle(150, 370,1000,50, COL_GREEN, 1) ;
	DrawTextXY(450,410,COL_GREEN,"5: Schwierigkeitsgrad 5");

	DrawEmptyRectangle(150, 440,1000,50, COL_GREEN, 1) ;
	DrawTextXY(400,480,COL_GREEN,"0: zurueck zum hauptmenu");
break;

case 5: //Highscore Fesnter
	SelectFont("LCD", 30, FONT_BOLD);
	DrawFilledRectangle(0, 0, 1300, 750, COL_BLACK, 1) ;
	DrawEmptyRectangle(0, 0, 1300, 750, COL_GREEN, 4) ;
	DrawTextXY(550,51,COL_GREEN,"Highscore");

	DrawEmptyRectangle(150,90,1000,50, COL_GREEN, 1) ;
	DrawTextXY(400,130,COL_GREEN,"1: Alle Eintraege loeschen");


	DrawEmptyRectangle(150, 440,1000,50, COL_GREEN, 1) ;
	DrawTextXY(400,480,COL_GREEN,"0: zurueck zum hauptmenu");

break;

default:
	break;
}






















}
