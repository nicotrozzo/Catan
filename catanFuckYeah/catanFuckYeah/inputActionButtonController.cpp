#include "inputActionButtonController.h"
#include "gameCoords.h"
#include "gameDefines.h"
#include "playingFSM.h"

inputActionButtonController::inputActionButtonController(catanGameModel * game, netwEmisor *emisor, timerEventGenerator * ansTimer) : gameModel(game)
{
	netEmisorEv = emisor;
	answerTimer = ansTimer;
}


bool inputActionButtonController::parseMouseEvent(mouseEvent * ev)
{
	bool ret = false;
	point mouseCoords = ev->getClickCoords();
	point bCoords;
	string tradeButtons[] = { "PLAYER_TRADE", "BANK_TRADE" };
	
	bCoords.x = gameCoords::buttonCoords["END_TURN"].xCoord;
	bCoords.y = gameCoords::buttonCoords["END_TURN"].yCoord;
	if ((mouseCoords.x >= bCoords.x) && (mouseCoords.x - bCoords.x <= OFFSET_END_TURN_X))
	{
		if ((mouseCoords.y >= bCoords.y) && (mouseCoords.y - bCoords.y <= OFFSET_END_TURN_Y))
		{
			if (!gameModel->initState())
			{
				ret = true;
				netEmisorEv->sendPackage(PASS);
				controllerEvent = new playingFSMEvent(CHANGE_STATE);
				answerTimer->startTimer();
			}
		}
	}

	for (int i = 0; i < 2 && !ret; i++)
	{
		bCoords.x = gameCoords::buttonCoords[tradeButtons[i]].xCoord;
		bCoords.y = gameCoords::buttonCoords[tradeButtons[i]].yCoord;
		if ((mouseCoords.x >= bCoords.x) && (mouseCoords.x - bCoords.x <= OFFSET_TRADE_X))
		{
			if ((mouseCoords.y >= bCoords.y) && (mouseCoords.y - bCoords.y <= OFFSET_TRADE_Y))
			{
				if (!gameModel->initState())
				{
					if (tradeButtons[i] == "PLAYER_TRADE")
					{
						ret = gameModel->preparePlayerTrade(DESSERT, 1);
					}
					else if (tradeButtons[i] == "BANK_TRADE")
					{
						ret = gameModel->prepareBankTrade(DESSERT, 1);
					}
					if (ret)
					{
						controllerEvent = new playingFSMCardsEv(tradeButtons[i] == "PLAYER_TRADE");
					}
				}
			}
		}
	}
	return ret;
}

bool inputActionButtonController::parseKeyboardEvent(keyboardEvent * ev)
{
	bool ret = false;
	if (!gameModel->initState())
	{
		switch (ev->getKey())
		{
		case 'P':
			netEmisorEv->sendPackage(PASS);
			controllerEvent = new playingFSMEvent(CHANGE_STATE);
			answerTimer->startTimer();
			ret = true;
			break;
		case 'B':
			ret = gameModel->prepareBankTrade(DESSERT, 1);
			break;
		case 'O':
			ret = gameModel->preparePlayerTrade(DESSERT, 1);
			break;
		}
		if (ret && (ev->getKey() != 'P'))
		{
			controllerEvent = new playingFSMCardsEv(ev->getKey() == 'O');
		}
	}
	return ret;
}

inputActionButtonController::~inputActionButtonController()
{
}
