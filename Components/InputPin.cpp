#include "InputPin.h"

InputPin::InputPin()
{}

void InputPin::setComponent(Component *pCmp)
{
	this->pComp = pCmp;
	type = InPin;

}
Component* InputPin::getComponent()
{
	return pComp;
	
}