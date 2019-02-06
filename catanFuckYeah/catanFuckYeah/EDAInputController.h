#pragma once
#include "inputEventGenerator.h"

enum inputControllerTypes { CTRL_ACTION_BUTTON, CTRL_EDGE_AND_VERTEX, CTRL_CARDS, CTRL_HEXAGON, CTRL_TICKANDX , CTRL_STATE, CTRL_REMATCH};

class EDAInputController : public eventGenerator
{
public:
	EDAInputController() : controllerEvent(nullptr) {}
	virtual inputControllerTypes getType() = 0;
	virtual bool parseMouseEvent(mouseEvent * ev) = 0;
	virtual bool parseKeyboardEvent(keyboardEvent * ev) = 0;
	genericEvent * getEvent()
	{
		genericEvent * temp = nullptr;
		if (controllerEvent != nullptr)
		{
			temp = controllerEvent;
			controllerEvent = nullptr;
		}
		return temp; 
	}

protected:
	genericEvent * controllerEvent;
};
