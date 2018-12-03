#pragma once
#include "EDAInputController.h"

class inputCardsController : public EDAInputController
{
public:
	inputCardsController();
	virtual void parseMouseEvent(mouseEvent * ev);
	virtual void parseKeyboardEvent(keyboardEvent * ev);
	~inputCardsController();
};

