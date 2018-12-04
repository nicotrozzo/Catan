#pragma once
#include "inputEventGenerator.h"

typedef enum inputControllerTypes { CTRL_ACTION_BUTTON, CTRL_EDGE_AND_VERTEX, CTRL_CARDS, CTRL_HEXAGON }

class EDAInputController
{
public:
	virtual inputControllerTypes getType() = 0;
	virtual void parseMouseEvent(mouseEvent * ev) = 0;
	virtual void parseKeyboardEvent(keyboardEvent * ev) = 0;
};
