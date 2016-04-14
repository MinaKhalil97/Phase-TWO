#include "AddANDgate2.h"
#include "..\ApplicationManager.h"

AddANDgate2::AddANDgate2(ApplicationManager *pApp):Action(pApp)
{
}

AddANDgate2::~AddANDgate2(void)
{
}

void AddANDgate2::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("2-Input AND Gate: Click to add the gate");
  
	//Wait for User Input
	int Len = UI.AND2_Width / 15;
	int Wdth = UI.AND2_Height / 15;

	bool flag = false;
	int t = 0;
	do
	{
		flag = false;

		if (t) {
			pOut->PrintMsg("Please Chose A Right Position ");
		}
		pIn->GetPointClicked(Cx, Cy);
		correct(Cx, Cy);
		for (int i = Cx - Len / 2 - 1; i <= Cx + Len / 2 + 1; i++)
		{
			if (i >= 0)
			for (int j = Cy - Wdth / 2 - 1; j <= Cy + Wdth / 2 + 1; j++)
			if (!pOut->valid(i , j)) { flag = true; break; }
			if (flag) break;
		}

		t++;

	} while (flag);

	
	//Clear Status Bar
	pOut->ClearStatusBar();
	
	
}

void AddANDgate2::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();
	
	//Calculate the rectangle Corners
	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;
	
	GraphicsInfo GInfo;

	GInfo.x1 = Cx * 15 - (Len) / 2;
	GInfo.x2 = Cx * 15 + (Len) / 2;
	GInfo.y1 = Cy * 15 - (Wdth) / 2;
	GInfo.y2 = Cy * 15 + (Wdth) / 2;
	GInfo.y1 += UI.ToolBarHeight;
	GInfo.y2 += UI.ToolBarHeight;



	AND2 *pA=new AND2(GInfo, AND2_FANOUT); 
	pManager->AddComponent(pA);
}

void AddANDgate2::Undo()
{}

void AddANDgate2::Redo()
{}

