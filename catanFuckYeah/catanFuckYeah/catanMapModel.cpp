#include "catanMapModel.h"

catanMapModel::catanMapModel()
{
	vector<resource_t>allResources({ { WOOD,4 },{ BRICK,3 },{ ORE,3 },{ WHEAT,4 },{ WOOL,4 },{ DESSERT,1 } });
	array<unsigned char, HEX_COUNT - 1> allCircularTokens = { 2,3,3,4,4,5,5,6,6,8,8,9,9,10,10,11,11,12 };
	array<unsigned char, NUMBER_OF_OCEAN_PIECES> allOceanPieces = { WOOD,BRICK,ORE,WHEAT,WOOL,DESSERT };
	int resRandNum;							//RECORDAR SRAND EN EL MAIN!!!!!!!!!!!!!!!!
	int tokenRandNum;
	int oceanRandNum;
	bool written;			//indica si ya se encontro en la lista entera lo que se buscaba en cada iteracion
	for (int i = 0; i < HEX_COUNT; i++)					//calculo random del mapa
	{
		resRandNum = rand() % NUMBER_OF_HABITATS;
		tokenRandNum = rand() % (HEX_COUNT - 1);
		written = false;
		for (int j = 0; (j < NUMBER_OF_HABITATS) && !written; j++)
		{
			if (allResources[(resRandNum + j) % NUMBER_OF_HABITATS].resCount > 0)
			{
				hexagons[i].hexResource = allResources[(resRandNum + j) % NUMBER_OF_HABITATS].res;
				allResources[(resRandNum + j) % NUMBER_OF_HABITATS].resCount--;
				written = true;
			}
		}
		if (hexagons[i].hexResource != DESSERT)
		{
			written = false;
			for (int j = 0; (j < (HEX_COUNT - 1)) && !written; j++)
			{
				if (allCircularTokens[(tokenRandNum + j) % (HEX_COUNT - 1)] != 0)
				{
					hexagons[i].circularToken = allCircularTokens[(tokenRandNum + j) % (HEX_COUNT - 1)];
					allCircularTokens[(tokenRandNum + j) % (HEX_COUNT - 1)] = 0;
					written = true;
				}
			}
		}
		else
		{
			hexagons[i].circularToken = 7;
			robberPos = i + 'A';
		}
	}
	for (int i = 0; i < NUMBER_OF_OCEAN_PIECES; i++)
	{
		written = false;
		oceanRandNum = rand() % NUMBER_OF_OCEAN_PIECES;
		for (int j = 0; (j < NUMBER_OF_OCEAN_PIECES) && !written; j++)
		{
			if ((allOceanPieces[(oceanRandNum + j) % (NUMBER_OF_OCEAN_PIECES)] != '0'))
			{
				oceanPieces[i].setResource(allOceanPieces[(oceanRandNum + j) % (NUMBER_OF_OCEAN_PIECES)]);
				allOceanPieces[(oceanRandNum + j) % (NUMBER_OF_OCEAN_PIECES)] = '0';
				written = true;
			}
		}
	}
	pendingConstruction.type = NO_PCKG;
}

unsigned char catanMapModel::getRobberPos()
{
	return robberPos;
}

bool catanMapModel::setRobberPos(unsigned char robberPos_)
{
	bool ret = false;
	if (robberPos != robberPos_)
	{
		ret = true;
		robberPos = robberPos_;
	}
	return ret;
}

string catanMapModel::getMap(void)
{
	string mapToReturn;
	for (int i = 0; i < NUMBER_OF_OCEAN_PIECES; i++)
	{
		mapToReturn += oceanPieces[i].getResource();
	}
	for (int i = 0; i < HEX_COUNT; i++)
	{
		mapToReturn += hexagons[i].hexResource;
	}
	return mapToReturn;
}

/*Devuelve 7 en el lugar del robber, hay que modificarlo despues*/
string catanMapModel::getCircularTokens(void)
{
	string circTokToReturn;
	for (int i = 0; i < HEX_COUNT; i++)
	{
		circTokToReturn += hexagons[i].circularToken;
	}
	return circTokToReturn;
}

bool catanMapModel::setMap(string map_)
{
	bool ret = false;
	bool error = false;
	map <unsigned char, unsigned char> allResources = { { WOOD,0 },{ BRICK,0 },{ ORE,0 },{ WHEAT,0 },{ WOOL,0 },{ DESSERT,0 } };
	size_t found = map_.find_first_not_of(RESOURCES_STR);
	string oceanPiecesChars;
	if (found == string::npos)		//si todas las letras son algun recurso
	{
		for (int i = 0; (i < NUMBER_OF_OCEAN_PIECES + HEX_COUNT) && !ret; i++)
		{
			if (i < NUMBER_OF_OCEAN_PIECES)
			{
				oceanPieces[i].setResource(map_[i]);
				oceanPiecesChars += map_[i];	//para verificar luego que esten todos los recursos en las oceanPieces
			}
			else
			{
				hexagons[i].hexResource = map_[i];
			}
		}
		found = oceanPiecesChars.find_first_not_of(RESOURCES_STR);	//verifica que se hayan asignado todas piezas de mar distintas
		if (found != string::npos)
		{
			for (int i = 0; (i < HEX_COUNT) && !error; i++)	//valida hexagonos
			{
				if (allResources.find(map_[i]) != allResources.end())
				{
					switch (map_[i])
					{
					case DESSERT:
						error = (allResources[map_[i]] > 1) ? true : false;
						break;
					case BRICK: case ORE:
						error = (allResources[map_[i]] > 3) ? true : false;
						break;
					default:
						error = (allResources[map_[i]] > 4) ? true : false;
					}
				}
				else
				{
					error = true;
				}
			}
			if (!error)
			{
				ret = true;
			}
		}
	}
	return ret;
}

bool catanMapModel::setCircularTokens(string circTokens)
{
	bool ret = true;
	size_t found = circTokens.find_first_not_of("\2\3\4\5\6\7\8\9\10\11\12");
	string aux = circTokens;
	int count;
	if (found == string::npos)
	{
		for (int i = 2; (i < 13) && ret; i++)
		{
			count = 0;
			size_t aPos = aux.find_first_of(i);
			while (aPos != string::npos)
			{
				aPos = aux.find_first_of(i, aPos);
				count++;
			}
			if ((i != 2) && (i != 7) && (i != 12))
			{
				if (count != 2)
				{
					ret = false;
				}
			}
			else
			{
				if (count != 1)
				{
					ret = false;
				}
			}
		}
		if (ret)
		{
			int i = 0;
			for (auto x : hexagons)
			{
				x.circularToken = circTokens[i];
				i++;
			}
		}
	}
	return ret;
}

bool catanMapModel::adjacentToHiddenRoad(string vertex)
{
	bool ret = false;
	list<string>::iterator it;
	for (it = hiddenRoads.begin(); (it != hiddenRoads.end()) && !ret; it++)
	{
		ret = vertexAdjacentToRoad(vertex, *it);
	}
	return ret;
}

/*Devuelve true en caso que el vertice sea adyacente a algun camino simple (camino en cuyos vertices no se puede construir)*/
bool catanMapModel::adjacentToSimpleRoad(string vertex)
{
	bool ret = false;
	for (auto x : p1SimpleRoads)
	{
		if (ret = vertexAdjacentToRoad(vertex, x->edge))	//sale si encontro que el vertice es adyacente a algun camino
		{
			break;
		}
	}
	if (!ret)
	{
		for (auto x : p2SimpleRoads)
		{
			if (ret = vertexAdjacentToRoad(vertex, x->edge))	//sale si encontro que el vertice es adyacente a algun camino
			{
				break;
			}
		}
	}
	return ret;
}

/*Devuelve true si el vertice es adyacente a un road en cuyos vertices se puede construir*/
bool catanMapModel::adjacentToLongRoad(string vertex, char player)
{
	bool ret = false;
	if (player == 1)
	{
		for (auto x : p1LongRoads)
		{
			if (ret = vertexAdjacentToRoad(vertex, x->edge))
			{
				break;
			}
		}
	}
	else if (player == 2)
	{
		for (auto x : p2LongRoads)
		{
			if (ret = vertexAdjacentToRoad(vertex, x->edge))
			{
				break;
			}
		}
	}
	return ret;
}

bool catanMapModel::checkAvailableRoad(string edge, char player)
{
	bool ret = false;
	ret = player == 1 ? ((p1LongRoads.size() + p1SimpleRoads.size())<AMOUNT_OF_ROADS)  : ((p2LongRoads.size() + p2SimpleRoads.size()) < AMOUNT_OF_ROADS);
	if (ret)
	{
		ret = false;
		if (existingEdge(edge))
		{
			if (freeEdge(edge))
			{
				if( ((player == 1) && (p1SimpleRoads.size() >= 2)) || ((player == 2) && (p2SimpleRoads.size() >=2 )) )
				{
					if ((adjacentToOwnBuilding(edge, player)) || (adjacentToOwnRoad(edge, player)))		//contiguo a vertices propios o a un road propio
					{
						ret = true;
					}
				}
				else if (initPhaseOk(player, edge, ROAD))
				{
					ret = true;
				}
			}
		}
		if (ret)
		{
			pendingConstruction.type = ROAD;
			pendingConstruction.coords = edge;
			pendingConstruction.player = player;
		}
	}
	return ret;
}

construction_t catanMapModel::getPendingConstruction()
{
	return pendingConstruction;
}

void catanMapModel::cancelConstruction()
{
	pendingConstruction.type = NO_PCKG;
}

networkingEventTypes catanMapModel::buildPendingConstruction()
{
	networkingEventTypes ret = NO_PCKG;
	switch (pendingConstruction.type)
	{
	case SETTLEMENT:
		if (buildSettlement(pendingConstruction.coords, pendingConstruction.player))
		{
			ret = SETTLEMENT;
		}
		break;
	case ROAD:
		if (buildRoad(pendingConstruction.coords, pendingConstruction.player))
		{
			ret = ROAD;
		}
		break;
	case CITY:
		if (buildCity(pendingConstruction.coords, pendingConstruction.player))
		{
			ret = CITY;
		}
		break;
	}
	if (ret)
	{
		pendingConstruction.type = NO_PCKG;
	}
	return ret;
}

unsigned char catanMapModel::getAmountOfSettlementsLeft()
{
	unsigned char count = AMOUNT_OF_SETTLEMENTS;
	count -= (p1UsedVertexList.size() - p1Cities.size());
	return count;
}

unsigned char catanMapModel::getAmountOfCitiesLeft()
{
	return (AMOUNT_OF_CITIES - p1Cities.size());
}

unsigned char catanMapModel::getAmountOfRoadsLeft()
{
	return (AMOUNT_OF_ROADS - (p1LongRoads.size() + p1SimpleRoads.size()));
}

bool catanMapModel::buildRoad(string edge, char player)
{
	bool ret = false;
	if ((player == 1) || (player == 2))
	{
		ret = true;
		for (auto x : hiddenRoads)	//si era un hiddenRoad, pasara a ser uno simple o long, se borra de la lista de hidden
		{
			if (!x.compare(edge))
			{
				hiddenRoads.remove(x);
				break;									//consideramos necesario un break ya que se encontro lo buscado en la lista y fue eliminado
			}
		}
		road* roadToAdd = new road;
		if (adjacentToOwnBuilding(edge, player))	//si es simple road
		{
			if (player == 1)
			{
				roadToAdd->edge = edge;
				for (auto x : p1SimpleRoads)
				{
					if (adjacentRoads(edge, x->edge))
					{
						x->adjacentConstructedRoads.push_back(roadToAdd);
						roadToAdd->adjacentConstructedRoads.push_back(x);
					}
				}
				for (auto x : p1LongRoads)
				{
					if (adjacentRoads(edge, x->edge))
					{
						x->adjacentConstructedRoads.push_back(x);
						roadToAdd->adjacentConstructedRoads.push_back(x);
					}
				}
				roadToAdd->visited = false;
				p1SimpleRoads.push_back(roadToAdd);
			}
			else		//si player 2
			{
				roadToAdd->edge = edge;
				for (auto x : p2SimpleRoads)
				{
					if (adjacentRoads(edge, x->edge))
					{
						x->adjacentConstructedRoads.push_back(roadToAdd);
						roadToAdd->adjacentConstructedRoads.push_back(x);
					}
				}
				for (auto x : p2LongRoads)
				{
					if (adjacentRoads(edge, x->edge))
					{
						x->adjacentConstructedRoads.push_back(x);
						roadToAdd->adjacentConstructedRoads.push_back(x);
					}
				}
				roadToAdd->visited = false;
				p2SimpleRoads.push_back(roadToAdd);
			}
		}
		else	//sino es long road
		{
			if (player == 1)
			{
				roadToAdd->edge = edge;
				for (auto x : p1SimpleRoads)
				{
					if (adjacentRoads(edge, x->edge))
					{
						x->adjacentConstructedRoads.push_back(roadToAdd);
						roadToAdd->adjacentConstructedRoads.push_back(x);
					}
				}
				for (auto x : p1LongRoads)
				{
					if (adjacentRoads(edge, x->edge))
					{
						x->adjacentConstructedRoads.push_back(x);
						roadToAdd->adjacentConstructedRoads.push_back(x);
					}
				}
				roadToAdd->visited = false;
				p1LongRoads.push_back(roadToAdd);
			}
			else
			{
				roadToAdd->edge = edge;
				for (auto x : p2SimpleRoads)
				{
					if (adjacentRoads(edge, x->edge))
					{
						x->adjacentConstructedRoads.push_back(roadToAdd);
						roadToAdd->adjacentConstructedRoads.push_back(x);
					}
				}
				for (auto x : p2LongRoads)
				{
					if (adjacentRoads(edge, x->edge))
					{
						x->adjacentConstructedRoads.push_back(x);
						roadToAdd->adjacentConstructedRoads.push_back(x);
					}
				}
				roadToAdd->visited = false;
				p2LongRoads.push_back(roadToAdd);
			}
		}
	}
	return ret;
}

bool catanMapModel::buildSettlement(string vertex, char player)
{
	bool ret = false;
	if ((player == 1) || (player == 2))
	{
		ret = true;		//construccion valida
	
		for (auto x : allEdges)	//marca como hiddenRoad a todos los vertices adyacentes al settlement que sera construido
		{
			if (vertexAdjacentToRoad(vertex,x))
			{
				hiddenRoads.push_back(x);
			}
		}
		for (auto x : p1SimpleRoads)	//actualiza la lista de longRoads del jugador 1, y los que encuentra los saca de la lista de hiddenRoads
		{
			if (vertexAdjacentToRoad(vertex, x->edge))	//si un longRoad es adyacente al nuevo settlement, pasa a ser simpleRoad NO HACE FALTA ESTE COMMENT
			{
				hiddenRoads.remove(x->edge);
			}
		}
		for (auto x: p2SimpleRoads)	//actualiza la lista de longRoads del jugador 2, y en los hiddenRoads quedan los que deben quedar
		{
			if (vertexAdjacentToRoad(vertex, x->edge))	//si un longRoad es adyacente al nuevo settlement, pasa a ser simpleRoad
			{
				hiddenRoads.remove(x->edge);
			}
		}
		if (player == 1)
		{
			p1UsedVertexList.push_back(vertex);
		}
		else
		{
			p2UsedVertexList.push_back(vertex);
		}
	}
	return ret;
}

bool catanMapModel::buildCity(string vertex, char player)
{
	bool ret = false;
	if ((player == 1) || (player == 2))
	{
		ret = true;
		if (player == 1)
		{
			p1Cities.push_back(vertex);
		}
		else
		{
			p2Cities.push_back(vertex);
		}
	}
	return ret;
}

bool catanMapModel::initPhaseOk(char player, string coords, networkingEventTypes constType)
{
	bool ret = false;
	if (constType == SETTLEMENT)
	{
		if(player == 1)
		{
			if (p1UsedVertexList.size() == 0)
			{
				ret = true;
			}
			else if (p1UsedVertexList.size() == 1)
			{
				ret = p1SimpleRoads.size() == 1;
			}
		}
		else if (player == 2)
		{
			if (p2UsedVertexList.size() == 0)
			{
				ret = true;
			}
			else if (p2UsedVertexList.size() == 1)
			{
				ret = p2SimpleRoads.size() == 1;
			}
		}
	}
	else if (constType == ROAD)
	{
		if (player == 1)
		{
			if (p1SimpleRoads.size() == 0)	//si todavia no construyo ningun camino, debe tener un vertice construido 
			{
				if ((p1UsedVertexList.size() == 1) && vertexAdjacentToRoad(p1UsedVertexList.front(),coords))	//debe ser adyacente al unico vertice construido
				{
					ret = true;
				}
			}
			else if (p1SimpleRoads.size() == 1)	//si ya construyo un camino, debe tener dos settlements construidos
			{
				if ((p1UsedVertexList.size() == 2) && vertexAdjacentToRoad(p1UsedVertexList.back(), coords))	//debe ser adyacente al segundo settlement construido
				{
					ret = true;
				}
			}
		}
		else if (player == 2)
		{
			if (p2SimpleRoads.size() == 0)	//si todavia no construyo ningun camino, debe tener un vertice construido 
			{
				if ((p2UsedVertexList.size() == 1) && vertexAdjacentToRoad(p2UsedVertexList.front(), coords))	//debe ser adyacente al unico vertice construido
				{
					ret = true;
				}
			}
			else if (p2SimpleRoads.size() == 1)	//si ya construyo un camino, debe tener dos settlements construidos
			{
				if ((p2UsedVertexList.size() == 2) && vertexAdjacentToRoad(p2UsedVertexList.back(), coords))	//debe ser adyacente al segundo settlement construido
				{
					ret = true;
				}
			}
		}
	}
	return ret;
}

list<string> catanMapModel::getP1BuiltVertexes()
{
	return p1UsedVertexList;
}

list<string> catanMapModel::getP1Settlements()
{
	list<string> settlements = p1UsedVertexList;
	for (auto x : p1Cities)
	{
		settlements.remove(x);
	}
	return settlements;
}

list<string> catanMapModel::getP1Cities()
{
	return p1Cities;
}

list<string> catanMapModel::getP2BuiltVertexes()
{
	return p2UsedVertexList;
}

list<string> catanMapModel::getP2Settlements()
{
	list<string> settlements = p2UsedVertexList;
	for (auto x : p2Cities)
	{
		settlements.remove(x);
	}
	return settlements;
}

list<string> catanMapModel::getP2Cities()
{
	return p2Cities;
}

list<string> catanMapModel::getP1Roads()
{
	list<string> ret;
	for (auto x : p1SimpleRoads)
	{
		ret.push_back(x->edge);
	}
	for (auto x : p1LongRoads)
	{
		ret.push_back(x->edge);
	}
	return ret;
}

list<string> catanMapModel::getP2Roads()
{
	list<string> ret;
	for (auto x : p2SimpleRoads)
	{
		ret.push_back(x->edge);
	}
	for (auto x : p2LongRoads)
	{
		ret.push_back(x->edge);
	}
	return ret;
}
/*Devuelve un diccionario con el costo (2, 3 o 4) de cada recurso para el jugador
El diccionario tiene las claves definidas en resourceType, menos DESSERT
*/
map<resourceType, unsigned char> catanMapModel::getBankTradeCosts(unsigned char player)
{
	map<resourceType, unsigned char> ret = { { BRICK,4 },{ WOOD,4 },{ WOOL,4 },{ ORE,4 },{ WHEAT,4 } };
	resourceType resourceBenefited;
	list<string>::iterator it;
	list<string>::iterator end;
	if (player == 1)
	{
		it = p1UsedVertexList.begin();
		end = p1UsedVertexList.end();
	}
	else if (player == 2)
	{
		it = p2UsedVertexList.begin();
		end = p2UsedVertexList.end();
	}
	for (; it != end; it++)
	{
		resourceBenefited = connectsToPort(*it);
		if (resourceBenefited)
		{
			if (resourceBenefited != DESSERT)
			{
				ret[resourceBenefited] = 2;	//en ese recurso en especifico, tiene 2x1
			}
			else		//si devuelve DESSERT, tiene 3x1 en todo
			{
				for (auto& mapIt : ret)
				{
					if (mapIt.second == 4)
					{
						mapIt.second = 3;
					}
				}
			}
		}
	}
	return ret;
}

/*Verifica si un vertice se conecta a un puerto
En caso que no lo haga, devuelve 0
En caso que lo haga, devuelve el recurso beneficiado por el puerto
En caso que sea un puerto de 3x1 en todos los recursos, devuelve DESSERT*/
resourceType catanMapModel::connectsToPort(string vertex)
{
	string portVertex[4];
	resourceType ret = static_cast<resourceType>(0);
	for (unsigned int i = 0; (i < 3) && !ret; i++)
	{
		if (oceanPieces[i].hasOnePort())
		{
			portVertex[0] = greater2CharVertex(i);	//uno de los vertices con puerto es el de long 2, que tiene el numero de puerto y la letra mas grande
			portVertex[1] = middleCharVertex(portVertex[0]);	//el otro vertice sera el que tiene los mismos caracteres que el anterior, pero con una letra en el medio
		}
		else
		{
			portVertex[0] = greater2CharVertex(i);	//uno de los vertices con puerto es el de long 2, que tiene el numero de puerto y la letra mas grande
			portVertex[1] = portVertex[0];
			portVertex[1] += thirdLetter(portVertex[0]);	//otro vertice sera el que tiene long 3 y comparte los primeros 2 caracteres con el anterior
			portVertex[2] = less2CharVertex(i);		//otro vertice sera de long2, con el numero de puerto y la letra mas chica
			if (i > 0)	//si no es la pieza 0
			{
				portVertex[3] = (i - 1) + '0';	//el ultimo vertice compartira los caracteres del anterior, y se le antepone el numero de la pieza anterior (i-1)
				portVertex[3] += portVertex[2];
			}
			else		//si es la pieza 0
			{
				portVertex[3] = portVertex[2];
				portVertex[3].insert(1, 1, '5');	//el ultimo vertice sera el "05A"
			}
		}
		int j = 0;
		for (auto temp : portVertex)
		{
			if (vertex == temp)
			{
				if (j < 2)
				{
					ret = oceanPieces[i].getResource();
				}
				else
				{
					ret = DESSERT;
				}
				break;
			}
			j++;
		}
		if (ret)
		{
			break;
		}
	}
	for (unsigned int i = 3; (i < NUMBER_OF_OCEAN_PIECES) && !ret; i++)
	{
		if (oceanPieces[i].hasOnePort())
		{
			portVertex[0] = less2CharVertex(i);
			portVertex[1] = portVertex[0];
			portVertex[1] += thirdLetter(portVertex[0]);
		}
		else
		{
			portVertex[0] = less2CharVertex(i);
			portVertex[1] = middleCharVertex(portVertex[0]);
			portVertex[2] = greater2CharVertex(i);
			portVertex[3] = (i - 1) + '0';
			portVertex[3] += portVertex[2];
		}
		int j = 0;
		for (auto temp : portVertex)
		{
			if (vertex == temp)
			{
				if (j < 2)
				{
					ret = oceanPieces[i].getResource();
				}
				else
				{
					ret = DESSERT;
				}
				break;
			}
			j++;
		}
		if (ret)
		{
			break;
		}
	}
	return ret;
}

/*Devuelve para la pieza de mar pieceNum su vertice adyacente con la letra de mayor ASCII*/
string catanMapModel::greater2CharVertex(unsigned int pieceNum)
{
	string ret;
	ret = static_cast<char>(pieceNum + '0');	//en la primera posicion tiene el numero de la pieza
	list<string>::iterator it;
	char maxAscii = 0;
	char found = 0;
	bool finished = false;
	for (it = allVertexes.begin(); (it != allVertexes.end()) && !finished; it++)
	{
		if (((*it)[0] == (pieceNum+'0')) && (it->length() == 2))	//si es un vertice adyacente a esa pieza de mar
		{
			if ((*it)[1] > maxAscii)
			{
				maxAscii = (*it)[1];
			}
			found++;
			if (found == 2)	//si ya encontro los dos vertices de long 2 de esa pieza de mar, en maxAscii ya esta el mayor
			{
				finished = true;
			}
		}
	}
	ret += maxAscii;	//en la segunda posicion tiene la letra de mayor ASCII
	return ret;
}

/*Devuelve para la pieza de mar pieceNum su vertice adyacente con la letra de menor ASCII*/
string catanMapModel::less2CharVertex(unsigned int pieceNum)
{
	string ret;
	ret	= static_cast<char>(pieceNum + '0');	//en la primera posicion tiene el numero de la pieza
	list<string>::iterator it;
	char minAscii = 'Z';
	char found = 0;
	bool finished = false;
	for (it = allVertexes.begin(); (it != allVertexes.end()) && !finished; it++)
	{
		if (((*it)[0] == (pieceNum+'0')) && (it->length() == 2))	//si es un vertice adyacente a esa pieza de mar
		{
			if ((*it)[1] < minAscii)
			{
				minAscii = (*it)[1];
			}
			found++;
			if (found == 2)	//si ya encontro los dos vertices de long 2 de esa pieza de mar, en minAscii ya esta el menor
			{
				finished = true;
			}
		}
	}
	ret += minAscii;	//en la segunda posicion tiene la letra de mayor ASCII
	return ret;
}

/*VERTEX DEBE SER UN VERTICE DE DOS CARACTERES
Devuelve el vertice que tiene los mismos caracteres que vertex con otra letra en el medio*/
string catanMapModel::middleCharVertex(string vertex)
{
	string ret;
	list<string>::iterator it;
	bool done = false;
	for (it = allVertexes.begin(); (it != allVertexes.end()) && !done; it++)
	{
		if (it->length() == 3)
		{
			if (((*it)[0] == vertex[0]) && ((*it)[2] == vertex[1]))
			{
				ret = *it;
				done = true;
			}
		}
	}
	return ret;
}

/*VERTEX DEBE SER UN VERTICE DE DOS CARACTERES
Devuelve la tercera letra del vertice que comienza con los mismos dos caracteres que vertex*/
char catanMapModel::thirdLetter(string vertex)
{
	char ret = 0;
	bool done = false;
	list<string>::iterator it;
	size_t found;
	for (it = allVertexes.begin(); (it != allVertexes.end()) && !done; it++)
	{
		found = it->find(vertex);
		if (found != string::npos)	//si encontro la secuencia de caracteres de vertex, se queda con el tercer caracter
		{
			ret = (*it)[2];
		}
	}
	return ret;
}

bool catanMapModel::freeEdge(string edge)
{
	bool ret = true;
	list<road *>::iterator it;
	for (it = p1SimpleRoads.begin(); (it != p1SimpleRoads.end()) && ret; it++)
	{
		ret = (*it)->edge.compare(edge);			//se encontro ret = false
	}
	for (it = p2SimpleRoads.begin(); (it != p2SimpleRoads.end()) && ret; it++)
	{
		ret = (*it)->edge.compare(edge);			//se encontro ret = false
	}
	for (it = p1LongRoads.begin(); (it != p1LongRoads.end()) && ret; it++)
	{
		ret = (*it)->edge.compare(edge);			//se encontro ret = false
	}
	for (it = p2LongRoads.begin(); (it != p2LongRoads.end()) && ret; it++)
	{
		ret = (*it)->edge.compare(edge);			//se encontro ret = false
	}
	return ret;
}

bool catanMapModel::adjacentToOwnBuilding(string edge, char player)
{
	bool ret = false;
	list<string>::iterator it;
	list<string>::iterator end;
	if (player == 1)
	{
		it = p1UsedVertexList.begin();
		end = p1UsedVertexList.end();
	}
	else if (player == 2)
	{
		it = p2UsedVertexList.begin();
		end = p2UsedVertexList.end();
	}
	for (; (it != end) && !ret; it++)
	{
		ret = vertexAdjacentToRoad(*it, edge);
	}
	return ret;
}

bool catanMapModel::adjacentToOwnRoad(string edge, char player)
{
	bool ret = false;
	//compara el eje pedido con todos los roads del jugador
	list<road *>::iterator it;
	list<road *>::iterator end;
	if (player == 1)
	{
		it = p1SimpleRoads.begin();
		end = p1SimpleRoads.end();
	}
	else if (player == 2)
	{
		it = p2SimpleRoads.begin();
		end = p2SimpleRoads.end();
	}
	for (; (it != end) && !ret; it++)
	{
		ret = adjacentRoads(edge, (*it)->edge);
	}
	if (!ret)
	{
		if (player == 1)
		{
			it = p1LongRoads.begin();
			end = p1LongRoads.end();
		}
		else if (player == 2)
		{
			it = p2LongRoads.begin();
			end = p2LongRoads.end();
		}
		for (; (it != end) && !ret; it++)
		{
			ret = adjacentRoads(edge, (*it)->edge);
		}
	}
	return ret;
}

/*Si devuelve true cambia pendingConstruction*/
bool catanMapModel::checkAvailableSettlement(string vertex, char player)
{
	bool ret = false;
	bool max = player == 1 ? ((p1UsedVertexList.size() - p1Cities.size()) < AMOUNT_OF_SETTLEMENTS) : ((p2UsedVertexList.size() - p2Cities.size()) < AMOUNT_OF_SETTLEMENTS);
	if (max)
	{
		if (existingVertex(vertex))
		{
			if (player == 1)
			{
				for (auto x : p1UsedVertexList)
				{
					if (x == vertex)
					{
						max = false;
						break;
					}
				}
			}
			else if (player == 2)
			{
				for (auto x : p2UsedVertexList)
				{
					if (x == vertex)
					{
						max = false;
						break;
					}
				}
			}
			if (max && ((player == 1) || (player == 2)))
			{
				if (!adjacentToHiddenRoad(vertex))
				{
					if (!adjacentToSimpleRoad(vertex))
					{
						if (adjacentToLongRoad(vertex, player) || initPhaseOk(player,vertex,SETTLEMENT))
						{
							pendingConstruction.type = SETTLEMENT;
							pendingConstruction.coords = vertex;
							pendingConstruction.player = player;
							ret = true;
						}
					}
				}
			}
		}
	}
	return ret;
}

bool catanMapModel::existingVertex(string vertex)
{
	bool ret = false;
	list<string>::iterator it;
	for (it = allVertexes.begin(); (it != allVertexes.end()) && !ret; it++)
	{
		if (!it->compare(vertex))
		{
			ret = true;
		}
	}
	return ret;
}

bool catanMapModel::existingEdge(string edge)
{
	bool ret = false;
	list<string>::iterator it;
	for (it = allEdges.begin(); (it != allEdges.end()) && !ret; it++)
	{
		if (!it->compare(edge))
		{
			ret = true;
		}
	}
	return ret;
}

bool catanMapModel::checkAvailableCity(string vertex, char player)
{
	bool ret = false;
	if (player == 1)
	{
		if((p1Cities.size() < AMOUNT_OF_CITIES) && (p1UsedVertexList.size() >= 2) && (p1SimpleRoads.size() >= 2))
		{
			list<string>::iterator it;
			for (it = p1UsedVertexList.begin(); (it != p1UsedVertexList.end()) && !ret; it++)		//itero para ver si ya hay settlement construido
			{
				ret = !(it->compare(vertex));			//si esta ocupado ret = true
				if (ret == true)
				{
					list<string>::iterator iter;
					for (iter = p1Cities.begin(); (iter != p1Cities.end()) && ret; iter++)			//itero para ver si ya es una ciudad
					{
						if (!iter->compare(*it))
						{
							ret = false;
						}
					}
				}
			}
		}
	}
	else if (player == 2)
	{
		if ((p2Cities.size() < AMOUNT_OF_CITIES) && (p2UsedVertexList.size() >= 2) && (p2SimpleRoads.size() >= 2)) 
		{
			list<string>::iterator it;
			for (it = p2UsedVertexList.begin(); (it != p2UsedVertexList.end()) && !ret; it++)		//itero para ver si ya hay settlement construido
			{
				ret = !(it->compare(vertex));			//si esta ocupado ret = true
				if (ret == true)
				{
					list<string>::iterator iter;
					for (iter = p2Cities.begin(); (iter != p2Cities.end()) && ret; iter++)			//itero para ver si ya es una ciudad
					{
						if (!iter->compare(*it))
						{
							ret = false;
						}
					}
				}
			}
		}
	}
	if (ret)
	{
		pendingConstruction.type = CITY;
		pendingConstruction.coords = vertex;
		pendingConstruction.player = player;
	}
	return ret;
}

unsigned char catanMapModel::getP1LongestRoad()
{
	unsigned char longestRoad = 0;
	list<road *> allRoads = p1LongRoads;
	for (auto x : p1SimpleRoads)	//carga en allRoads todos los roads
	{
		allRoads.push_back(x);
	}
	if (allRoads.size() > 0)
	{
		road * firstRoad = endpointSearchRec(allRoads.front());	//busca un camino en una punta
		for (auto x : allRoads)	//borra todas las marcas que haya hecho la recursividad anterior
		{
			x->visited = false;
		}
		longestRoadSearchRec(firstRoad, longestRoad, 0);
		for (auto x : allRoads)
		{
			if (!(x->visited))
			{
				endpointSearchRec(x);
				for (auto x : allRoads)
				{
					x->visited = false;
				}
				longestRoadSearchRec(x, longestRoad, 0);
				break;
			}
		}
	}
	return longestRoad;
}

road * catanMapModel::endpointSearchRec(road * randRoad)
{
	road * nextRoad = hasUnvisitedNeighbours(randRoad);
	if (nextRoad  != nullptr)
	{
		randRoad->visited = true;
		return endpointSearchRec(nextRoad);
	}
	else
	{
		return randRoad;
	}
}

void catanMapModel::longestRoadSearchRec(road * actualRoad, unsigned char & longestRoad, unsigned char depth)
{
	if (hasUnvisitedNeighbours(actualRoad) != nullptr)
	{
		actualRoad->visited = true;
		for (auto x : actualRoad->adjacentConstructedRoads)
		{
			if (!(x->visited))
			{
				longestRoadSearchRec(x, longestRoad, depth + 1);
			}
		}
	}
	else
	{
		if (depth >= longestRoad)
		{
			longestRoad = depth + 1;
		}
	}
}

/*Devuelve nullptr si no tiene vecinos no visitados, sino devuelve un puntero a algun vecino visitado*/
road * catanMapModel::hasUnvisitedNeighbours(road * actualRoad)
{
	road * ret = nullptr;
	for (auto x : actualRoad->adjacentConstructedRoads)
	{
		if (!( x->visited))	
		{
			ret = x;
			break;
		}
	}	
	return ret;
}

unsigned char catanMapModel::getP2LongestRoad()
{
	unsigned char longestRoad = 0;
	list<road *> allRoads = p2LongRoads;
	for (auto x : p2SimpleRoads)	//carga en allRoads todos los roads
	{
		allRoads.push_back(x);
	}
	if (allRoads.size() > 0)
	{
		road * firstRoad = endpointSearchRec(allRoads.front());	//busca un camino en una punta
		for (auto x : allRoads)	//borra todas las marcas que haya hecho la recursividad anterior
		{
			x->visited = false;
		}
		longestRoadSearchRec(firstRoad, longestRoad, 0);
		for (auto x : allRoads)
		{
			if (!(x->visited))
			{
				endpointSearchRec(x);
				for (auto x : allRoads)
				{
					x->visited = false;
				}
				longestRoadSearchRec(x, longestRoad, 0);
				break;
			}
		}
	}
	return longestRoad;
}

list<pepe> catanMapModel::getSelectedHex(unsigned int diceValue)
{
	list<pepe> ret;
	unsigned char letter = 'A';
	if ((diceValue >= 2) && (diceValue <= 12))
	{
		for (auto x : hexagons)
		{
			if (x.circularToken == diceValue)
			{
				ret.push_back({ letter, x.hexResource });
			}
			letter++;
		}
	}
	return ret;
}

/*Devuelve true si el vertice y el eje recibidos son adyacentes*/
bool catanMapModel::vertexAdjacentToRoad(string vertex, string road)
{
	unsigned char matches;
	bool ret = false;
	if (vertex.length() == 3)
	{
		if (!((vertex.find_first_of("012345") == string::npos) && (road.length() != 2)))
		{
			matches = 0;
			for (unsigned int i = 0; i < vertex.length(); i++)
			{
				size_t found = road.find(vertex[i]);	//busca caracter a caracter del vertice en el camino siendo evaluado	
				if (found != string::npos)	//si lo encontro
				{
					bool hasTwoNumbers = (vertex.find_first_of("012345") != vertex.find_last_of("012345"));
					if ((i != 1) || !((found == 2) && (road.length() == 3))) 
					{
						if ( (i!=2) || !hasTwoNumbers || (found==1) ) 
						{
							matches++;
						}
					}
				}
			}
			if (matches >= 2)	//si dos letras del vertice coinciden con alguna del camino, son adyacentes
			{
				if (!( (vertex.find_first_of("012345") == 0) && (road.find(vertex.substr(0,2)) == 0) && (road != vertex) ) )
				{
					ret = true;
				}
			}
		}
	}
	else if (vertex.length() == 2)		//en el caso de los vertices que comparten con el mar
	{
		ret = ((road.find(vertex) == 0) ? true : false);	//con la correccion de la nomenclatura se cumple esta condicion, el camino
	}													//empieza con los dos caracteres de su vertice adyacente de dos caracteres		
	return ret;
}

bool catanMapModel::adjacentRoads(string road1, string road2)
{
	bool ret = false;
	unsigned char matches;
	size_t found;
	list<string>::iterator it;
	if (road1.length() == 2)
	{
		for (it = allVertexes.begin(); (it != allVertexes.end()) && !ret; it++)
		{
			if (vertexAdjacentToRoad(*it, road1))
			{
				ret = vertexAdjacentToRoad(*it, road2);	
			}
		}
	}
	else if (road1.length() == 3)
	{
		for (it = allVertexes.begin(); (it != allVertexes.end()) && !ret; it++)
		{
			if (it->length() == 2)
			{
				found = road1.find(*it);
				if (found == 0)
				{
					ret = vertexAdjacentToRoad(*it, road2);
				}
			}
			else
			{
				matches = 0;
				for (unsigned int i = 0; i < it->length(); i++)
				{
					size_t found = road1.find((*it)[i]);	//busca caracter a caracter del vertice siendo evaluado en el camino 
					if (found != string::npos)				//si lo encontro
					{
						matches++;
					}
				}
				if (matches == 3)	//si las tres letras del vertice coinciden las tres del camino, aunque sea en otro orden, son adyacentes
				{
					ret = vertexAdjacentToRoad(*it, road2);
				}
			}
		}
	}
	return ret;
}

catanMapModel::~catanMapModel()
{

}

void oceanPiece::setResource(unsigned char resource_)
{
	resource = static_cast<resourceType>(resource_);
	switch (resource_)
	{
	case 'N': case 'P':	case 'M':
		hasTwoPorts = false;
		break;
	case 'T': case 'O': case 'L':
		hasTwoPorts = true;
		break;
	}
}

resourceType oceanPiece::getResource()
{
	return resource;
}

bool oceanPiece::hasOnePort()
{
	return !hasTwoPorts;
}