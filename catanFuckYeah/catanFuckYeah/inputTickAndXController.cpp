#include "inputTickAndXController.h"
#include "gameDefines.h"
#include "gameCoords.h"
#include "playingFSM.h"

inputTickAndXController::inputTickAndXController(catanGameModel * game, netwEmisor * emisor)
{
	netEmisorEv = emisor;
	gameModel = game;
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
{	//acordarse de hacer delete cuando pedimos el evento para no caer en memoty leaks
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
		construction_t building; //para ver el building pendiente
		switch (actionToDo)
		{
		case TICK_OPP_TRADE:
			ret = gameModel->playerTrade();
			netEmisorEv->sendPackage(YES);
			if (ret == false)
			{
				controllerEvent = new playingFSMErrorEv("Error en trueque invalido");
			}
			break;
		case TICK_BANK_TRADE:
			if (gameModel->bankTradeReady())
			{
				ret = gameModel->bankTrade();
				if (ret)
				{
					evType = CARDS_EV;
					string message;
					string myRes(1, gameModel->getPlayerSelectedResource().res);
					string bankRes(1, gameModel->getBankSelectedResource());
					for (int i = 0; i < gameModel->getPlayerSelectedResource().resCount; i++)
					{
						message += myRes;
					}
					netEmisorEv->sendPackage(BANK_TRADE, to_string(message.length() + bankRes.length()) + message + bankRes);
				}
			}
			break;
		case TICK_OWN_TRADE:
			if (ret = gameModel->playerTradeReady())
			{
				cards tradeCards[] = { gameModel->getP1SelectedCardsForTrade(), gameModel->getP2SelectedCardsForTrade() };
				int ownResCount = static_cast<int>(tradeCards[0].totalCardsCount());
				int oppResCount = static_cast<int>(tradeCards[1].totalCardsCount());
				string myRes, oppRes;
				string* tradeRes[] = { &myRes, &oppRes };
				for (int i = 0; i < NUMBER_OF_PLAYERS; i++)
				{
					for (int j = 0; j < tradeCards[i].brick; j++)
					{
						*(tradeRes[i]) += "L";
					}
					for (int j = 0; j < tradeCards[i].ore; j++)
					{
						*(tradeRes[i]) += "P";
					}
					for (int j = 0; j < tradeCards[i].wool; j++)
					{
						*(tradeRes[i]) += "O";
					}
					for (int j = 0; j < tradeCards[i].wood; j++)
					{
						*(tradeRes[i]) += "M";
					}
					for (int j = 0; j < tradeCards[i].wheat; j++)
					{
						*(tradeRes[i]) += "T";
					}
				}
				netEmisorEv->sendTrade(OFFER_TRADE, ownResCount, myRes, oppResCount, oppRes);
				evType = TICK_EV;
			}
			break;
		case TICK_BUILD:
			if (gameModel->isConstructing())
			{
				building = gameModel->getMap()->getPendingConstruction();
				ret = gameModel->construct();
			}
			if (ret)
			{
				evType = TICK_EV;
				netEmisorEv->sendPackage(building.type, building.coords);
			}
			break;
		case TICK_ROBB_CARDS:
			if (gameModel->robberCardsReady())
			{
				cards myDiscard = gameModel->getP1DiscardRobberCards();
				if (ret = gameModel->discardCurrentPlayer())
				{
					string info = "";
					for (int j = 0; j < myDiscard.brick; j++)
					{
						info += "L";
					}
					for (int j = 0; j < myDiscard.ore; j++)
					{
						info += "P";
					}
					for (int j = 0; j < myDiscard.wool; j++)
					{
						info += "O";
					}
					for (int j = 0; j < myDiscard.wood; j++)
					{
						info += "M";
					}
					for (int j = 0; j < myDiscard.wheat; j++)
					{
						info += "T";
					}
					netEmisorEv->sendPackage(ROBBER_CARDS, info);
				}
			}
			break;
		}
	}
	else
	{
		switch (actionToDo)
		{
		case TICK_OPP_TRADE: 
			gameModel->clearTrades();
			netEmisorEv->sendPackage(NO);
			ret = true;
			break;
		case TICK_BANK_TRADE: case TICK_OWN_TRADE:
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
