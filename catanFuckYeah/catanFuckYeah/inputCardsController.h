#pragma once
#include "EDAInputController.h"
#include "catanGameModel.h"

class inputCardsController : public EDAInputController
{
public:
	inputCardsController(catanGameModel * game);
	
	virtual bool parseMouseEvent(mouseEvent * ev);
	virtual bool parseKeyboardEvent(keyboardEvent * ev);
	void setTrade(bool trade) { playerTrade = trade; }	// false si es trade con bank, true si es con el otro usuario
	inputControllerTypes getType() { return CTRL_CARDS; }
	~inputCardsController();
private:
	catanGameModel * gameModel;
	bool playerTrade;
};

