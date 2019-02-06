#pragma once
#include "EDAInputController.h"
#include "netwEmisor.h"

class inputRematchController :	public EDAInputController
{
public:
	inputRematchController(netwEmisor * emisor_);
	virtual inputControllerTypes getType() { return CTRL_REMATCH; }
	virtual bool parseMouseEvent(mouseEvent * ev);
	virtual bool parseKeyboardEvent(keyboardEvent * ev);
	void expectEvent();
	void dontExpectEvent();
private:
	netwEmisor * emisor;
	bool expectingEvent;
};

