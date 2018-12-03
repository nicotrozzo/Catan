#include "catanGameModel.h"
#include "gameDefines.h"
#include <cstring>
#include <iterator>

catanGameModel::catanGameModel()
{
	dice1 = 0;
	dice2 = 0;
	//ver de poner quien arranca jugando
}

bool catanGameModel::dicesThrown(unsigned char dice1, unsigned char dice2)
{
	//tiene que cambiar el jugador que esta jugando
	//tiene que asignar recursos a los player que esten en el casillero que haya salido
	this->dice1 = dice1;
	this->dice2 = dice2;
	bool ret = false;
	list<pepe> hexagonos;
	list<string> vertex;
	list<string> cities;
	size_t found;
	player1Playing = !player1Playing;
	if ((dice1 + dice2) != 7)
	{
		hexagonos = map.getSelectedHex(dice1 + dice2);
		vertex = map.getP1BuiltVertexes();
		cities = map.getP1Cities();
		for (auto y : hexagonos)
		{
			for (auto x : vertex)
			{
				found = x.find(y.letter);
				if (found != string::npos)
				{
					player1.incResource(y.hexResource);	//si tiene una construccion adyacente al hexagono
				}
			}
			for (auto x : cities)
			{
				found = x.find(y.letter);
				if (found != string::npos)
				{
					player1.incResource(y.hexResource);	//si tiene una citi adyacente al hexagono le asigno un recurso mas
				}
			}
		}
		vertex = map.getP2BuiltVertexes();
		cities = map.getP2Cities();
		for (auto y : hexagonos)
		{
			for (auto x : vertex)
			{
				found = x.find(y.letter);
				if (found != string::npos)
				{
					player2.incResource(y.hexResource);	//si tiene una construccion adyacente al hexagono
				}
			}
			for (auto x : cities)
			{
				found = x.find(y.letter);
				if (found != string::npos)
				{
					player2.incResource(y.hexResource);	//si tiene una citi adyacente al hexagono le asigno un recurso mas
				}
			}
		}
		ret = true;
	}
	
	return ret;
}

bool catanGameModel::construction(networkingEventTypes type, string coords)
{
	bool ret = false;
	switch(type)
	{
	case ROAD:
		if (map.buildRoad(coords, getCurrentPlayer().getPlayerNumber()))
		{
			ret = true;
		}
		break;
	case SETTLEMENT:
		if (map.buildSettlement(coords, getCurrentPlayer().getPlayerNumber()))
		{
			ret = true;
		}
		break;
	case CITY:
		if (map.buildCity(coords, getCurrentPlayer().getPlayerNumber()))
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
	unsigned int currentResCount[] = { 0, 0, 0, 0, 0 };	//cada elemento representa un recurso
	unsigned int otherResCount[] = { 0, 0, 0, 0, 0 };		
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
			ret = (( (*pCResCount > getCurrentPlayer().getCards().brick) ? false : true) && (*pOResCount > getOtherPlayer().getCards().brick ? false : true));
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
				ret = (getCurrentPlayer().decResource(x) && getOtherPlayer().incResource(x));
			}
		}
		for (auto x : otherPlayerCards)
		{
			while (ret != false)
			{
				ret = (getCurrentPlayer().incResource(x) && getOtherPlayer().decResource(x));
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
	if (hex != map.getRobberPos())
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
				ret = getCurrentPlayer().decResource(x);
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
				ret = getOtherPlayer().decResource(x);
			}
		}
	}
	else
	{
		ret = false;
	}
	return ret;
}


catanPlayerModel catanGameModel::getCurrentPlayer()
{
	catanPlayerModel ret;
	if (player1Playing)
	{
		ret = player1;
	}
	else
	{
		ret = player2;
	}
	return ret;
}

catanPlayerModel catanGameModel::getOtherPlayer()
{
	catanPlayerModel ret;
	if (player1Playing)
	{
		ret = player2;
	}
	else
	{
		ret = player1;
	}
	return ret;
}

bool catanGameModel::gameOver()
{
	bool ret = false;
	if ((getCurrentPlayer().getVictoryPoints() == POINTS_TO_WIN) || (getOtherPlayer().getVictoryPoints() == POINTS_TO_WIN))
	{
		ret = true;
	}
	return ret;
}

void catanGameModelSetup::setStartingPlayer(char player)
{
	if (player == 1)
	{
		player1Playing = true;
	}
	else
	{
		player1Playing = false;
	}
}


catanGameModel::~catanGameModel()
{
}

