#include "catanGameModel.h"
#include "gameDefines.h"
#include <cstring>
#include <iterators.h>

catanGameModel::catanGameModel()
{
}

bool catanGameModel::dicesThrown(unsigned int diceValue)
{
	return false;
}

bool catanGameModel::construction(networkingEventTypes type, string coords)
{
	bool ret = false;
	switch(type)
	{
	case ROAD:
		if (map.checkAvailableRoad(coords, getCurrentPlayer().getPlayerNumber()))
		{
			ret = true;
		}
		break;
	case SETTLEMENT:
		if (map.checkAvailableSettlement(coords, getCurrentPlayer().getPlayerNumber()))
		{
			ret = true;
		}
		break;
	case CITY:
		if (map.checkAvailableCity(coords, getCurrentPlayer().getPlayerNumber()))
		{
			ret = true;
		}
		break;
	}
	return ret;
}

bool catanGameModel::validSelectedCards(string currentPlayerCards, string otherPlayerCards)
{
	bool ret = true;
	string possibleRes = RESOURCES_STR;
	unsigned int currentResCount[] = { brickCount = 0, woodCount = 0, woolCount = 0, oreCount = 0,  wheatCount = 0 };	//estan ordenados segun RESOURCES_STR
	unsigned int otherResCount[] = { brickCount = 0, woodCount = 0, woolCount = 0, oreCount = 0,  wheatCount = 0 };
	unsigned int * pCResCount = currentResCount, *pOResCount = otherResCount;
	std::size_t currentPos = 0, otherPos = 0;
	for (auto x : possibleRes)	//char
	{
		currentPos = currentPlayerCards.find_first_of(x, currentPos);
		while (currentPos != std::string::npos)
		{
			*pCResCount++;
			currentPos = currentPlayerCards.find_first_of(x, currentPos + 1);
		}

		otherPos = otherPlayerCards.find_first_of(x, otherPos);
		while (otherPos != std::string::npos)
		{
			*pOResCount++;
			otherPos = otherPlayerCards.find_first_of(x, otherPos + 1);
		}

		switch(x)
		{
		case 'L':
			ret = ((*pCResCount > getCurrentPlayer().getCards().brick ? false : true) && (*pOResCount > getOtherPlayer().getCards().brick ? false : true));
			break;
		case 'M':
			ret = ((*pCResCount > getCurrentPlayer().getCards().wood ? false : true) && (*pOResCount > getOtherPlayer().getCards().wood ? false : true));
			break;
		case 'O':
			ret = ((*pCResCount > getCurrentPlayer().getCards().wool ? false : true) && (*pOResCount > getOtherPlayer().getCards().wool ? false : true));
			break;
		case 'P':
			ret = ((*pCResCount > getCurrentPlayer().getCards().ore ? false : true) && (*pOResCount > getOtherPlayer().getCards().ore ? false : true));
			break;
		case 'T':
			ret = ((*pCResCount > getCurrentPlayer().getCards().wheat ? false : true) && (*pOResCount > getOtherPlayer().getCards().wheat ? false : true));
			break;
		default:
			break;
		}

		if (ret == false)
		{
			break;			//consideramos necesario utilizar un break para salir del for ya que si alguna parte del intercambio no esta en condiciones no es necesario analizar las otras componentes de dicho intercambio
		}

		pCResCount++;
		pOResCount++;
	}
	return ret;
}

bool catanGameModel::playersTrade(string currentPlayerCards, string otherPlayerCards)
{
	bool ret = true;
	if (validSelectedCards(currentPlayerCards, otherPlayerCards))
	{
		for (auto x : currentPlayerCards)
		{
			while (ret != false)
			{
				ret = (getCurrentPlayer().decResource(1, x) && getOtherPlayer().incResource(1, x));
			}
		}
		for (auto x : otherPlayerCards)
		{
			while (ret != false)
			{
				ret = (getCurrentPlayer().incResource(1, x) && getOtherPlayer().decResource(1, x));
			}
		}
	}
	else
	{
		ret = false;
	}
	return ret;
}

bool catanGameModel::bankTrade(string player, unsigned char bankResource)	//player seria nameIs?
{
	//ver 
	return false;
}

bool catanGameModel::robberMoved(unsigned char hex)
{
	bool ret = false;
	if (hex != map.getRoberPos())
	{
		map.setRobberPos(hex);
		ret = true;
	}
	return ret;
}

bool catanGameModel::discardCurrentPlayer(string cards)
{
	bool ret = true;
	if (validSelectedCards(cards, ""))
	{
		for (auto x : cards)
		{
			while (ret != false)
			{
				ret = getCurrentPlayer().decResource(1, x);
			}
		}
	}
	else
	{
		ret = false;
	}
	return ret;
}

bool catanGameModel::discardOtherPlayer(string cards)
{
	bool ret = true;
	if (validSelectedCards("", cards))
	{
		for (auto x : cards)
		{
			while (ret != false)
			{
				ret = getOtherPlayer().decResource(1, x);
			}
		}
	}
	else
	{
		ret = false;
	}
	return ret;
}


bool catanGameModel::gameOver()
{
	bool ret = false;
	if ((getCurrentPlayer().getVictoryPoints() == POINTS_TO_WIN) || ((getOtherPlayer().getVictoryPoints() == POINTS_TO_WIN))
	{
		ret = true;
	}
	return ret;
}

catanGameModel::~catanGameModel()
{
}
