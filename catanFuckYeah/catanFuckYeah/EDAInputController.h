#pragma once
#include "inputEventGenerator.h"

typedef enum inputControllerTypes { CTRL_ACTION_BUTTON, CTRL_EDGE_AND_VERTEX, CTRL_CARDS, CTRL_HEXAGON, CTRL_TICKANDX };

class EDAInputController : public eventGenerator
{
public:
	EDAInputController() : controllerEvent(nullptr) {}
	virtual inputControllerTypes getType() = 0;
	virtual void parseMouseEvent(mouseEvent * ev) = 0;
	virtual void parseKeyboardEvent(keyboardEvent * ev) = 0;
	genericEvent * getEvent() { return controllerEvent; }
private:
	genericEvent * controllerEvent;
};
