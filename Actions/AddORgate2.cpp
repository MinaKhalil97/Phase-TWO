#include "AddORgate2.h"
#include "..\ApplicationManager.h"

AddORgate2::AddORgate2(ApplicationManager *pApp):Action(pApp)
{
}

AddORgate2::~AddORgate2(void)
{
}

void AddORgate2::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("2-Input OR Gate: Click to add the gate");

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
		for (int i = Cx - Len / 2; i <= Cx + Len / 2; i++)
		{
			if (i >= 0)
			for (int j = Cy - Wdth / 2; j <= Cy + Wdth / 2; j++)
			if (!pOut->valid(i,j) ) { flag = true; break; }
			if (flag) break;
		}

		t++;

	} while (flag);

	for (int i = Cx - Len / 2 - 1; i <= Cx + Len / 2 + 1; i++)
	{
		if (i >= 0)
		for (int j = Cy - Wdth / 2 - 1; j <= Cy + Wdth / 2 + 1; j++) if (j >= 0) pOut->SetTaken(i, j);
	}


	//Clear Status Bar
	pOut->ClearStatusBar();
	
}

void AddORgate2::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();
	
	//Calculate the rectangle Corners
	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;
	
	GraphicsInfo GInfo; //Gfx info to be used to construct the AND2 gate
	
	GInfo.x1 = Cx * 15 - (Len) / 2;
	GInfo.x2 = Cx * 15 + (Len) / 2;
	GInfo.y1 = Cy * 15 - (Wdth) / 2;
	GInfo.y2 = Cy * 15 + (Wdth) / 2;
	GInfo.y1 += UI.ToolBarHeight;
	GInfo.y2 += UI.ToolBarHeight;
	OR2 *pA=new OR2(GInfo, AND2_FANOUT); 
	pManager->AddComponent(pA);
}

void AddORgate2::Undo()
{}

void AddORgate2::Redo()
{}

