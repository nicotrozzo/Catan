#include "inputCardsController.h"
#include "inputEventGenerator.h"
#include "gameCoords.h"
#include "gameDefines.h"

inputCardsController::inputCardsController(catanGameModel * game) : gameModel(game)
{
}

bool inputCardsController::parseMouseEvent(mouseEvent * ev)
{
	bool ret = false;
	string resources[] = { "BRICK", "WOOD", "WOOL", "ORE", "WHEAT" };
	string player1(1, gameModel->getCurrentPlayer().getPlayerNumber());
	string player2(1, gameModel->getOtherPlayer().getPlayerNumber());
	string players[] = { player1, player2 };
	point mouseCoords = ev->getClickCoords();
	point cCoord;
	resourceType res[] = { BRICK, WOOD, WOOL, ORE, WHEAT };
	for (int i = 0; i < NUMBER_OF_RESOURCES ; i++)	
	{
		for (int j = 0; j < NUMBER_OF_PLAYERS; j++)
		{
			cCoord.x = gameCoords::cardsCoords[resources[i] + players[j]].xCoord;
			cCoord.y = gameCoords::cardsCoords[resources[i] + players[j]].yCoord;
			if ((mouseCoords.x >= cCoord.x) && ((mouseCoords.x - cCoord.x) <= OFFSET_CARD_X))
			{
				if ((mouseCoords.y >= cCoord.y) && ((mouseCoords.y - cCoord.y) <= OFFSET_CARD_Y))
				{
					if (function == OFFER_TRADE)
					{
						ret = gameModel->preparePlayerTrade(res[i], j + 1);
					}
					else if (function == BANK_TRADE)
					{
						ret = gameModel->prepareBankTrade(res[i], ((players[j] == player1) ? true : false));
					}
					else if ((function == ROBBER_CARDS) && (players[j] == player1))
					{
						ret = gameModel->prepareRobberDiscard(res[i]);
					}
				}
			}
		}
	}
	return ret;
}


bool inputCardsController::parseKeyboardEvent(keyboardEvent * ev)
{
	bool ret = true;
	switch (ev->getKey())
	{
	case '1':
		ret = selectCall(WHEAT, 1);
		break;
	case '2':
		ret = selectCall(ORE, 1);
		break;
	case '3':
		ret = selectCall(WOOL, 1);
		break;
	case '4':
		ret = selectCall(WOOD, 1);
		break;
	case '5':
		ret = selectCall(BRICK, 1);
		break;
	case 'a': case 'A':
		ret = selectCall(WHEAT, 2);
		break;
	case 'b': case 'B':
		ret = selectCall(ORE, 2);
		break;
	case 'c': case 'C':
		ret = selectCall(WOOL, 2);
		break;
	case 'd': case 'D':
		ret =selectCall(WOOD, 2);
		break;
	case 'e': case 'E':
		ret = selectCall(BRICK, 2);
		break;
	}
	return ret;
}

bool inputCardsController::setFunction(networkingEventTypes function_)
{
	bool ret = false;
	switch (function_)
	{
	case ROBBER_CARDS: case OFFER_TRADE: case BANK_TRADE:
		function = function_;
		ret = true;
		break;
	default:
		break;
	}
	return ret;
}

bool inputCardsController::selectCall(resourceType resource, unsigned char player)
{
	bool ret = false;
	switch (function)
	{
	case OFFER_TRADE:
		ret = gameModel->preparePlayerTrade(resource, player);
		break;
	case BANK_TRADE:
		ret = gameModel->prepareBankTrade(resource, player == 1 ? true : false);
		break;
	case ROBBER_CARDS:
		ret = gameModel->prepareRobberDiscard(resource);
		break;
	default:
		break;
	}
	return ret;
}

inputCardsController::~inputCardsController()
{
}
