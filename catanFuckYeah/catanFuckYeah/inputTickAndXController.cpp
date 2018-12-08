#include "inputTickAndXController.h"
#include "gameDefines.h"
#include "gameCoords.h"


inputTickAndXController::inputTickAndXController(catanGameModel * game)
{

}

void inputTickAndXController::parseMouseEvent(mouseEvent * ev)
{
	point mouseCoords = ev->getClickCoords();
	gameCoords::buttonCoords["YES"];
	if(mouseCoords.x > )
	{
		switch (actionToDo)
		{
		case TICK_OPP_TRADE:

			break;
		case TICK_BANK_TRADE:
		
			break;
		case TICK_OWN_TRADE:
			
			break;
		case TICK_BUILD:
			
			break;
		case TICK_ROBB_CARDS:
			
			break;
		}
	}
	//else if (clickEnCruz)
	//{
		switch (actionToDo)
		{
		case TICK_OPP_TRADE:


			break;
		case TICK_BANK_TRADE:

			break;
		case TICK_OWN_TRADE:

			break;
		case TICK_BUILD:

			break;
		case TICK_ROBB_CARDS:

			break;
		}




	//}

}

void inputTickAndXController::parseKeyboardEvent(keyboardEvent * ev)
{

}

void inputTickAndXController::setActionToDo(tickActions_t action)
{
	if (validAction(action))
	{
		actionToDo = action;
	}
}


inputTickAndXController::~inputTickAndXController()
{
}

bool inputTickAndXController::validAction(tickActions_t action)
{
	return (action >= TICK_OPP_TRADE) && (action <= TICK_ROBB_CARDS);
}
