#include "AddConnection.h"
#include "..\ApplicationManager.h"

AddConnection::AddConnection(ApplicationManager *pApp):Action(pApp)
{
	InComp = NULL;
	OutComp = NULL;
}

AddConnection::~AddConnection(void)
{
}

void AddConnection::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	Component* comp1 = NULL ;
	Component* comp2 = NULL;
	flag = true;
	pOut->PrintMsg("Draw a connection");
	//Print Action Message
	//Print Action Message
	//pIn->GetPointClicked(x1, y1);
	pOut->PrintMsg("Please Chose The Source Gate ");
	pIn->GetPointClicked(x1, y1);
	correct(x1, y1);

	 comp1 = pManager->IsGate(x1, y1);
	if ( comp1 == NULL )
	{
		pOut->PrintMsg("Sorry the connection can't be drawn");
		pIn->GetPointClicked(x1, y1);
		flag = false;
		return;
	}
	OutComp=comp1->IsFullOutputs();
	if (OutComp == NULL)
	{
		pOut->PrintMsg("Sorry the connection can't be drawn");
		pIn->GetPointClicked(x1, y1);
		flag = false;
		return;
	}

	pOut->PrintMsg("Please Chose The Destination Gate ");
	pIn->GetPointClicked(x2, y2);
	
	correct(x2, y2);
	
	 comp2 = pManager->IsGate(x2, y2);
	if (comp2 == NULL || comp1 == comp2)
	{
		pOut->PrintMsg("Sorry the connection can't be drawn");
		pIn->GetPointClicked(x1, y1);
		flag = false;
		return;
	}
	InComp = comp2->IsFullInputs();
	if (InComp == NULL)
	{
		pOut->PrintMsg("Sorry the connection can't be drawn");
		pIn->GetPointClicked(x1, y1);
		flag = false;
		return;
	}

	//Clear Status Bar
	pOut->ClearStatusBar();
	 
}

void AddConnection::Execute()
{
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	if (!flag) return;
	GraphicsInfo GInfo;

	GInfo.x1 = x1 * 15;
	GInfo.x2 = x2 * 15;
	GInfo.y1 = y1 * 15;
	GInfo.y2 = y2 * 15;
	GInfo.y1 += UI.ToolBarHeight;
	GInfo.y2 += UI.ToolBarHeight;

	if (pOut->bfs(GInfo) == false)
	{
		pOut->PrintMsg("Sorry the connection can't be drawn");
		pIn->GetPointClicked(x1, y1);
		return;
	}

	Connection *pA = new Connection(GInfo, OutComp, InComp);
	pManager->AddComponent(pA);

}

void AddConnection::Undo()
{}

void AddConnection::Redo()
{}

