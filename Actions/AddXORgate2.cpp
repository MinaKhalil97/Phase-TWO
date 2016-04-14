#include "AddXORgate2.h"
#include "..\ApplicationManager.h"

AddXORgate2::AddXORgate2(ApplicationManager *pApp):Action(pApp)
{
}

AddXORgate2::~AddXORgate2(void)
{
}

void AddXORgate2::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("2-Input XOR Gate: Click to add the gate");

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
			if (j >= 0 && !pOut->valid(i,j)) { flag = true; break; }
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

void AddXORgate2::Execute()
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
	XOR2 *pA=new XOR2(GInfo, AND2_FANOUT); 
	pManager->AddComponent(pA);
}

void AddXORgate2::Undo()
{}

void AddXORgate2::Redo()
{}

