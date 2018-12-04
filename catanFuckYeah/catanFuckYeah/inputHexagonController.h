#pragma once
#include "EDAInputController.h"
#include "catanGameModel.h"

class inputHexagonController : public EDAInputController
{
public:
	inputHexagonController(catanGameModel * game);
	virtual void parseMouseEvent(mouseEvent * ev);
	virtual void parseKeyboardEvent(keyboardEvent * ev);
	inputControllerTypes getType() { return CTRL_HEXAGON; }
	~inputHexagonController();
private:
	catanGameModel * game;
};

