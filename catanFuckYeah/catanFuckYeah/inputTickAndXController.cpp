#include "inputTickAndXController.h"
#include "gameDefines.h"
#include "gameCoords.h"
#include "playingFSM.h"

inputTickAndXController::inputTickAndXController(catanGameModel * game)
{

}

bool inputTickAndXController::parseMouseEvent(mouseEvent * ev)
{
	bool ret = false;
	point mouseCoords = ev->getClickCoords();
	point tickCoord, crossCoord;
	tickCoord.x = gameCoords::buttonCoords["YES"].xCoord;
	tickCoord.y = gameCoords::buttonCoords["YES"].yCoord;
	crossCoord.x = gameCoords::buttonCoords["NO"].xCoord;
	crossCoord.y = gameCoords::buttonCoords["NO"].yCoord;
	if(((mouseCoords.x >= tickCoord.x) &&(mouseCoords.x - tickCoord.x < OFFSET_YES_X)) && ((mouseCoords.y >= tickCoord.y) && (mouseCoords.y - tickCoord.y < OFFSET_YES_Y)))
	{
		ret = selectionCall(1);
	}
	else if (((mouseCoords.x >= crossCoord.x) && (mouseCoords.x - crossCoord.x < OFFSET_NO_X)) && ((mouseCoords.y >= crossCoord.y) && (mouseCoords.y - crossCoord.y < OFFSET_NO_Y)))
	{
		ret = selectionCall(0);
	}
	return ret;
}

bool inputTickAndXController::parseKeyboardEvent(keyboardEvent * ev)
{
	bool ret = false;
	switch (ev->getKey())
	{
	case 'y': case 'Y':
		ret = selectionCall(1);
		break;
	case 'n': case 'N':
		ret = selectionCall(0);
		break;
	default:
		break;
	}
	return ret;
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

bool inputTickAndXController::selectionCall(bool yes)
{
	bool ret = false;
	playingFSMEvTypes evType = CHANGE_STATE;
	if (yes)
	{
		switch (actionToDo)
		{
		case TICK_OPP_TRADE:
			ret = gameModel->playerTrade();
			if (ret == false)
			{
				controllerEvent = new playingFSMErrorEv("Error en trueque invalido");
			}
			break;
		case TICK_BANK_TRADE:
			if (gameModel->bankTradeReady())
			{
				ret = gameModel->bankTrade();
			}
			break;
		case TICK_OWN_TRADE:
			if (gameModel->playerTradeReady())
			{
				ret = gameModel->playerTrade();	//aca generar evento de TICK
				if (ret == true)
				{
					evType = TICK_EV;
				}
			}
			break;
		case TICK_BUILD:
			ret = gameModel->construct();
			break;
		case TICK_ROBB_CARDS:
			if (gameModel->robberCardsReady())
			{
				ret = gameModel->discardCurrentPlayer();
			}
			break;
		}
	}
	else
	{
		switch (actionToDo)
		{
		case TICK_OPP_TRADE: case TICK_BANK_TRADE: case TICK_OWN_TRADE:
			gameModel->clearTrades();
			ret = true;
			break;
		case TICK_BUILD:
			gameModel->cancelConstruction();
			ret = true;
			break;
		case TICK_ROBB_CARDS:
			gameModel->clearRobberCards();
			ret = true;
			break;
		}
	}
	if (ret == true)
	{
		controllerEvent = new playingFSMEvent(evType);
	}
	return ret;
}
