#include "ApplicationManager.h"
#include "Actions\AddANDgate2.h"
#include "Actions\AddNOTgate.h"
#include "Actions\AddORgate2.h"
#include "Actions\AddXORgate2.h"
#include "Actions\AddConnection.h"






ApplicationManager::ApplicationManager()
{
	CompCount = 0;

	for(int i=0; i<MaxCompCount; i++)
		CompList[i] = NULL;

	//Creates the Input / Output Objects & Initialize the GUI
	OutputInterface = new Output();
	InputInterface = OutputInterface->CreateInput();
}
////////////////////////////////////////////////////////////////////
void ApplicationManager::AddComponent(Component* pComp)
{
	CompList[CompCount++] = pComp;		
}
////////////////////////////////////////////////////////////////////

ActionType ApplicationManager::GetUserAction()
{
	//Call input to get what action is reuired from the user
	return InputInterface->GetUserAction(); 	
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = NULL;
	switch (ActType)
	{
		case ADD_AND_GATE_2:
			pAct= new AddANDgate2(this);
			break;
		case ADD_OR_GATE_2 :
			pAct = new AddORgate2(this);
			break;
		case ADD_INV:
			pAct = new AddNOTgate(this);
			break;
		case ADD_XOR_GATE_2 :
			pAct = new AddXORgate2(this);
			break;
		case ADD_CONNECTION:
			pAct = new AddConnection(this);
			break;
		case ADD_COMPONENTS:
			OutputInterface->ShowUpperToolBar();
			//create design toolbar
			break;

		case EXIT:
			///TODO: create ExitAction here
			break;
	}
	if(pAct)
	{
		pAct->Execute();
		delete pAct;
		pAct = NULL;
	}
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::UpdateInterface()
{
	OutputInterface->ClearDrawingArea();
		for(int i=0; i<CompCount; i++)
		if ( CompList[i]->isGate())CompList[i]->Draw(OutputInterface);
		for (int i = 0; i<CompCount; i++)
		if (!CompList[i]->isGate())CompList[i]->Draw(OutputInterface);
		OutputInterface->print();
	

}

////////////////////////////////////////////////////////////////////
Input* ApplicationManager::GetInput()
{
	return InputInterface;
}

////////////////////////////////////////////////////////////////////
Output* ApplicationManager::GetOutput()
{
	return OutputInterface;
}

////////////////////////////////////////////////////////////////////

Component*  ApplicationManager::IsGate(int  x, int y)
{
	GraphicsInfo GI;
	Component* comp;
	for (int i = 0; i < CompCount; i++)
	{
		GI = CompList[i]->Get();
		GI.y1 -= UI.ToolBarHeight;
		GI.y2 -= UI.ToolBarHeight;
		GI.y1 /= 15;
		GI.y2 /= 15;
		GI.x1 /= 15;
		GI.x2 /= 15;
		if (x >= GI.x1-1 && x <= GI.x2+1 && y >= GI.y1-1 && y <= GI.y2+1 && CompList[i]->isGate()) return comp = CompList[i];
		
	}
	return NULL;
}

ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<CompCount; i++)
		delete CompList[i];
	delete OutputInterface;
	delete InputInterface;
	
}

