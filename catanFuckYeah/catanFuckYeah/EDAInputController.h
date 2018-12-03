#pragma once
#include "inputEventGenerator.h"

class EDAInputController
{
public:
	virtual void parseMouseEvent(mouseEvent * ev) = 0;
	virtual void parseKeyboardEvent(keyboardEvent * ev) = 0;
};
