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
**	File        : InfoVar.c
**
**	Funktion   	: Grundmodul zur Anzeige der Infofenster
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
**	Tests		: 9.4.2015: 	Test durch Zusammenführung mit Steuerung
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

void InfoVar(int i)// i= Infovar
{
// switch auswertung
switch(i){

case 1:		//Countdown 1
	SelectFont("LCD", 300, FONT_BOLD);

	DrawFilledRectangle(450,205,400,400,COL_BLACK,1);
	DrawEmptyRectangle(450,205,400,400,COL_GREEN,4);
	DrawTextXY(570,580,COL_GREEN,"3");


	break;
case 2://Countdown 2

	SelectFont("LCD", 300, FONT_BOLD);

	DrawFilledRectangle(450,205,400,400,COL_BLACK,1);
	DrawEmptyRectangle(450,205,400,400,COL_GREEN,4);
	DrawTextXY(570,580,COL_GREEN,"2");

	break;

case 3: //Countdown 3

	SelectFont("LCD", 300, FONT_BOLD);
	DrawFilledRectangle(0,0,1600,810,COL_BLACK_TRANSPARENT,1);
	DrawFilledRectangle(450,205,400,400,COL_BLACK,1);
	DrawEmptyRectangle(450,205,400,400,COL_GREEN,4);
	DrawTextXY(570,580,COL_GREEN,"1");
	break;

case 4: //Fehler


	break;

case 5: //Pause

	SelectFont("LCD", 100, FONT_BOLD);
	DrawFilledRectangle(0,0,1600,810,COL_BLACK_TRANSPARENT,1);
	DrawFilledRectangle(450,205,400,400,COL_BLACK,1);
	DrawEmptyRectangle(450,205,400,400,COL_GREEN,4);
	DrawTextXY(570,580,COL_GREEN,"Pause");

	break;




}
}
