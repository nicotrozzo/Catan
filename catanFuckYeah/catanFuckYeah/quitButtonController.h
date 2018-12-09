#pragma once
#include "eventHandling.h"
#include "inputEventGenerator.h"
class quitButtonController : public eventGenerator
{
public:
	quitButtonController();
	void parseMouseEvent(mouseEvent * ev);
	void parseKeyboardEvent(keyboardEvent * ev);
	genericEvent * getEvent();
	void toggleState();
private:
	bool startMenu;
	genericEvent * controllerEvent;
};
