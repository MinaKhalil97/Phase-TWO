//#include "Input.h"
#include "Output.h"
#include<string>
#include<iostream>
#include<sstream>
#include<string>
Input::Input(window* pW)
{
	pWind = pW; //point to the passed window
}

void Input::GetPointClicked(int &x, int &y)
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click

}
buttonstate Input::GetButtonState(const button State, int &x, int &y){
	return pWind->GetButtonState(State, x, y);
}


string Input::GetSrting(Output *pOut)
{
	///TODO: Implement this Function
	//Read a complete string from the user until the user presses "ENTER".
	//If the user presses "ESCAPE". This function should return an empty string.
	//"BACKSPACE" should be also supported
	//User should see what he is typing at the status bar

	char c;
	string s = "";
	pWind->WaitKeyPress(c);

	while (c != 13)
	{
		if (c == 8)
		{
			if ((int)s.size() != 0) s.erase(s.size() - 1, 1);
		}
		else s += c;
		pOut->PrintMsg(s);
		pWind->WaitKeyPress(c);
	}
	UI.BottomTOG = false;
	return s;
}

//This function reads the position where the user clicks to determine the desired action
ActionType Input::GetUserAction() const
{
	int x, y, hx, hy;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click
	pWind->GetMouseCoord(hx, hy);
	if (UI.AppMode == DESIGN)	//application is in design mode
	{
		//DRAWING AREA
		if (x > 70 && y>UI.ToolBarHeight&&x<UI.width - 92 && y < 530){
			return DSN_TOOL;
		}
		// right tool bar //////
		if (y >= UI.Start_Point_Right_Y && y < (UI.Start_Point_Right_Y + UI.Height_Right) && x >= UI.Start_Point_Right &&x <= UI.ToolBarHeight + 10 + UI.Start_Point_Right)
		{

			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up Vertically <==
			int ClickedItemOrder = ((y - UI.Start_Point_Right_Y) / UI.Action_Width_Icon_Right);

			switch (ClickedItemOrder)
			{
			case ITM_UNDO:return UNDO;
			case ITM_REDO:return REDO;
			case ITM_DELETE:return DEL;
			case ITM_ZOOM:return ZOOM;
			case ITM_TRUTHTABLE:return CREATE_TRUTH_TABLE;
			case ITM_SIMULATE:return SIM_MODE;
			default: return DSN_TOOL;



			}

		}
		//[0] If user click on the Upper toolbar and it's opened
		if (y >= 0 && y < 60 && x >= UI.Start_Point_Top&&x <= (UI.Start_Point_Top + UI.Action_Width) && UI.UpperToolBarOpened)

		{//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==

			int ClickedItemOrder = ((x - UI.Start_Point_Top) / UI.Action_Width_Icon);

			switch (ClickedItemOrder)
			{
			case ITM_BUFF:return ADD_Buff;
			case ITM_NOT:return ADD_INV;
			case ITM_AND2:return ADD_AND_GATE_2;
			case ITM_NAND2:return ADD_NAND_GATE_2;
			case ITM_OR2:return ADD_OR_GATE_2;
			case ITM_NOR2:return 	ADD_NOR_GATE_2;
			case ITM_XOR2: return ADD_XOR_GATE_2;
			case ITM_XNOR2: return ADD_XNOR_GATE_2;
			case ITM_AND3:return ADD_AND_GATE_3;
			case ITM_NOR3:	return ADD_NOR_GATE_3;
			case ITM_XOR3:return ADD_XOR_GATE_3;
			case ITM_LED:return ADD_LED;
			case ITM_SWITCH:return ADD_Switch;
			case ITM_CONNECTION:return ADD_CONNECTION;

			default: return DSN_TOOL;



			}
		}

		//left tool bar 
		if (y >= UI.Start_Point_Left && y < UI.Start_Point_Left + UI.Height_Left && x >= 0 && x <= UI.ToolBarHeight + 10)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==

			int ClickedItemOrder = ((y - UI.Start_Point_Left) / UI.Action_Width_Icon_Left);

			switch (ClickedItemOrder)
			{
			case ITM_ADD:return ADD_COMPONENTS;
			case ITM_NEW:return NEW;
			case ITM_OPEN:return LOAD;
			case ITM_SAVE:return SAVE;
			case ITM_EXIT:return EXIT;
			default: return DSN_TOOL;



			}

		}






		return EMPTY_AREA;
	}

	else	//Application is in Simulation mode
	{
		return SIM_MODE;	//This should be changed after creating the compelete simulation bar
	}

	return SELECT;
}


Input::~Input()
{
}
