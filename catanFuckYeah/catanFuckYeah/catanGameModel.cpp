#include "catanGameModel.h"
#include "gameDefines.h"
#include <cstring>
#include <iterator>

catanGameModel::catanGameModel()
{
	dice1 = 0;
	dice2 = 0;
	longestRoadPlayer = 0;
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

bool catanGameModel::validConstruction(networkingEventTypes type, string coords)
{
	bool ret = true;
	unsigned char player = player1Playing ? 1 : 2;
	switch (type)
	{
	case SETTLEMENT:
		if (!map.checkAvailableSettlement(coords, player))
		{
			ret = map.checkAvailableCity(coords, player);
		}
		else
		{
			ret = true;
		}
		break;
	case ROAD:
		ret = map.checkAvailableRoad(coords, player);
		break;
	}
	if (ret)
	{
		if (!constructing)
		{
			constructing = true;
			notifyAllObservers();
		}
	}
	return ret;
}

/*Construye la construccion que tenga guardada internamente el mapa, que es la ultima valida por la que hayan preguntado
en validConstruction()
*/
bool catanGameModel::construct()
{
	bool ret = false;
	unsigned char player = player1Playing ? 1 : 2;
	if (construct)
	{
		ret = map.buildPendingConstruction();
		if (ret)
		{
			constructing = false;
			updatePlayersVictoryPoints();
		}
		
		/*switch (pendingConstruction.type)
		{
		case ROAD:
			ret = map.buildRoad(pendingConstruction.coords, player);
			break;
		case SETTLEMENT:
			ret = map.buildSettlement(pendingConstruction.coords, player);
			break;
		case CITY:
			ret = map.buildCity(pendingConstruction.coords, player);
			break;
		}
		pendingConstruction.type = static_cast<networkingEventTypes>(0);*/
	}
	return ret;
}

void catanGameModel::cancelConstruction()
{
	constructing = false;
	map.cancelConstruction();
}

bool catanGameModel::isConstructing()
{
	return constructing;
}

void catanGameModel::updatePlayersVictoryPoints()
{
	unsigned char vicPoints1 = 0;
	unsigned char vicPoints2 = 0;
	unsigned char longestRoad1 = map.getP1LongestRoad();
	unsigned char longestRoad2 = map.getP2LongestRoad();
	if (player1.getLongestRoad() < longestRoad1)
		void catanGameModel::cancelConstruction()
	{
	}
	{
		player1.setLongestRoad(longestRoad1);
	}
	if (player2.getLongestRoad() < longestRoad2)
	{
		player2.setLongestRoad(longestRoad2);
	}
	if ((longestRoad1 >= 5) || (longestRoad2 >= 5))
	{
		if ((longestRoad1 > longestRoad2) || ((longestRoad1 == longestRoad2) && (longestRoadPlayer == 1)))
		{
			vicPoints1++;
		}
		else
		{
			vicPoints2++;
		}
	}
	vicPoints1 += map.getP1Settlements().length() + 2 * map.getP1Cities().length();
	player1.setVictoryPoints(vicPoints1);
	vicPoints2 += map.getP2Setllements().length() + 2 * map.getP1Cities.length();
	player2.setVictoryPoints(vicPoints2);
}

bool catanGameModel::validSelectedCards(string currentPlayerCards, string otherCards)
{
	bool ret = true;
	string possibleRes = RESOURCES_STR;
	unsigned int currentResCount[] = { 0, 0, 0, 0, 0 };	//cada elemento representa un recurso
	unsigned int otherResCount[] = { 0, 0, 0, 0, 0 };		
	unsigned int * pCResCount = currentResCount, *pOResCount = otherResCount;
	std::size_t currentPos = 0, otherPos = 0;
	if ((currentPlayerCards.length() <= 9) && (otherCards.length() <= 9))
	{
		for (auto x : possibleRes)
		{
			currentPos = currentPlayerCards.find_first_of(x, currentPos);
			while (currentPos != std::string::npos)
			{
				*pCResCount++;
				currentPos = currentPlayerCards.find_first_of(x, currentPos + 1);
			}

			otherPos = otherCards.find_first_of(x, otherPos);
			while (otherPos != std::string::npos)
			{
				*pOResCount++;
				otherPos = otherCards.find_first_of(x, otherPos + 1);
			}
			if (((*pCResCount == 0) && (*pOResCount != 0)) || ((*pCResCount != 0) && (*pOResCount == 0)))	//me fijo que no haya mismos recursos seleccionados
			{
				switch (x)
				{
				case 'L':
					ret = (((*pCResCount > getCurrentPlayer().getCards().brick) ? false : true) && (*pOResCount > getOtherPlayer().getCards().brick ? false : true));
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
			}
			if (ret == false)
			{
				break;			//consideramos necesario utilizar un break para salir del for ya que si alguna parte del intercambio no esta en condiciones no es necesario analizar las otras componentes de dicho intercambio
			}

			pCResCount++;
			pOResCount++;
		}
	}
	return ret;
}

/**/
bool catanGameModel::playersTrade(string currentPlayerCards, string otherPlayerCards)
{
	bool ret = false;
	if (validSelectedCards(currentPlayerCards, otherPlayerCards))
	{
		for (auto x : currentPlayerCards)
		{
			//tiene que modificar los datos miembro internios y que se encargue preprePlayerTrade()... dato a modificar: p1SelectedCardsForTrade
			switch (x)
			{
			case BRICK:
				p1SelectedCardsForTrade.brick++;
				break;
			case WOOD:
				p1SelectedCardsForTrade.wood++;
				break;
			case WOOL:
				p1SelectedCardsForTrade.wool++;
				break;
			case ORE:
				p1SelectedCardsForTrade.ore++;
				break;
			case WHEAT:
				p1SelectedCardsForTrade.wheat++;
				break;
			default:
				break;
			}
		}
		for (auto x : otherPlayerCards)
		{
			switch (x)
			{
			case BRICK:
				p2SelectedCardsForTrade.brick++;
				break;
			case WOOD:
				p2SelectedCardsForTrade.wood++;
				break;
			case WOOL:
				p2SelectedCardsForTrade.wool++;
				break;
			case ORE:
				p2SelectedCardsForTrade.ore++;
				break;
			case WHEAT:
				p2SelectedCardsForTrade.wheat++;
				break;
			default:
				break;
			}
		}
		ret = true;
	}
	return ret;
}

bool catanGameModel::bankTrade(string playerResource, resourceType bankResource)	
{ 
	bool ret = false;
	map<resourceType, unsigned char> costs = map.getBankTradeCosts(2);
	size_t strLenght = 0;
	char res = playerResource[0];
	unsigned char costRes;
	for (auto x : playerResource)
	{
		if (res == x)
		{
			strLenght++;
		}
	}
	if (strLenght == playerResource.length())
	{
		switch (res)
		{
		case BRICK:
			costRes = costs[BRICK];
			break;
		case WOOL:
			costRes = costs[WOOL];
			break;
		case WOOD:
			costRes = costs[WOOD];
			break;
		case ORE:
			costRes = costs[ORE];
			break;
		case WHEAT:
			costRes = costs[WHEAT];
			break;
		default:
			break;
		}
		if (strLenght == static_cast<size_t>(costRes))
		{
			for (; strLenght != 0; strLenght--)
			{
				getOtherPlayer().decResource(res);
			}
		}
	}
	return ret;
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

map<resourceType, unsigned char> catanGameModel::getBankTradeCosts()
{
	unsigned char player = player1Playing ? 1 : 2;
	return map.getBankTradeCosts(player);
}

bool catanGameModel::prepareRobberDiscard(resourceType resource)
{
	bool ret = false;
	if (selecting != ROBBER_CARDS)
	{
		selecting = ROBBER_CARDS;
		notifyAllObservers();
	}
	if (p1DiscardRobberCards.totalCardsCount() < player1.getCards().totalCardsCount() / 2)
	{
		switch (resource)
		{
		case BRICK:
			ret = player1.getCards().brick > p1DiscardRobberCards.brick;
			if (ret)
			{
				p1DiscardRobberCards.brick++;
			}
			break;
		case WOOD:
			ret = player1.getCards().brick > p1DiscardRobberCards.brick;
			if (ret)
			{
				p1DiscardRobberCards.brick++;
			}
			break;
		case WOOL:
			ret = player1.getCards().wool > p1DiscardRobberCards.wool;
			if (ret)
			{
				p1DiscardRobberCards.wool++;
			}
			break;
		case ORE:
			ret = player1.getCards().ore > p1DiscardRobberCards.ore;
			if (ret)
			{
				p1DiscardRobberCards.ore++;
			}
			break;
		case WHEAT:
			ret = player1.getCards().wheat > p1DiscardRobberCards.wheat;
			if (ret)
			{
				p1DiscardRobberCards.wheat++;
			}
			break;
		default:
			break;
		}
	}
	if (ret)
	{
		notifyAllObservers();
	}
	return ret;
}

bool catanGameModel::robberCardsReady()
{
	return p1DiscardRobberCards.totalCardsCount() >= player1.getCards().totalCardsCount()/2;
}

void catanGameModel::clearRobberCards()
{
	p1DiscardRobberCards.ore = 0;
	p1DiscardRobberCards.brick = 0;
	p1DiscardRobberCards.wheat = 0;
	p1DiscardRobberCards.wool = 0;
	p1DiscardRobberCards.wood = 0;
	notifyAllObservers();
}

bool catanGameModel::discardCurrentPlayer()
{
	bool ret = false;
	if (robberCardsReady())
	{
		player1.decResource(ORE,p1DiscardRobberCards.ore);
		player1.decResource(WHEAT, p1DiscardRobberCards.wheat);
		player1.decResource(WOOL,p1DiscardRobberCards.wool);
		player1.decResource(WOOD,p1DiscardRobberCards.wood);
		player1.decResource(BRICK,p1DiscardRobberCards.brick);
	}
	selecting = NO_PCKG;
	notifyAllObservers();
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

networkingEventTypes catanGameModel::isSelecting()
{
	return selecting;
}

void catanGameModel::clearTrades()
{
	p1SelectedCardsForTrade = { 0,0,0,0,0 };
	p2SelectedCardsForTrade = { 0,0,0,0,0 };
	playerSelectedResource = {DESSERT,0};
	bankSelectedResource = DESSERT;
	selecting = NO_PCKG;
	notifyAllObservers();
}

/*preparePlayerTrade: 
*Recibe:
	-Primer parametro: recurso a incrementar
	-Segundo parametro: jugador cuyo recurso se quiere incrementar (1 o 2)
*Funcionamiento: si se puede, incrementa el recurso pedido en 1 en los recursos seleccionados por el jugador solicitado para el intercambio
Siempre incrementa el recurso del jugador 2 para que el usuario no pueda saber cuantos recursos tiene el jugador 2
*Devuelve: false si se trato de incrementar un recurso DEL JUGADOR ACTUAL que no tenia. 
Si devuelve true, MODIFICA EL MODELO
*/
bool catanGameModel::preparePlayerTrade(resourceType resource, unsigned char player)
{
	bool ret = false;
	if (selecting != OFFER_TRADE)
	{
		selecting = OFFER_TRADE;		//para avisar a los observers
		notifyAllObservers();
	}
	else if( ((player == 1) && (p1SelectedCardsForTrade.totalCardsCount() < 9)) || ((player == 2) && (p2SelectedCardsForTrade.totalCardsCount() < 9)))
	{
		if (!selectedResource(resource, (player == 1) ? 2 : 1))	//se fija que el otro jugador no tenga seleccionado ya ese recurso
		{
			ret = true;
			if (player == 1)	//si es el jugador 1, se fija que tenga la cantidad de cartas suficientes
			{
				switch (resource)
				{
				case WHEAT:
					ret = player1.getCards().wheat > p1SelectedCardsForTrade.wheat;
					break;
				case WOOL:
					ret = player1.getCards().wool > p1SelectedCardsForTrade.wool;
					break;
				case BRICK:
					ret = player1.getCards().brick > p1SelectedCardsForTrade.brick;
					break;
				case ORE:
					ret = player1.getCards().brick > p1SelectedCardsForTrade.brick;
					break;
				case WOOD:
					ret = player1.getCards().brick > p1SelectedCardsForTrade.brick;
					break;
				default:
					ret = false;
				}
			}
			if (ret)
			{
				switch (resource)
				{
				case WHEAT:
					player == 1 ? p1SelectedCardsForTrade.wheat++ : p2SelectedCardsForTrade.wheat++;
					break;
				case WOOL:
					player == 1 ? p1SelectedCardsForTrade.wool++ : p2SelectedCardsForTrade.wool++;
					break;
				case BRICK:
					player == 1 ? p1SelectedCardsForTrade.brick++ : p2SelectedCardsForTrade.brick++;
					break;
				case ORE:
					player == 1 ? p1SelectedCardsForTrade.ore++ : p2SelectedCardsForTrade.ore++;
					break;
				case WOOD:
					player == 1 ? p1SelectedCardsForTrade.wood++ : p2SelectedCardsForTrade.wood++;
					break;
				}
				notifyAllObservers();
			}
		}
	}
	return ret;
}

/*Devuelve true si el jugador tiene seleccionado dicho recurso*/
bool catanGameModel::selectedResource(resourceType resource, unsigned char player)
{
	bool ret = false;
	switch (resource)
	{
	case WHEAT:
		ret = (player == 1 ? p1SelectedCardsForTrade.wheat != 0  : p2SelectedCardsForTrade.wheat != 0);
		break;
	case WOOL:
		ret = (player == 1 ? p1SelectedCardsForTrade.wool != 0 : p2SelectedCardsForTrade.wool != 0);
		break;
	case BRICK:
		ret = (player == 1 ? p1SelectedCardsForTrade.brick != 0 : p2SelectedCardsForTrade.brick != 0);
		break;
	case ORE:
		ret = (player == 1 ? p1SelectedCardsForTrade.ore != 0 : p2SelectedCardsForTrade.ore != 0);
		break;
	case WOOD:
		ret = (player == 1 ? p1SelectedCardsForTrade.wood != 0 : p2SelectedCardsForTrade.wood != 0);
		break;
	}
	return ret;
}

/*playerTradeReady:
*Funcionamiento: se fija que el intercambio de cartas de jugadores este listo para ser enviado
Devuelve true si el intercambio con el jugador preparado esta listo
Aclaracion: No valida la cantidad de cartas del jugador 2, solo las del 1*/
bool catanGameModel::playerTradeReady()
{
	return (p1SelectedCardsForTrade.totalCardsCount() > 0) && (p2SelectedCardsForTrade.totalCardsCount() > 0);
}

/*Realiza el player trade preparado, devuelve true si lo puede hacer, 0 sino*/
bool catanGameModel::playerTrade()
{
	bool ret = false;
	if (playerTradeReady())
	{
		player1.decResource(ORE,p1SelectedCardsForTrade.ore);
		player1.decResource(BRICK, p1SelectedCardsForTrade.brick);
		player1.decResource(WHEAT, p1SelectedCardsForTrade.wheat);
		player1.decResource(WOOL, p1SelectedCardsForTrade.wool);
		player1.decResource(WOOD, p1SelectedCardsForTrade.wood);
		player2.incResource(ORE, p1SelectedCardsForTrade.ore);
		player2.incResource(BRICK, p1SelectedCardsForTrade.brick);
		player2.incResource(WHEAT, p1SelectedCardsForTrade.wheat);
		player2.incResource(WOOL, p1SelectedCardsForTrade.wool);
		player2.incResource(WOOD, p1SelectedCardsForTrade.wood);
		player1.incResource(ORE, p2SelectedCardsForTrade.ore);
		player1.incResource(BRICK, p2SelectedCardsForTrade.brick);
		player1.incResource(WHEAT, p2SelectedCardsForTrade.wheat);
		player1.incResource(WOOL, p2SelectedCardsForTrade.wool);
		player1.incResource(WOOD, p2SelectedCardsForTrade.wood);
		player2.decResource(ORE, p2SelectedCardsForTrade.ore);
		player2.decResource(BRICK, p2SelectedCardsForTrade.brick);
		player2.decResource(WHEAT, p2SelectedCardsForTrade.wheat);
		player2.decResource(WOOL, p2SelectedCardsForTrade.wool);
		player2.decResource(WOOD, p2SelectedCardsForTrade.wood);
		selecting = static_cast<networkingEventTypes>(0);
		notifyAllObservers();
		ret = true;
	}
	return ret;
}

/*prepareBankTrade:
*Recibe: 
	-Primer parametro: recurso a seleccionar
	-Segundo parametro: indica si se selecciona un recurso del banco o del jugador. True si es del jugador, false si es del banco
*Funcionamiento: intenta seleccionar el recurso solicitado para el jugador o el banco. Si se selecciona un recurso del jugador y habia uno seleccionado del banco, este ultimo se borra
				Si se selecciona un recurso del jugador y ya habia un recurso seleccionado del jugador, pisa el anterior, lo mismo con recursos del banco.
				Si el jugador no dispone de los recursos suficientes, no hace nada.
				Si el jugador dispone de los recursos, selecciona la cantidad necesaria, segun los costos del jugador para el bank trade
*Devuelve: true si selecciona el recurso, false si no*/
bool catanGameModel::prepareBankTrade(resourceType resource, bool player)
{
	bool ret = false;
	if (selecting != BANK_TRADE)
	{
		selecting = BANK_TRADE;
		notifyAllObservers();
	}
	else if (player)
	{
		bankSelectedResource = DESSERT;
		unsigned char cost = map.getBankTradeCosts(1)[resource];	//obtiene el costo de construir el recurso pedido para el jugador 1
		switch (resource)
		{
		case WHEAT:
			ret = player1.getCards().wheat >= cost ? true : false;
			break;
		case WOOL:
			ret = player1.getCards().wool >= cost ? true : false;
			break;
		case BRICK:
			ret = player1.getCards().brick >= cost ? true : false;
			break;
		case ORE:
			ret = player1.getCards().ore >= cost ? true : false;
			break;
		case WOOD:
			ret = player1.getCards().wood >= cost ? true : false;
			break;
		}
		if(ret)
		{
			playerSelectedResource = { resource, cost };	//pisa el recurso anterior si habia
		}
	}
	else
	{
		if (playerSelectedResource.res != DESSERT)	//solo permite modificar si el jugador ya selecciono un recurso
		{
			if ((playerSelectedResource.res != resource))	//no permite cambios de un mismo recurso
			{
				bankSelectedResource = resource;
				ret = true;
			}

		}
	}
	if (ret)	//si se modifico algo,avisa a los observers
	{
		notifyAllObservers();
	}
	return ret;
}

/*Devuelve true si el bankTrade preparado esta listo para ser realizado*/
bool catanGameModel::bankTradeReady()
{
	return (playerSelectedResource.res != DESSERT) && (bankSelectedResource != DESSERT);
}

/*Realiza el bank trade preparado, devuelve false si no lo puede hacer*/
bool catanGameModel::bankTrade()
{
	bool ret = false;
	if (bankTradeReady())
	{
		player1.decResource(playerSelectedResource.res, playerSelectedResource.resCount);	
		player1.incResource(bankSelectedResource);
		selecting = static_cast<networkingEventTypes>(0);
		notifyAllObservers();
		ret = true;
	}
	return ret;
}

bool catanGameModel::player1Playing()
{
	return player1Playing;
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
	if ((getCurrentPlayer().getVictoryPoints() >= POINTS_TO_WIN) || (getOtherPlayer().getVictoryPoints() >= POINTS_TO_WIN))
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