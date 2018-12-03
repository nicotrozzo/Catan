#pragma once
#include "EDAInputController.h"

class inputHexagonController : public EDAInputController
{
public:
	inputHexagonController();
	virtual void parseMouseEvent(mouseEvent * ev);
	virtual void parseKeyboardEvent(keyboardEvent * ev);
	~inputHexagonController();
};

