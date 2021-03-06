#ifndef CONST_H
#define CONST_H

//This header file contains some defenitions to be used all over the application

//All possible actions
enum ActionType
{
	ADD_Buff,			//Add 1-input Buffer gate
	ADD_INV,			//Add 1-input Inverter gate
	ADD_AND_GATE_2,		//Add 2-input AND gate
	ADD_OR_GATE_2,		//Add 2-input OR gate
	ADD_NAND_GATE_2,	//Add 2-input NAND gate
	ADD_NOR_GATE_2,		//Add 2-input NOR gate
	ADD_XOR_GATE_2,		//Add 2-input XOR gate
	ADD_XNOR_GATE_2,	//Add 2-input XNOR gate
	ADD_AND_GATE_3,		//Add 3-input AND gate
	ADD_NOR_GATE_3,		//Add 3-input NOR gate
	ADD_XOR_GATE_3,		//Add 3-input XOR gate
	ADD_Switch,			//Add Switch
	ADD_LED,			//Add LED
	ADD_CONNECTION,		//Add Wire Connection

	ADD_Label,			//Add Label to a Component, a Connection
	EDIT_Label,			//Edit Label of a Component, a Connection
	ZOOM,
	CREATE_TRUTH_TABLE,	//Create Truth Table of the Circuit

	Change_Switch,		//Change Switch Status in Simulation Mode

	SELECT,		//Select a Component, a Connection
	DEL,		//Delete a Component, a Connection
	MOVE,		//Move a Component, a Connection
	NEW,


	SAVE,		//Save the whole Circuit to a file
	LOAD,		//Load a Circuit from a file

	UNDO,		//Undo the last Action preformed
	REDO,		//Redo the last Action canceled

	DSN_MODE,	//Switch to Design mode
	SIM_MODE,	//Switch to Simulatiom mode
	ADD_COMPONENTS,
	EXIT,		//Exit the application

	STATUS_BAR,		//A click on the status bar
	DSN_TOOL,	//A click on an empty place in the design tool bar,
	EMPTY_AREA,
	HUNDO, HREDO, HDEL, HZOOM, HTRUTH, HSIM

};

//Possible Status for the pin
enum STATUS
{
	LOW,
	HIGH
};

enum  MODE	//Modes of operation
{
	DESIGN,
	SIMULATION
};

enum DsnToolBar //The toolbar actions
{
	TOOLBARTOP,
	TOOLBARLEFT,
	TOOLBARRIGHT,


	ITMCNT,

};


enum DsgnMenuItemTop//The items of the design menu (you should add more items)
{
	ITM_BUFF,
	ITM_NOT,
	ITM_AND2,
	ITM_NAND2,
	ITM_OR2,
	ITM_NOR2,
	ITM_XOR2,
	ITM_XNOR2,
	ITM_AND3,
	ITM_NOR3,
	ITM_XOR3,
	ITM_LED,
	ITM_SWITCH,
	ITM_CONNECTION,
	ITM_DSN_CNT


};
enum DsgnMenuItemLeft
{
	ITM_ADD,
	ITM_NEW,
	ITM_OPEN,
	ITM_SAVE,
	ITM_EXIT,
	ITM_DSN_CNT_LEFT



};
enum DsgnMenuItemRight
{
	ITM_UNDO,
	ITM_REDO,
	ITM_DELETE,
	ITM_ZOOM,
	ITM_TRUTHTABLE,
	ITM_SIMULATE

};



enum SimMenuItem //The items of the simulation menu (you should add more items)
{/* shlnahom 33ashan 3amlen zayhom fo2 !!
 //Note: Items are ordered here as they appear in menu
 ITM_SIM,	//Simulate menu item
 ITM_TRUTH,	//Truth table menu item
 ITM_DSGNMODE,
 ITM_EXIT,
 //TODO:Add more items names here

 ITM_SIM_CNT		//no. of simulation menu items ==> This should be the last line in this enum
 */
};

//Maximum number of input pins that can be connected to any output pin
#define MAX_CONNS 20

//assume fan out is 5 for now it can be read from the user or can be predefined as const
enum FANOUT
{
	AND2_FANOUT = 5	//Default fan out of 2-input AND gate
};


enum PinType
{
	OPin,
	InPin
};
//A structure to contain drawing parameters for each component
//Each component occupies a rectangluar area so it needs 2 points to represent that area
//this structure can be extended if desired
struct GraphicsInfo
{
	int x1, y1, x2, y2;
};

#ifndef NULL
#define NULL 0
#endif

#endif