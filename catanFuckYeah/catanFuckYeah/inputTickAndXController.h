#pragma once
#include "EDAInputController.h"
#include "catanGameModel.h"

typedef enum tickActions_t{ TICK_OPP_TRADE, TICK_BANK_TRADE, TICK_OWN_TRADE, TICK_BUILD, TICK_ROBB_CARDS};

class inputTickAndXController :	public EDAInputController
{
public:
	inputTickAndXController();
	virtual inputControllerTypes getType() { return CTRL_TICKANDX; }
	virtual void parseMouseEvent(mouseEvent * ev);
	virtual void parseKeyboardEvent(keyboardEvent * ev);
	void setActionToDo(tickActions_t action);	
	~inputTickAndXController();

private:
	catanGameModel * game;
	tickActions_t actionToDo;
	bool validAction(tickActions_t action);
};

