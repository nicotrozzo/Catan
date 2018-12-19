#pragma once
#include "eventHandling.h"
#include "inputEventGenerator.h"
class quitButtonController : public eventGenerator
{
public:
	quitButtonController();
	bool parseMouseEvent(mouseEvent * ev);
	bool parseKeyboardEvent(keyboardEvent * ev);
	genericEvent * getEvent();
	void toggleState();
private:
	bool startMenu;
	genericEvent * controllerEvent;
};
