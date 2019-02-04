#include "catanGameModel.h"
#include "gameDefines.h"
#include <cstring>
#include <iterator>

using namespace std;

catanGameModel::catanGameModel()
{
	dice1 = 0;
	dice2 = 0;
	longestRoadPlayer = 0;
	player1Playing = rand() % 2;
	player1Started = player1Playing;
	clearTrades();
}

bool catanGameModel::dicesThrown(unsigned char dice1, unsigned char dice2)
{
	//tiene que cambiar el jugador que esta jugando
	//tiene que asignar recursos a los player que esten en el casillero que haya salido
	bool ret = false;
	player1Playing = !player1Playing;
	if (dice1 != 0)
	{
		this->dice1 = dice1;
		this->dice2 = dice2;
		list<pepe> hexagonos;
		list<string> vertex;
		list<string> cities;
		size_t found;
		if ((dice1 + dice2) != 7)
		{
			hexagonos = map.getSelectedHex(dice1 + dice2);
			vertex = map.getP1BuiltVertexes();
			cities = map.getP1Cities();
			for (auto y : hexagonos)
			{
				if (y.letter != map.getRobberPos())
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
	}
	notifyAllObservers();
	return ret;
}

bool catanGameModel::validResourceForConstruct(networkingEventTypes type)
{
	bool ret = false;
	cards resNeeded = { 0,0,0,0,0 };
	cards player;
	switch (type)
	{
	case SETTLEMENT:
		resNeeded.brick = 1;
		resNeeded.wheat = 1;
		resNeeded.wood = 1;
		resNeeded.wool = 1;
		break;
	case CITY:
		resNeeded.ore = 3;
		resNeeded.wheat = 2;
		break;
	case ROAD:
		resNeeded.brick = 1;
		resNeeded.wood = 1;
		break;
	default:
		break;
	}
	if (player1Playing)
	{
		player = player1.getCards();
	}
	else
	{
		player = player2.getCards();
	}
	return ((player.brick >= resNeeded.brick) && (player.ore >= resNeeded.ore) && (player.wood >= resNeeded.wood) && (player.wool >= resNeeded.wool) && (player.wheat >= resNeeded.wheat));
}

bool catanGameModel::validConstruction(networkingEventTypes type, string coords)
{
	bool ret = false;
	unsigned char player = (player1Playing ? 1 : 2);
	if (!selecting)
	{
		if (initConstructionOk(player))
		{
			bool initState = (player1Playing ? map.getP1Roads().size() < 2 : map.getP2Roads().size() < 2);	//si esta en el estado inicial, no necesita recursos para construir
			if ((validResourceForConstruct(type)) || initState)
			{
				switch (type)
				{
				case SETTLEMENT:
					ret = map.checkAvailableSettlement(coords, player);
					break;
				case CITY:
					ret = map.checkAvailableCity(coords, player);
					break;
				case ROAD:
					ret = map.checkAvailableRoad(coords, player);
					break;
				}
			}
			if (ret)
			{
				constructing = true;
				notifyAllObservers();
			}
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
	networkingEventTypes type;
	//unsigned char player = (player1Playing ? 1 : 2);
	if (constructing)
	{
		bool initState = (player1Playing ? map.getP1Roads().size() < 2 : map.getP2Roads().size() < 2);	//si esta en el estado inicial, no necesita recursos para construir
		string coords = map.getPendingConstruction().coords;
		type = map.buildPendingConstruction();
		if (!initState)
		{
			switch (type)
			{
			case SETTLEMENT:
				getCurrentPlayer()->decResource(BRICK);
				getCurrentPlayer()->decResource(WHEAT);
				getCurrentPlayer()->decResource(WOOD);
				getCurrentPlayer()->decResource(WOOL);
				break;
			case ROAD:
				getCurrentPlayer()->decResource(BRICK);
				getCurrentPlayer()->decResource(WOOD);
				break;
			case CITY:
				getCurrentPlayer()->decResource(ORE, 3);
				getCurrentPlayer()->decResource(WHEAT, 2);
				break;
			}
		}
		else if(type == SETTLEMENT)
		{
			if (player1Playing && map.getP1Settlements().size() == 2)
			{
				for (int i = 0; i < coords.length(); i++)
				{
					player1.incResource(map.getHexResource(coords[i]));
				}
			}
			else if(!player1Playing && map.getP2Settlements().size() == 2)
			{
				for (int i = 0; i < coords.length(); i++)
				{
					player2.incResource(map.getHexResource(coords[i]));
				}
			}
		}
		if (type != NO_PCKG)
		{
			ret = true;
			constructing = false;
			updatePlayersVictoryPoints();
		}
	}
	return ret;
}

void catanGameModel::cancelConstruction()
{
	constructing = false;
	map.cancelConstruction();
	notifyAllObservers();
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
	vicPoints1 += map.getP1Settlements().size() + 2 * map.getP1Cities().size();
	player1.setVictoryPoints(vicPoints1);
	vicPoints2 += map.getP2Settlements().size() + 2 * map.getP2Cities().size();
	player2.setVictoryPoints(vicPoints2);
	notifyAllObservers();
}

bool catanGameModel::validSelectedCards(string cardsPlayer1, string cardsPlayer2)	//en este caso current es el jugador 2 siempre
{
	bool ret = true;
	string possibleRes = "LMOPT";
	unsigned int player1ResCount[] = { 0, 0, 0, 0, 0 };	//cada elemento representa un recurso
	unsigned int player2ResCount[] = { 0, 0, 0, 0, 0 };		
	unsigned int * p1ResCount = player1ResCount, *p2ResCount = player2ResCount;
	std::size_t player1Pos = 0, player2Pos = 0;
	if (((cardsPlayer1.length() <= 9) && (cardsPlayer2.length() <= 9)) || (cardsPlayer1.size() == 0) ) 
	{
		for (auto x : possibleRes)
		{
			player1Pos = cardsPlayer1.find_first_of(x, player1Pos);
			while (player1Pos != std::string::npos)
			{
				(*p1ResCount)++;
				player1Pos = cardsPlayer1.find_first_of(x, player1Pos + 1);
			}

			player2Pos = cardsPlayer2.find_first_of(x, player2Pos);
			while (player2Pos != std::string::npos)
			{
				(*p2ResCount)++;
				player2Pos = cardsPlayer2.find_first_of(x, player2Pos + 1);
			}
			if (((*p1ResCount == 0) && (*p2ResCount != 0)) || ((*p1ResCount != 0) && (*p2ResCount == 0)))	//me fijo que no haya mismos recursos seleccionados
			{
				switch (x)
				{
				case 'L':
					ret = (((*p1ResCount > player1.getCards().brick) ? false : true) && (*p2ResCount > player2.getCards().brick ? false : true));
					break;
				case 'M':
					ret = ((*p1ResCount > player1.getCards().wood ? false : true) && (*p2ResCount > player2.getCards().wood ? false : true));
					break;
				case 'O':
					ret = ((*p1ResCount > player1.getCards().wool ? false : true) && (*p2ResCount > player2.getCards().wool ? false : true));
					break;
				case 'P':
					ret = ((*p1ResCount > player1.getCards().ore ? false : true) && (*p2ResCount > player2.getCards().ore ? false : true));
					break;
				case 'T':
					ret = ((*p1ResCount > player1.getCards().wheat ? false : true) && (*p2ResCount > player2.getCards().wheat ? false : true));
					break;
				default:
					ret = false;
					break;
				}
			}
			else if ( (player1Pos != string::npos) && (player2Pos != string::npos) )
			{
				ret = false;
			}
				
			if (ret == false)
			{
				break;			//consideramos necesario utilizar un break para salir del for ya que si alguna parte del intercambio no esta en condiciones no es necesario analizar las otras componentes de dicho intercambio
			}

			p1ResCount++;
			p2ResCount++;
			player1Pos = 0;
			player2Pos = 0;
		}
	}
	return ret;
}

bool catanGameModel::p2HasSelectedCards()
{
	cards pSel = p2SelectedCardsForTrade;
	cards p2 = player2.getCards();
	return ((pSel.ore <= p2.ore) && (pSel.brick <= p2.brick) && (pSel.wheat <= p2.wheat) && (pSel.wood <= p2.wood) && (pSel.wool <= p2.wool));
}

bool catanGameModel::initConstructionOk(unsigned char player)
{
	bool ret = false;
	if (player == 1)
	{
		if (player1Started)
		{
			ret = map.getP1Roads().size() == 0;
			if (!ret)
			{
				ret = map.getP2Roads().size() >= 2;
			}
		}
		else
		{
			ret = true;
			if (map.getP2Roads().size() == 1)
			{
				ret = map.getP1Roads().size() < 2;
			}
		}
	}
	else if (player == 2)
	{
		if (!player1Started)	//si arranco el jugador 2
		{
			ret = map.getP2Roads().size() == 0;
			if (!ret)
			{
				ret = map.getP1Roads().size() >= 2;
			}
		}
		else
		{
			ret = true;
			if (map.getP1Roads().size() == 1)
			{
				ret = map.getP2Roads().size() < 2;
			}
		}
	}
	return ret;
}

bool catanGameModel::playersTrade(string cardsPlayer1, string cardsPlayer2)
{
	bool ret = false;
	p2SelectedCardsForTrade = {0,0,0,0,0};
	p1SelectedCardsForTrade = { 0,0,0,0,0 };
	if (validSelectedCards(cardsPlayer1, cardsPlayer2))
	{
		for (auto x : cardsPlayer2)
		{
			//tiene que modificar los datos miembro internos y que se encargue playerTrade()... dato a modificar: p1SelectedCardsForTrade
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
		for (auto x : cardsPlayer1)
		{
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
		ret = true;
		selecting = OFFER_TRADE;
		notifyAllObservers();
	}
	return ret;
}

bool catanGameModel::bankTrade(string playerResource, resourceType bankResource)	
{ 
	bool ret = false;
	std::map<resourceType, unsigned char> costs = map.getBankTradeCosts(2);		
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
			for (; (strLenght != 0) && !ret; strLenght--)
			{
				ret = getCurrentPlayer()->decResource(res);
			}
			if (ret)
			{
				ret = getCurrentPlayer()->incResource(static_cast<unsigned char>(bankResource));
			}
		}
	}
	if (ret)
	{
		notifyAllObservers();
	}
	return ret;
}

bool catanGameModel::robberMoved(unsigned char hex)
{
	bool ret = false;
	if (map.setRobberPos(hex))
	{
		ret = true;
		notifyAllObservers();
	}
	return ret;
}

map<resourceType, unsigned char> catanGameModel::getBankTradeCosts()
{
	return map.getBankTradeCosts(1);
}

/*Devuelve true si se podia seleccionar uno mas de dicho recurso*/
bool catanGameModel::prepareRobberDiscard(resourceType resource)
{
	bool ret = false;
	if (!constructing)
	{
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
				ret = player1.getCards().wood > p1DiscardRobberCards.wood;
				if (ret)
				{
					p1DiscardRobberCards.wood++;
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
		ret = true;
		selecting = NO_PCKG;
		notifyAllObservers();
	}

	return ret;
}

bool catanGameModel::discardPlayer2(string cards)		//cuando se llama a este metodo es el turno del jugador 2
{
	bool ret = true;
	if ((floor(player2.getAmountOfCards() / 2.0) == cards.length()) && (player2.getAmountOfCards() > 7) && validSelectedCards("", cards))
	{
		for (auto x : cards)
		{
			if (!(ret = player2.decResource(x)))
			{
				break;
			}
		}
	}
	else
	{
		ret = false;
	}
	if (ret)
	{
		notifyAllObservers();
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
	if (!constructing)
	{
		if (selecting != OFFER_TRADE)
		{
			selecting = OFFER_TRADE;		//para avisar a los observers
			notifyAllObservers();
		}
		else if (((player == 1) && (p1SelectedCardsForTrade.totalCardsCount() < 9)) || ((player == 2) && (p2SelectedCardsForTrade.totalCardsCount() < 9)))
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
						ret = player1.getCards().ore > p1SelectedCardsForTrade.ore;
						break;
					case WOOD:
						ret = player1.getCards().wood > p1SelectedCardsForTrade.wood;
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
		if (p2HasSelectedCards())
		{
			player1.decResource(ORE, p1SelectedCardsForTrade.ore);
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
			ret = true;
		}
		selecting = NO_PCKG;
		clearTrades();
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
	if (!constructing)
	{
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
			if (ret)
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

bool catanGameModel::isPlayer1Playing()
{
	return player1Playing;
}

bool catanGameModel::hasToConstruct()
{
	bool ret = false;
	if (player1Playing)
	{
		if (player1Started)
		{
			ret = (map.getP1Roads().size() == 0);
			if (!ret)
			{
				ret = ((map.getP2Roads().size() == 2) && ((map.getP1Roads().size() < 2)));
			}
		}
		else
		{
			ret = (map.getP2Roads().size() == 1) && (map.getP1Roads().size() < 2);
		}
	}
	else
	{
		if (!player1Started)
		{
			ret = (map.getP2Roads().size() == 0);
			if (!ret)
			{
				ret = ((map.getP1Roads().size() == 2) && ((map.getP2Roads().size() < 2)));
			}
		}
		else
		{
			ret = (map.getP1Roads().size() == 1) && (map.getP2Roads().size() < 2);
		}
	}
	return ret;
}

bool catanGameModel::initState()
{
	return (map.getP1Roads().size() < 2) || (map.getP2Roads().size() < 2);
}

catanPlayerModel *catanGameModel::getCurrentPlayer()
{
	catanPlayerModel *ret = nullptr;
	if (player1Playing)
	{
		ret = &player1;
	}
	else
	{
		ret = &player2;
	}
	return ret;
}

catanPlayerModel *catanGameModel::getOtherPlayer()
{
	catanPlayerModel *ret = nullptr;
	if (player1Playing)
	{
		ret = &player2;
	}
	else
	{
		ret = &player1;
	}
	return ret;
}

catanMapModel *catanGameModel::getMap()
{
	return &map;
}

bool catanGameModel::gameOver()
{
	bool ret = false;
	if ((getCurrentPlayer()->getVictoryPoints() >= POINTS_TO_WIN) || (getOtherPlayer()->getVictoryPoints() >= POINTS_TO_WIN))
	{
		ret = true;
	}
	return ret;
}

void catanGameModel::notify()
{
	notifyAllObservers();
}

catanGameModel::~catanGameModel()
{

}