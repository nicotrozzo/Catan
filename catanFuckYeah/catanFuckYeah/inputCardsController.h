#pragma once
#include "EDAInputController.h"
#include "catanGameModel.h"

class inputCardsController : public EDAInputController
{
public:
	inputCardsController(catanGameModel * game);
	
	virtual void parseMouseEvent(mouseEvent * ev);
	virtual void parseKeyboardEvent(keyboardEvent * ev);
	void setFunction(networkingEventTypes function_);
	inputControllerTypes getType() { return CTRL_CARDS; }
	~inputCardsController();
private:
	catanGameModel * gameModel;
	networkingEventTypes function;
	void selectCall(resourceType resource, unsigned char player);
};

