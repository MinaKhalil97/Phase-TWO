#ifndef UI_INFO_H
#define UI_INFO_H

#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\Defs.h"

//User Interface information file.
//This file contains info that is needed by Input and Output classes to
//handle the user interface

__declspec(selectany) //This line to prevent "redefinition error"

struct UI_Info	//User Interface Info.
{
	MODE AppMode;		//Application Mode (design or simulation)
	bool UpperToolBarOpened = false, AddButtonToggled = false; bool BottomTOG = false;
	int hov = 0;
	static const int	width = 1000, height = 600, //Window width and height
		wx = 15, wy = 15,			//Window starting coordinates
		StatusBarHeight = 50,	//Status Bar Height
		ToolBarHeight = 60,		//Tool Bar Height (distance from top of window to bottom line of toolbar)
		ToolItemWidth = 60,		//Width of each item in toolbar menu
		Action_Width = 854,
	    Height_Left = 360,
		Start_Point_Left = 90,
		Height_Right = 440,
		Start_Point_Right = width - ToolItemWidth - 25,
		Start_Point_Right_Y = 60,
		Action_Width_Icon = 61,
		Action_Width_Icon_Left = 72,
		Action_Width_Icon_Right = 73,
		Start_Point_Top = 55;

	color DrawColor;		//Drawing color
	color SelectColor;		//Highlighting color
	color ConnColor;		//Connector color
	color MsgColor;			//Messages color
	color BkGrndColor;		//Back ground color


	//This should be calculated accurately because it will be used later to create connections between gates
	//For now, we will assume that rect width = 50 and height = 50
	static const int	AND2_Width = 45,		//AND2 Gate Image default width
		AND2_Height = 45;		//AND2 Gate Image default height

}UI;	//create a single global object UI

#endif