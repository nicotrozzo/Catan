#include "inputCardsController.h"
#include "inputEventGenerator.h"
#include "gameCoords.h"
#include "gameDefines.h"

inputCardsController::inputCardsController(catanGameModel * game) : gameModel(game)
{
}

void inputCardsController::parseMouseEvent(mouseEvent * ev)
{
	string resources[] = { "BRICK", "WOOD", "WOOL", "ORE", "WHEAT" };
	string player1(1, gameModel->getCurrentPlayer().getPlayerNumber());
	string player2(1, gameModel->getOtherPlayer().getPlayerNumber());
	string players[] = { player1, player2 };
	point mouseCoords = ev->getClickCoords();
	point cCoord;
	resourceType res[] = { BRICK, WOOD, WOOL, ORE, WHEAT };
	for (int i = 0; i < NUMBER_OF_RESOURCES ; i++)	
	{
		for (int j = 0; j < 2; j++)
		{
			cCoord.x = gameCoords::cardsCoords[resources[i] + players[j]].xCoord;
			cCoord.y = gameCoords::cardsCoords[resources[i] + players[j]].yCoord;
			if ((mouseCoords.x >= cCoord.x) && ((mouseCoords.x - cCoord.x) <= OFFSET_CARD_X))
			{
				if ((mouseCoords.y >= cCoord.y) && ((mouseCoords.y - cCoord.y) <= OFFSET_CARD_Y))
				{
					if (function == OFFER_TRADE)
					{
						gameModel->preparePlayerTrade(res[i], j + 1);
					}
					else if (function == BANK_TRADE)
					{
						gameModel->prepareBankTrade(res[i], ((players[j] == player1) ? true : false));
					}
					else if ((function == ROBBER_CARDS) && (players[j] == player1))
					{
						gameModel->prepareRobberDiscard(res[i]);
					}
				}
			}
		}
	}

}


void inputCardsController::parseKeyboardEvent(keyboardEvent * ev)
{
	switch (ev->getKey())
	{
	case '1':
		selectCall(WHEAT, 1);
		break;
	case '2':
		selectCall(ORE, 1);
		break;
	case '3':
		selectCall(WOOL, 1);
		break;
	case '4':
		selectCall(WOOD, 1);
		break;
	case '5':
		selectCall(BRICK, 1);
		break;
	case 'a': case 'A':
		selectCall(WHEAT, 2);
		break;
	case 'b': case 'B':
		selectCall(ORE, 2);
		break;
	case 'c': case 'C':
		selectCall(WOOL, 2);
		break;
	case 'd': case 'D':
		selectCall(WOOD, 2);
		break;
	case 'e': case 'E':
		selectCall(BRICK, 2);
		break;
	}
}

void inputCardsController::setFunction(networkingEventTypes function_)
{
	switch (function_)
	{
	case ROBBER_CARDS: case OFFER_TRADE: case BANK_TRADE:
		function = function_;
		break;
	default:
		break;
	}
}

void inputCardsController::selectCall(resourceType resource, unsigned char player)
{
	switch (function)
	{
	case OFFER_TRADE:
		gameModel->preparePlayerTrade(resource, player);
		break;
	case BANK_TRADE:
		gameModel->prepareBankTrade(resource, player == 1 ? true : false);
		break;
	case ROBBER_CARDS:
		gameModel->prepareRobberDiscard(resource);
		break;
	default:
		break;
	}
}

inputCardsController::~inputCardsController()
{
}
