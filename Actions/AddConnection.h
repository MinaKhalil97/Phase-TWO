#ifndef _ADD_CONNECTION_H
#define _ADD_CONNECTION_H

#include "action.h"
#include "..\ApplicationManager.h"
#include "..\Components\Connection.h"
#include "..\Components\Gate.h"
class AddConnection:	public Action
{
private:
	//Parameters for rectangular area to be occupied by the gate
	int x1, y1, x2, y2;	//point 1 , point 2

	InputPin* InComp;
	OutputPin* OutComp;
	bool flag;
public:
	AddConnection(ApplicationManager *pApp);
	virtual ~AddConnection(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};

#endif