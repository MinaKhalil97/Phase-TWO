#include "Output.h"
#include<string>
#include<iostream>


void Output::correct(int& x, int &y) const
{
	y -= UI.ToolBarHeight;
	int Cx1 = (x) / 15;
	int Cx2 = (x + 14) / 15;
	Cx1 *= 15;
	Cx2 *= 15;
	if (abs(Cx1 - x) <= abs(Cx2 - x)) x /= 15;
	else x = (x + 14) / 15;

	int Cy1 = (y) / 15;
	int Cy2 = (y + 14) / 15;
	Cy1 *= 15;
	Cy2 *= 15;
	if (abs(Cy1 - y) <= abs(Cy2 - y)) y /= 15;
	else y = (y + 14) / 15;
}

Output::Output()
{
	//Initialize user interface parameters

	UI.AppMode = DESIGN;	//Design Mode is the startup mode

	//Initilaize interface colors
	UI.DrawColor = BLACK;
	UI.SelectColor = BLUE;
	UI.ConnColor = RED;
	UI.MsgColor = BLUE;
	UI.BkGrndColor = WHITE;

	//Create the drawing window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	ChangeTitle("Programming Techniques Project");

	initi();
	CreateDesignToolBar();	//Create the desgin toolbar
	CreateStatusBar();		//Create Status bar
	ClearDrawingArea();
	
}

void Output::initi()
{
	arr = new int*[UI.height / 15 + 50];
	for (int i = 0; i <= UI.height / 15; i++) arr[i] = new int[UI.width / 15 + 50];
	for (int i = 0; i <= UI.height / 15; i++)
	for (int j = 0; j <= UI.width / 15; j++) arr[i][j] = 0;

	visit = new int*[100];
	for (int i = 0; i < 100; i++)
		visit[i] = new int[100];
}

Input* Output::CreateInput() const
{
	//Create an Input Object & assign it to the Same Window
	Input* pIn = new Input(pWind);
	return pIn;
}


//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int wd, int h, int x, int y) const
{
	return new window(wd, h, x, y);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::ChangeTitle(string Title) const
{
	pWind->ChangeTitle(Title);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar() const
{
	/*pWind->SetPen(RED,3);
	pWind->DrawLine(0, UI.height-UI.StatusBarHeight, UI.width, UI.height-UI.StatusBarHeight);
	*/
	if (UI.BottomTOG){
		pWind->DrawImage("images\\Menu\\BOTTOM_BARTOGGLED-L.jpg", 35, UI.height - 85, 920, 70);
	}
	else{
		pWind->DrawImage("images\\Menu\\BOTTOM_BAR.jpg", 35, UI.height - 85, 920, 70);
	}
}
//////////////////////////////////////////////////////////////////////////////////
void Output::PrintMsg(string msg) const
{
	CreateStatusBar();	//Clear Status bar to print message on it
	// Set the Message offset from the Status Bar
	int MsgX = 125;
	int MsgY = 62;

	// Print the Message
	pWind->SetFont(22, BOLD | ITALICIZED, BY_NAME, "Arial");
	pWind->SetPen(UI.MsgColor);
	pWind->DrawString(MsgX, UI.height - MsgY, msg);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar()const
{
	// Set the Message offset from the Status Bar
	int MsgX = 125;
	int MsgY = 66;

	//Overwrite using bachground color to erase the message
	pWind->SetPen(UI.BkGrndColor);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(MsgX, UI.height - MsgY, UI.width - 60, UI.height - 35);
}
//////////////////////////////////////////////////////////////////////////////////////////
//Clears the drawing (degin) area
void Output::ClearDrawingArea() 
{
	pWind->SetPen(WHITE, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(UI.ToolBarHeight + 10, UI.ToolBarHeight, UI.Start_Point_Right, UI.height - 90);
	pWind->SetPen(LIGHTSLATEGRAY, 4);
	for (int i = 75; i < UI.width - 90; i += 15){
		for (int j = 75; j < UI.height - 90; j += 15){

			pWind->DrawPixel(i, j);
		}

	}
	for (int i = 0; i <= UI.height / 15; i++)
	for (int j = 0; j <= UI.width / 15; j++) 
	 arr[i][j] = 0;

}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the Design mode
void Output::CreateDesignToolBar() const
{
	/*for (int i = 15; i < UI.width-160; i += 15){
	pWind->SetPen(LIGHTSLATEGRAY, 1);
	//pWind->DrawLine(i+70, UI.ToolBarHeight+10, i+70, UI.height - 67);
	pWind->DrawPixel(i + 70, UI.ToolBarHeight + 10);
	}
	for (int i = 15; i < UI.height-140; i += 15){
	pWind->SetPen(LIGHTSLATEGRAY, 1);
	//pWind->DrawLine(70, i+70, UI.width-92, i+70);
	pWind->DrawPixel(70, i+70);
	}*/
	pWind->SetPen(LIGHTSLATEGRAY, 4);
	for (int i = 75; i < UI.width - 90; i += 15){
		for (int j = 75; j < UI.height - 95; j += 15){

			pWind->DrawPixel(i, j);
		}

	}

	UI.AppMode = DESIGN;	//Design Mode
	//You can draw the tool bar icons in any way you want.
	//first sraw the tool bar

	string ToolBarItems[ITMCNT];
	ToolBarItems[TOOLBARTOP] = "images\\Menu\\TOP_BAR.jpg";
	//leftbar
	if (!UI.AddButtonToggled){
		ToolBarItems[TOOLBARLEFT] = "images\\Menu\\LEFT_BAR.jpg";
	}
	else { ToolBarItems[TOOLBARLEFT] = "images\\Menu\\LEFT_BARTOGGLED.jpg"; }
	//right bar
	ToolBarItems[TOOLBARRIGHT] = "images\\Menu\\RIGHT_BAR.jpg";


	//
	pWind->DrawImage(ToolBarItems[1], -5, UI.Start_Point_Left, UI.ToolBarHeight + 10, UI.Height_Left);
	pWind->DrawImage(ToolBarItems[2], UI.Start_Point_Right, UI.Start_Point_Right_Y, UI.ToolBarHeight + 10, UI.Height_Right);


}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the simulation mode
void Output::CreateSimulationToolBar() const
{
	UI.AppMode = SIMULATION;	//Simulation Mode

	//TODO: Write code to draw the simualtion toolbar (similar to that of design toolbar drawing)


}

//setting buffer
void Output::SetBuffer(bool val = true){
	pWind->SetBuffering(val);
}
void Output::UpdateBuffer(){
	pWind->UpdateBuffer();
}


void Output::SetTaken(int  i, int j ,int x)
{
	arr[j][i] = x;
}

bool Output::valid(int i, int j ,int x) const
{
	if (i<=0 || j >= (UI.height - UI.StatusBarHeight - UI.ToolBarHeight) / 15 || i >= UI.width / 15 || j <= 0 || arr[j][i]==1 || arr[j][i] == 2 || arr[j][i] == x) return false;
	else return true;

}



//======================================================================================//
//								Components Drawing Functions							//
//======================================================================================//

void Output::DrawAND2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;
	
	int Cx = r_GfxInfo.x1 + Len / 2;
	int Cy = r_GfxInfo.y1 + Wdth / 2;
	
////////////////////////////////////
	int x1 = r_GfxInfo.x1;
	int x2 = r_GfxInfo.x2;
	int y1 = r_GfxInfo.y1;
	int y2 = r_GfxInfo.y2;
	correct(x1, y1);
	correct(x2, y2);

	x1 *= 15;
	x2 *= 15;
	x1 -= 15;
	
	y1 *= 15;
	y1 -= 15;
	y2 *= 15;
	y1 += UI.ToolBarHeight;
	y2 += UI.ToolBarHeight;
	
	pWind->SetPen(BLACK, 3);
	pWind->DrawLine(x1, y1 + 15, x1 + 7, y1 + 15);
	pWind->DrawLine(x1,y1 + 45, x1 + 7, y1 + 45);
	//output
	pWind->DrawLine(x1 + 60 - 7, y1 + 30, x1 + 60, y1 + 30);


	if (selected)	//use image in the highlighted case
		pWind->SetPen(BLUE, 3);
	else
		pWind->SetPen(RED, 3);

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	//pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);

	//drawing the gate
	pWind->DrawLine(x1 + 7, y1 + 7, x1 + 37, y1 + 7);
	pWind->DrawLine(x1 + 7, y1 + 7,x1 + 7, y1 + 60 - 7);
	pWind->DrawLine(x1 + 7, y1 + 60 - 7, x1 + 37, y1 + 60 - 7);
	pWind->DrawArc(x1 + 10, y1 - 2 + 7, x1 + 60 - 7, y1 + 48 + 7, 270, 90);
	
	///////////////////////////

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info

	Cy -= UI.ToolBarHeight;
	Cx /= 15;
	Cy /= 15;
	Len /= 15;
	Wdth /= 15;
	for (int i = Cx - Len / 2 - 1; i <= Cx + Len / 2 + 1; i++)
	{

		for (int j = Cy - Wdth / 2; j <= Cy + Wdth / 2; j++)
		{
			if (i == Cx - Len / 2 - 1 || j == Cy - Wdth / 2 - 1 || i == Cx + Len / 2 + 1 || j == Cy + Wdth / 2 + 1) arr[j][i] = 2;
			else arr[j][i] = 1; 
		}

	}
	
	
}

void Output::DrawAND3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;

	int Cx = r_GfxInfo.x1 + Len / 2;
	int Cy = r_GfxInfo.y1 + Wdth / 2;
	////////////////////////////////////
	int x1 = r_GfxInfo.x1;
	int x2 = r_GfxInfo.x2;
	int y1 = r_GfxInfo.y1;
	int y2 = r_GfxInfo.y2;
	correct(x1, y1);
	correct(x2, y2);

	x1 *= 15;
	x2 *= 15;
	x1 -= 15;

	y1 *= 15;
	y1 -= 15;
	y2 *= 15;
	y1 += UI.ToolBarHeight;
	y2 += UI.ToolBarHeight;
	pWind->SetPen(BLACK, 3);
	pWind->DrawLine(x1, y1 + 15, x1 + 7, y1 + 15);
	pWind->DrawLine(x1, y1 + 45, x1 + 7, y1 + 45);
	pWind->DrawLine(r_GfxInfo.x1, r_GfxInfo.y1 + 30, r_GfxInfo.x1 + 7, r_GfxInfo.y1 + 30);

	//output
	pWind->DrawLine(x1 + 60 - 7, y1 + 30, x1 + 60, y1 + 30);


	if (selected)	//use image in the highlighted case
		pWind->SetPen(BLUE, 3);
	else
		pWind->SetPen(RED, 3);

	

	//drawing the gate
	pWind->DrawLine(r_GfxInfo.x1 + 7, r_GfxInfo.y1 + 7, r_GfxInfo.x1 + 37, r_GfxInfo.y1 + 7);
	pWind->DrawLine(r_GfxInfo.x1 + 7, r_GfxInfo.y1 + 7, r_GfxInfo.x1 + 7, r_GfxInfo.y1 + 60 - 7);
	pWind->DrawLine(r_GfxInfo.x1 + 7, r_GfxInfo.y1 + 60 - 7, r_GfxInfo.x1 + 37, r_GfxInfo.y1 + 60 - 7);
	pWind->DrawArc(r_GfxInfo.x1 + 10, r_GfxInfo.y1 - 2 + 7, r_GfxInfo.x1 + 60 - 7, r_GfxInfo.y1 + 48 + 7, 270, 90);

	///////////////////////////

	Cy -= UI.ToolBarHeight;
	Cx /= 15;
	Cy /= 15;
	Len /= 15;
	Wdth /= 15;
	for (int i = Cx - Len / 2 - 1; i <= Cx + Len / 2 + 1; i++)
	{

		for (int j = Cy - Wdth / 2; j <= Cy + Wdth / 2; j++)
		{
			if (i == Cx - Len / 2 - 1 || j == Cy - Wdth / 2 - 1 || i == Cx + Len / 2 + 1 || j == Cy + Wdth / 2 + 1) arr[j][i] = 2;
			else arr[j][i] = 1;
		}

	}


}

void Output::DrawOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;

	int Cx = r_GfxInfo.x1 + Len / 2;
	int Cy = r_GfxInfo.y1 + Wdth / 2;
	////////////////////////////////////
	int x1 = r_GfxInfo.x1;
	int x2 = r_GfxInfo.x2;
	int y1 = r_GfxInfo.y1;
	int y2 = r_GfxInfo.y2;
	correct(x1, y1);
	correct(x2, y2);

	x1 *= 15;
	x2 *= 15;
	x1 -= 15;

	y1 *= 15;
	y1 -= 15;
	y2 *= 15;
	y1 += UI.ToolBarHeight;
	y2 += UI.ToolBarHeight;


	pWind->SetPen(BLACK, 3);
	pWind->DrawLine(x1, y1 + 15, x1 + 7, y1 + 15);
	pWind->DrawLine(x1, y1 + 45, x1 + 7, y1 + 45);
	pWind->DrawLine(r_GfxInfo.x1, r_GfxInfo.y1 + 30, r_GfxInfo.x1 + 7, r_GfxInfo.y1 + 30);

	//output
	pWind->DrawLine(x1 + 60 - 7, y1 + 30, x1 + 60, y1 + 30);


	if (selected)	//use image in the highlighted case
		pWind->SetPen(BLUE, 3);
	else
		pWind->SetPen(RED, 3);



	//drawing the gate
	pWind->DrawLine(r_GfxInfo.x1 + 7, r_GfxInfo.y1 + 7, r_GfxInfo.x1 + 37, r_GfxInfo.y1 + 7);
	pWind->DrawArc(r_GfxInfo.x1 + 10 - 20, r_GfxInfo.y1 - 2 + 7, r_GfxInfo.x1 + 60 - 7 - 35, r_GfxInfo.y1 + 48 + 7, 270, 90);
	pWind->DrawLine(r_GfxInfo.x1 + 7, r_GfxInfo.y1 + 60 - 7, r_GfxInfo.x1 + 37, r_GfxInfo.y1 + 60 - 7);
	pWind->DrawArc(r_GfxInfo.x1 + 10, r_GfxInfo.y1 - 2 + 7, r_GfxInfo.x1 + 60 - 7, r_GfxInfo.y1 + 48 + 7, 270, 90);

	///////////////////////////

	Cy -= UI.ToolBarHeight;
	Cx /= 15;
	Cy /= 15;
	Len /= 15;
	Wdth /= 15;
	for (int i = Cx - Len / 2 - 1; i <= Cx + Len / 2 + 1; i++)
	{

		for (int j = Cy - Wdth / 2; j <= Cy + Wdth / 2; j++)
		{
			if (i == Cx - Len / 2 - 1 || j == Cy - Wdth / 2 - 1 || i == Cx + Len / 2 + 1 || j == Cy + Wdth / 2 + 1) arr[j][i] = 2;
			else arr[j][i] = 1;
		}

	}


}

void Output::DrawXOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;

	int Cx = r_GfxInfo.x1 + Len / 2;
	int Cy = r_GfxInfo.y1 + Wdth / 2;
	////////////////////////////////////
	int x1 = r_GfxInfo.x1;
	int x2 = r_GfxInfo.x2;
	int y1 = r_GfxInfo.y1;
	int y2 = r_GfxInfo.y2;
	correct(x1, y1);
	correct(x2, y2);

	x1 *= 15;
	x2 *= 15;
	x1 -= 15;

	y1 *= 15;
	y1 -= 15;
	y2 *= 15;
	y1 += UI.ToolBarHeight;
	y2 += UI.ToolBarHeight;


	pWind->SetPen(BLACK, 3);
	pWind->DrawLine(x1, y1 + 15, x1 + 7, y1 + 15);
	pWind->DrawLine(x1, y1 + 45, x1 + 7, y1 + 45);
	pWind->DrawLine(r_GfxInfo.x1, r_GfxInfo.y1 + 30, r_GfxInfo.x1 + 7, r_GfxInfo.y1 + 30);

	//output
	pWind->DrawLine(x1 + 60 - 7, y1 + 30, x1 + 60, y1 + 30);


	if (selected)	//use image in the highlighted case
		pWind->SetPen(BLUE, 3);
	else
		pWind->SetPen(RED, 3);



	//drawing the gate
	pWind->DrawLine(r_GfxInfo.x1 + 17, r_GfxInfo.y1 + 7, r_GfxInfo.x1 + 37, r_GfxInfo.y1 + 7);
	pWind->DrawArc(r_GfxInfo.x1 + 10 - 20, r_GfxInfo.y1 - 2 + 7, r_GfxInfo.x1 + 60 - 7 - 35, r_GfxInfo.y1 + 48 + 7, 270, 90);
	pWind->DrawArc(r_GfxInfo.x1 + 10 - 10, r_GfxInfo.y1 - 2 + 7, r_GfxInfo.x1 + 60 - 7 - 25, r_GfxInfo.y1 + 48 + 7, 270, 90);
	pWind->DrawLine(r_GfxInfo.x1 + 17, r_GfxInfo.y1 + 60 - 7, r_GfxInfo.x1 + 37, r_GfxInfo.y1 + 60 - 7);
	pWind->DrawArc(r_GfxInfo.x1 + 10, r_GfxInfo.y1 - 2 + 7, r_GfxInfo.x1 + 60 - 7, r_GfxInfo.y1 + 48 + 7, 270, 90);

	///////////////////////////

	Cy -= UI.ToolBarHeight;
	Cx /= 15;
	Cy /= 15;
	Len /= 15;
	Wdth /= 15;
	for (int i = Cx - Len / 2 - 1; i <= Cx + Len / 2 + 1; i++)
	{

		for (int j = Cy - Wdth / 2; j <= Cy + Wdth / 2; j++)
		{
			if (i == Cx - Len / 2 - 1 || j == Cy - Wdth / 2 - 1 || i == Cx + Len / 2 + 1 || j == Cy + Wdth / 2 + 1) arr[j][i] = 2;
			else arr[j][i] = 1;
		}

	}


}

void Output::DrawXOR3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;

	int Cx = r_GfxInfo.x1 + Len / 2;
	int Cy = r_GfxInfo.y1 + Wdth / 2;
	////////////////////////////////////
	int x1 = r_GfxInfo.x1;
	int x2 = r_GfxInfo.x2;
	int y1 = r_GfxInfo.y1;
	int y2 = r_GfxInfo.y2;
	correct(x1, y1);
	correct(x2, y2);

	x1 *= 15;
	x2 *= 15;
	x1 -= 15;

	y1 *= 15;
	y1 -= 15;
	y2 *= 15;
	y1 += UI.ToolBarHeight;
	y2 += UI.ToolBarHeight;


	pWind->SetPen(BLACK, 3);
	pWind->DrawLine(r_GfxInfo.x1, r_GfxInfo.y1 + 15, r_GfxInfo.x1 + 14, r_GfxInfo.y1 + 15);
	pWind->DrawLine(r_GfxInfo.x1, r_GfxInfo.y1 + 30, r_GfxInfo.x1 + 14, r_GfxInfo.y1 + 30);
	pWind->DrawLine(r_GfxInfo.x1, r_GfxInfo.y1 + 45, r_GfxInfo.x1 + 14, r_GfxInfo.y1 + 45);

	//output
	pWind->DrawLine(x1 + 60 - 7, y1 + 30, x1 + 60, y1 + 30);


	if (selected)	//use image in the highlighted case
		pWind->SetPen(BLUE, 3);
	else
		pWind->SetPen(RED, 3);



	//drawing the gate
	pWind->DrawLine(r_GfxInfo.x1 + 17, r_GfxInfo.y1 + 7, r_GfxInfo.x1 + 37, r_GfxInfo.y1 + 7);
	pWind->DrawArc(r_GfxInfo.x1 + 10 - 20, r_GfxInfo.y1 - 2 + 7, r_GfxInfo.x1 + 60 - 7 - 35, r_GfxInfo.y1 + 48 + 7, 270, 90);
	pWind->DrawArc(r_GfxInfo.x1 + 10 - 10, r_GfxInfo.y1 - 2 + 7, r_GfxInfo.x1 + 60 - 7 - 25, r_GfxInfo.y1 + 48 + 7, 270, 90);
	pWind->DrawLine(r_GfxInfo.x1 + 17, r_GfxInfo.y1 + 60 - 7, r_GfxInfo.x1 + 37, r_GfxInfo.y1 + 60 - 7);
	pWind->DrawArc(r_GfxInfo.x1 + 10, r_GfxInfo.y1 - 2 + 7, r_GfxInfo.x1 + 60 - 7, r_GfxInfo.y1 + 48 + 7, 270, 90);

	///////////////////////////

	Cy -= UI.ToolBarHeight;
	Cx /= 15;
	Cy /= 15;
	Len /= 15;
	Wdth /= 15;
	for (int i = Cx - Len / 2 - 1; i <= Cx + Len / 2 + 1; i++)
	{

		for (int j = Cy - Wdth / 2; j <= Cy + Wdth / 2; j++)
		{
			if (i == Cx - Len / 2 - 1 || j == Cy - Wdth / 2 - 1 || i == Cx + Len / 2 + 1 || j == Cy + Wdth / 2 + 1) arr[j][i] = 2;
			else arr[j][i] = 1;
		}

	}


}

void Output::DrawBUFFER(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;

	int Cx = r_GfxInfo.x1 + Len / 2;
	int Cy = r_GfxInfo.y1 + Wdth / 2;
	////////////////////////////////////
	int x1 = r_GfxInfo.x1;
	int x2 = r_GfxInfo.x2;
	int y1 = r_GfxInfo.y1;
	int y2 = r_GfxInfo.y2;
	correct(x1, y1);
	correct(x2, y2);

	x1 *= 15;
	x2 *= 15;
	x1 -= 15;

	y1 *= 15;
	y1 -= 15;
	y2 *= 15;
	y1 += UI.ToolBarHeight;
	y2 += UI.ToolBarHeight;


	pWind->SetPen(BLACK, 3);
	pWind->DrawLine(r_GfxInfo.x1, r_GfxInfo.y1 + 30, r_GfxInfo.x1 + 15, r_GfxInfo.y1 + 30);
	pWind->DrawLine(r_GfxInfo.x1 + 60 - 15, r_GfxInfo.y1 + 30, r_GfxInfo.x1 + 60, r_GfxInfo.y1 + 30);
	if (selected)	//use image in the highlighted case
		pWind->SetPen(BLUE, 3);
	else
		pWind->SetPen(RED, 3);
	//draw buffer 
	pWind->DrawTriangle(r_GfxInfo.x1 + 15, r_GfxInfo.y1 + 7, r_GfxInfo.x1 + 15, r_GfxInfo.y1 + 60 - 7, r_GfxInfo.x1 + 60 - 15, r_GfxInfo.y1 + 30, FRAME);
	///////////////////////////

	Cy -= UI.ToolBarHeight;
	Cx /= 15;
	Cy /= 15;
	Len /= 15;
	Wdth /= 15;
	for (int i = Cx - Len / 2 - 1; i <= Cx + Len / 2 + 1; i++)
	{

		for (int j = Cy - Wdth / 2; j <= Cy + Wdth / 2; j++)
		{
			if (i == Cx - Len / 2 - 1 || j == Cy - Wdth / 2 - 1 || i == Cx + Len / 2 + 1 || j == Cy + Wdth / 2 + 1) arr[j][i] = 2;
			else arr[j][i] = 1;
		}

	}


}

void Output::DrawNOT(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;

	int Cx = r_GfxInfo.x1 + Len / 2;
	int Cy = r_GfxInfo.y1 + Wdth / 2;
	
	////////////////////////////////////
	int x1 = r_GfxInfo.x1;
	int x2 = r_GfxInfo.x2;
	int y1 = r_GfxInfo.y1;
	int y2 = r_GfxInfo.y2;
	correct(x1, y1);

	x1 *= 15;
	x1 -= 15;

	y1 *= 15;
	y1 -= 15;
	y1 += UI.ToolBarHeight;

	pWind->SetPen(BLACK, 3);
	pWind->DrawLine(x1, y1 + 30, x1 + 15, y1 + 30);


	pWind->DrawLine(x1 + 60 - 9, y1 + 30, x1 + 60, y1 + 30);
	if (selected)	//use image in the highlighted case
		pWind->SetPen(BLUE, 3);
	else
		pWind->SetPen(RED, 3);
	//draw buffer 
	pWind->DrawTriangle(x1 + 15, y1 + 7, x1 + 15, y1 + 60 - 7, x1 + 60 - 15, y1 + 30, FRAME);
	if (selected)	//use image in the highlighted case
		pWind->SetPen(BLUE, 2);
	else
		pWind->SetPen(RED, 2);
	pWind->DrawCircle(x1 + 60 - 15 + 3, y1 + 30, 5);
	///////////////////////////

	Cy -= UI.ToolBarHeight;
	Cx /= 15;
	Cy /= 15;
	Len /= 15;
	Wdth /= 15;
	for (int i = Cx - Len / 2 - 1; i <= Cx + Len / 2 + 1; i++)
	{

		for (int j = Cy - Wdth / 2; j <= Cy + Wdth / 2; j++)
		{
			if (i == Cx - Len / 2 - 1 || j == Cy - Wdth / 2 - 1 || i == Cx + Len / 2 + 1 || j == Cy + Wdth / 2 + 1) arr[j][i] = 2;
			else arr[j][i] = 1;
		}

	}


}


void Output::DrawNOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;

	int Cx = r_GfxInfo.x1 + Len / 2;
	int Cy = r_GfxInfo.y1 + Wdth / 2;
	////////////////////////////////////
	int x1 = r_GfxInfo.x1;
	int x2 = r_GfxInfo.x2;
	int y1 = r_GfxInfo.y1;
	int y2 = r_GfxInfo.y2;
	correct(x1, y1);
	correct(x2, y2);

	x1 *= 15;
	x2 *= 15;
	x1 -= 15;

	y1 *= 15;
	y1 -= 15;
	y2 *= 15;
	y1 += UI.ToolBarHeight;
	y2 += UI.ToolBarHeight;


	pWind->SetPen(BLACK, 3);
	pWind->DrawLine(r_GfxInfo.x1, r_GfxInfo.y1 + 15, r_GfxInfo.x1 + 14, r_GfxInfo.y1 + 15);
	pWind->DrawLine(r_GfxInfo.x1, r_GfxInfo.y1 + 45, r_GfxInfo.x1 + 14, r_GfxInfo.y1 + 45);


	pWind->DrawLine(r_GfxInfo.x1 + 60 - 9, r_GfxInfo.y1 + 30, r_GfxInfo.x1 + 60, r_GfxInfo.y1 + 30);
	string GateImage;
	if (selected)	//use image in the highlighted case
		pWind->SetPen(BLUE, 3);
	else
		pWind->SetPen(RED, 3);

	//drawing the gate
	pWind->DrawLine(r_GfxInfo.x1 + 7, r_GfxInfo.y1 + 7, r_GfxInfo.x1 + 37, r_GfxInfo.y1 + 7);
	pWind->DrawArc(r_GfxInfo.x1 + 10 - 20, r_GfxInfo.y1 - 2 + 7, r_GfxInfo.x1 + 60 - 7 - 35, r_GfxInfo.y1 + 48 + 7, 270, 90);
	pWind->DrawLine(r_GfxInfo.x1 + 7, r_GfxInfo.y1 + 60 - 7, r_GfxInfo.x1 + 37, r_GfxInfo.y1 + 60 - 7);
	pWind->DrawArc(r_GfxInfo.x1 + 10, r_GfxInfo.y1 - 2 + 7, r_GfxInfo.x1 + 60 - 7, r_GfxInfo.y1 + 48 + 7, 270, 90);
	if (selected)	//use image in the highlighted case
		pWind->SetPen(BLUE, 2);
	else
		pWind->SetPen(RED, 2);
	pWind->DrawCircle(r_GfxInfo.x1 + 60 - 10 + 3, r_GfxInfo.y1 + 30, 5);
	///////////////////////////

	Cy -= UI.ToolBarHeight;
	Cx /= 15;
	Cy /= 15;
	Len /= 15;
	Wdth /= 15;
	for (int i = Cx - Len / 2 - 1; i <= Cx + Len / 2 + 1; i++)
	{

		for (int j = Cy - Wdth / 2; j <= Cy + Wdth / 2; j++)
		{
			if (i == Cx - Len / 2 - 1 || j == Cy - Wdth / 2 - 1 || i == Cx + Len / 2 + 1 || j == Cy + Wdth / 2 + 1) arr[j][i] = 2;
			else arr[j][i] = 1;
		}

	}


}

void Output::DrawNOR3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;

	int Cx = r_GfxInfo.x1 + Len / 2;
	int Cy = r_GfxInfo.y1 + Wdth / 2;
	////////////////////////////////////
	int x1 = r_GfxInfo.x1;
	int x2 = r_GfxInfo.x2;
	int y1 = r_GfxInfo.y1;
	int y2 = r_GfxInfo.y2;
	correct(x1, y1);
	correct(x2, y2);

	x1 *= 15;
	x2 *= 15;
	x1 -= 15;

	y1 *= 15;
	y1 -= 15;
	y2 *= 15;
	y1 += UI.ToolBarHeight;
	y2 += UI.ToolBarHeight;


	pWind->SetPen(BLACK, 3);
	pWind->DrawLine(r_GfxInfo.x1, r_GfxInfo.y1 + 15, r_GfxInfo.x1 + 14, r_GfxInfo.y1 + 15);
	pWind->DrawLine(r_GfxInfo.x1, r_GfxInfo.y1 + 45, r_GfxInfo.x1 + 14, r_GfxInfo.y1 + 45);
	pWind->DrawLine(r_GfxInfo.x1, r_GfxInfo.y1 + 45, r_GfxInfo.x1 + 14, r_GfxInfo.y1 + 45);


	pWind->DrawLine(r_GfxInfo.x1 + 60 - 9, r_GfxInfo.y1 + 30, r_GfxInfo.x1 + 60, r_GfxInfo.y1 + 30);
	if (selected)	//use image in the highlighted case
		pWind->SetPen(BLUE, 3);
	else
		pWind->SetPen(RED, 3);

	//drawing the gate
	pWind->DrawLine(r_GfxInfo.x1 + 7, r_GfxInfo.y1 + 7, r_GfxInfo.x1 + 37, r_GfxInfo.y1 + 7);
	pWind->DrawArc(r_GfxInfo.x1 + 10 - 20, r_GfxInfo.y1 - 2 + 7, r_GfxInfo.x1 + 60 - 7 - 35, r_GfxInfo.y1 + 48 + 7, 270, 90);
	pWind->DrawLine(r_GfxInfo.x1 + 7, r_GfxInfo.y1 + 60 - 7, r_GfxInfo.x1 + 37, r_GfxInfo.y1 + 60 - 7);
	pWind->DrawArc(r_GfxInfo.x1 + 10, r_GfxInfo.y1 - 2 + 7, r_GfxInfo.x1 + 60 - 7, r_GfxInfo.y1 + 48 + 7, 270, 90);
	if (selected)	//use image in the highlighted case
		pWind->SetPen(BLUE, 2);
	else
		pWind->SetPen(RED, 2);
	pWind->DrawCircle(r_GfxInfo.x1 + 60 - 10 + 3, r_GfxInfo.y1 + 30, 5);
	///////////////////////////

	Cy -= UI.ToolBarHeight;
	Cx /= 15;
	Cy /= 15;
	Len /= 15;
	Wdth /= 15;
	for (int i = Cx - Len / 2 - 1; i <= Cx + Len / 2 + 1; i++)
	{

		for (int j = Cy - Wdth / 2; j <= Cy + Wdth / 2; j++)
		{
			if (i == Cx - Len / 2 - 1 || j == Cy - Wdth / 2 - 1 || i == Cx + Len / 2 + 1 || j == Cy + Wdth / 2 + 1) arr[j][i] = 2;
			else arr[j][i] = 1;
		}

	}


}

void Output::DrawXNOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;

	int Cx = r_GfxInfo.x1 + Len / 2;
	int Cy = r_GfxInfo.y1 + Wdth / 2;
	////////////////////////////////////
	int x1 = r_GfxInfo.x1;
	int x2 = r_GfxInfo.x2;
	int y1 = r_GfxInfo.y1;
	int y2 = r_GfxInfo.y2;
	correct(x1, y1);
	correct(x2, y2);

	x1 *= 15;
	x2 *= 15;
	x1 -= 15;

	y1 *= 15;
	y1 -= 15;
	y2 *= 15;
	y1 += UI.ToolBarHeight;
	y2 += UI.ToolBarHeight;


	pWind->SetPen(BLACK, 3);
	pWind->DrawLine(r_GfxInfo.x1, r_GfxInfo.y1 + 15, r_GfxInfo.x1 + 14, r_GfxInfo.y1 + 15);
	pWind->DrawLine(r_GfxInfo.x1, r_GfxInfo.y1 + 45, r_GfxInfo.x1 + 14, r_GfxInfo.y1 + 45);


	pWind->DrawLine(r_GfxInfo.x1 + 60 - 9, r_GfxInfo.y1 + 30, r_GfxInfo.x1 + 60, r_GfxInfo.y1 + 30);
	if (selected)	//use image in the highlighted case
		pWind->SetPen(BLUE, 3);
	else
		pWind->SetPen(RED, 3);

	//drawing the gate
	pWind->DrawLine(r_GfxInfo.x1 + 17, r_GfxInfo.y1 + 7, r_GfxInfo.x1 + 37, r_GfxInfo.y1 + 7);
	pWind->DrawArc(r_GfxInfo.x1 + 10 - 20, r_GfxInfo.y1 - 2 + 7, r_GfxInfo.x1 + 60 - 7 - 35, r_GfxInfo.y1 + 48 + 7, 270, 90);
	pWind->DrawArc(r_GfxInfo.x1 + 10 - 10, r_GfxInfo.y1 - 2 + 7, r_GfxInfo.x1 + 60 - 7 - 25, r_GfxInfo.y1 + 48 + 7, 270, 90);
	pWind->DrawLine(r_GfxInfo.x1 + 17, r_GfxInfo.y1 + 60 - 7, r_GfxInfo.x1 + 37, r_GfxInfo.y1 + 60 - 7);
	pWind->DrawArc(r_GfxInfo.x1 + 10, r_GfxInfo.y1 - 2 + 7, r_GfxInfo.x1 + 60 - 7, r_GfxInfo.y1 + 48 + 7, 270, 90);
	if (selected)	//use image in the highlighted case
		pWind->SetPen(BLUE, 2);
	else
		pWind->SetPen(RED, 2);
	pWind->DrawCircle(r_GfxInfo.x1 + 60 - 10 + 3, r_GfxInfo.y1 + 30, 5);
	///////////////////////////

	Cy -= UI.ToolBarHeight;
	Cx /= 15;
	Cy /= 15;
	Len /= 15;
	Wdth /= 15;
	for (int i = Cx - Len / 2 - 1; i <= Cx + Len / 2 + 1; i++)
	{

		for (int j = Cy - Wdth / 2; j <= Cy + Wdth / 2; j++)
		{
			if (i == Cx - Len / 2 - 1 || j == Cy - Wdth / 2 - 1 || i == Cx + Len / 2 + 1 || j == Cy + Wdth / 2 + 1) arr[j][i] = 2;
			else arr[j][i] = 1;
		}

	}


}

void Output::DrawLED(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;

	int Cx = r_GfxInfo.x1 + Len / 2;
	int Cy = r_GfxInfo.y1 + Wdth / 2;
	////////////////////////////////////
	int x1 = r_GfxInfo.x1;
	int x2 = r_GfxInfo.x2;
	int y1 = r_GfxInfo.y1;
	int y2 = r_GfxInfo.y2;
	correct(x1, y1);
	correct(x2, y2);

	x1 *= 15;
	x2 *= 15;
	x1 -= 15;

	y1 *= 15;
	y1 -= 15;
	y2 *= 15;
	y1 += UI.ToolBarHeight;
	y2 += UI.ToolBarHeight;


	if (selected)	//use image in the highlighted case
	{
		pWind->SetPen(BLUE, 3);
		pWind->SetBrush(BLUE);
	}
	else
	{
		pWind->SetPen(RED, 3);
		pWind->SetBrush(RED);
	}
	pWind->DrawRectangle(r_GfxInfo.x1 - 4, r_GfxInfo.y1 + 30 - 5, r_GfxInfo.x1 + 32 + 3, r_GfxInfo.y1 + 38 - 7);

	pWind->SetBrush(LIGHTSEAGREEN);
	pWind->DrawArc(r_GfxInfo.x1 + 13 - 15, r_GfxInfo.y1, r_GfxInfo.x1 + 46 - 15, r_GfxInfo.y1 + 50, 0, 180, FILLED);
	pWind->DrawCircle(r_GfxInfo.x1 + 20, r_GfxInfo.y1 + 10, 2);
	pWind->SetBrush(BLACK);
	pWind->DrawLine(r_GfxInfo.x1 + 15, r_GfxInfo.y1 + 30, r_GfxInfo.x1 + 15, r_GfxInfo.y1 + 45);
	pWind->DrawLine(r_GfxInfo.x1 + 23, r_GfxInfo.y1 + 31, r_GfxInfo.x1 + 23, r_GfxInfo.y1 + 42);
	///////////////////////////

	Cy -= UI.ToolBarHeight;
	Cx /= 15;
	Cy /= 15;
	Len /= 15;
	Wdth /= 15;
	for (int i = Cx - Len / 2 - 1; i <= Cx + Len / 2 + 1; i++)
	{

		for (int j = Cy - Wdth / 2; j <= Cy + Wdth / 2; j++)
		{
			if (i == Cx - Len / 2 - 1 || j == Cy - Wdth / 2 - 1 || i == Cx + Len / 2 + 1 || j == Cy + Wdth / 2 + 1) arr[j][i] = 2;
			else arr[j][i] = 1;
		}

	}


}

void Output::DrawNAND2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;

	int Cx = r_GfxInfo.x1 + Len / 2;
	int Cy = r_GfxInfo.y1 + Wdth / 2;
	////////////////////////////////////
	int x1 = r_GfxInfo.x1;
	int x2 = r_GfxInfo.x2;
	int y1 = r_GfxInfo.y1;
	int y2 = r_GfxInfo.y2;
	correct(x1, y1);
	correct(x2, y2);

	x1 *= 15;
	x2 *= 15;
	x1 -= 15;

	y1 *= 15;
	y1 -= 15;
	y2 *= 15;
	y1 += UI.ToolBarHeight;
	y2 += UI.ToolBarHeight;


	pWind->SetPen(BLACK, 3);
	pWind->DrawLine(r_GfxInfo.x1, r_GfxInfo.y1 + 30, r_GfxInfo.x1 + 15, r_GfxInfo.y1 + 30);


	pWind->DrawLine(r_GfxInfo.x1 + 60 - 9, r_GfxInfo.y1 + 30, r_GfxInfo.x1 + 60, r_GfxInfo.y1 + 30);
	if (selected)	//use image in the highlighted case
		pWind->SetPen(BLUE, 3);
	else
		pWind->SetPen(RED, 3);
	//draw buffer 
	pWind->DrawTriangle(r_GfxInfo.x1 + 15, r_GfxInfo.y1 + 7, r_GfxInfo.x1 + 15, r_GfxInfo.y1 + 60 - 7, r_GfxInfo.x1 + 60 - 15, r_GfxInfo.y1 + 30, FRAME);
	if (selected)	//use image in the highlighted case
		pWind->SetPen(BLUE, 2);
	else
		pWind->SetPen(RED, 2);
	pWind->DrawCircle(r_GfxInfo.x1 + 60 - 15 + 3, r_GfxInfo.y1 + 30, 5);
	///////////////////////////

	Cy -= UI.ToolBarHeight;
	Cx /= 15;
	Cy /= 15;
	Len /= 15;
	Wdth /= 15;
	for (int i = Cx - Len / 2 - 1; i <= Cx + Len / 2 + 1; i++)
	{

		for (int j = Cy - Wdth / 2; j <= Cy + Wdth / 2; j++)
		{
			if (i == Cx - Len / 2 - 1 || j == Cy - Wdth / 2 - 1 || i == Cx + Len / 2 + 1 || j == Cy + Wdth / 2 + 1) arr[j][i] = 2;
			else arr[j][i] = 1;
		}

	}


}
void Output::DrawConnection(GraphicsInfo r_GfxInfo, bool selected) 
{
	int x1 = r_GfxInfo.x1/15;
	int y1 = (r_GfxInfo.y1 - UI.ToolBarHeight) / 15;
	int x2 = r_GfxInfo.x2/15;
	int y2 = (r_GfxInfo.y2 - UI.ToolBarHeight) / 15;
	
	bfs(r_GfxInfo);
	int x = x2, y = y2;
	GraphicsInfo GInfo;
	if (selected) pWind->SetPen(BLUE, 3);
	else pWind->SetPen(RED, 3);
	while (x != x1 || y != y1)
	{
		ii n = mp[ii(x, y)];
		GInfo.x1 = x * 15;
		GInfo.y1 = y * 15 + UI.ToolBarHeight;
		GInfo.x2 = n.first * 15;
		GInfo.y2 = n.second * 15 + UI.ToolBarHeight;
		pWind->DrawLine(GInfo.x1, GInfo.y1, GInfo.x2, GInfo.y2);
		x = n.first;
		y = n.second;
		arr[y][x] = 3;
	}
	mp.clear();
	arr[y2][x2] = 3;
	PrintMsg("Finish2");
	return;
}

////////////////////////////////////
void Output::DrawString(string s, int x, int y) const
{
	pWind->SetPen(BLACK);
	pWind->SetFont(20, BOLD | ITALICIZED, BY_NAME, "Arial");
	pWind->DrawString(x, y, s);
}
Output::~Output()
{
	delete pWind;
}


void Output::print()
{
	for (int i = 0; i <= UI.height / 15; i++)
	{
		for (int j = 0; j <= UI.width / 15; j++) cout << arr[i][j];
		cout << endl;
	}
	cout << endl;

}


bool Output::bfs(GraphicsInfo r_GfxInfo)
{
	int x1 = r_GfxInfo.x1 / 15;
	int y1 = (r_GfxInfo.y1 - UI.ToolBarHeight) / 15;
	int x2 = r_GfxInfo.x2 / 15;
	int y2 = (r_GfxInfo.y2 - UI.ToolBarHeight) / 15;

	for (int i = 0; i < 100; i++)
	for (int j = 0; j < 100; j++) visit[i][j] = 0;
	while (!q.empty())
	{
		q.pop();
	}
	mp.clear();
	mp[ii(x1, y1)] = ii(-1, -1);
	visit[x1][y1] = 1;
	q.push(ii(x1, y1));
	
	while (!q.empty())
	{
		ii n = q.front();
		int x = n.first;
		int y = n.second;
		q.pop();
		if (x == x2 && y == y2) break;
		if ((valid(x + 1, y , 3) || (arr[y][x + 1] == 2 && y == y2 && x + 1 == x2)) && !visit[x + 1][y]++)
		{

			q.push(ii(x + 1, y));
			mp[ii(x + 1, y)] = ii(x, y);
		}
		if ((valid(x - 1, y , 3) || (arr[y][x - 1] == 2 && y == y2 && x - 1 == x2)) && !visit[x - 1][y]++)
		{

			q.push(ii(x - 1, y));
			mp[ii(x - 1, y)] = ii(x, y);
		}
		if ((valid(x, y + 1 , 3) || (arr[y + 1][x] == 2 && y + 1 == y2 && x == x2)) && !visit[x][y + 1]++)
		{

			q.push(ii(x, y + 1));
			mp[ii(x, y + 1)] = ii(x, y);
		}
		if ((valid(x, y - 1 , 3) || (arr[y - 1][x] == 2 && y - 1 == y2 && x == x2)) && !visit[x][y - 1]++)
		{
			visit[x][y - 1] = 1;
			q.push(ii(x, y - 1));
			mp[ii(x, y - 1)] = ii(x, y);
		}
	}

	if (mp[ii(x2, y2)] == ii(0, 0))
	{
		return false;
	}

	return true;
}

void Output::ShowUpperToolBar(){
	string ToolBarItems[ITMCNT];
	ToolBarItems[TOOLBARTOP] = "images\\Menu\\TOP_BAR.jpg";
	//pWind->DrawImage(ToolBarItems[0], UI.Start_Point_Top, 0, UI.Action_Width, UI.ToolBarHeight);
	pWind->SetPen(WHITE, 1);
	pWind->SetBrush(WHITE);

	if (!UI.UpperToolBarOpened){
		UI.AddButtonToggled = true;
		CreateDesignToolBar();
		for (int i = -UI.ToolBarHeight; i <= 0; i += 15){
			//CreateDesignToolBar();
			//pWind->DrawRectangle(UI.Start_Point_Top, 0, UI.Action_Width, UI.ToolBarHeight);
			pWind->DrawImage(ToolBarItems[0], UI.Start_Point_Top, i, UI.Action_Width, UI.ToolBarHeight);
		}
		UI.UpperToolBarOpened = true;
	}
	else {
		UI.AddButtonToggled = false;
		CreateDesignToolBar();
		for (int i = 0; i >= -UI.ToolBarHeight; i -= 10){
			pWind->DrawImage(ToolBarItems[0], UI.Start_Point_Top, i, UI.Action_Width, UI.ToolBarHeight);
			pWind->SetPen(WHITE, 1);
			pWind->DrawRectangle(UI.Start_Point_Top, UI.ToolBarHeight, UI.Action_Width + 100, UI.ToolBarHeight + i);
		}
		UI.UpperToolBarOpened = false;
	}
}