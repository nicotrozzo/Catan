#include "catanMapModel.h"

/*Calcula el mapa random*/
catanMapModel::catanMapModel()
{
	vector<resource>allResources({ {WOOD,3}, {BRICK,3}, {ORE,3}, {WHEAT,3}, {WOOL,3}, {DESSERT,1} });
	array<unsigned char, HEX_COUNT - 1> allCircularTokens = { 2,3,3,4,4,5,5,6,6,8,8,9,9,10,10,11,11,12 };
	array<unsigned char, NUMBER_OF_OCEAN_PIECES> allOceanPieces = { WOOD,BRICK,ORE,WHEAT,WOOL,DESSERT };
	int resRandNum;							//RECORDAR SRAND EN EL MAIN!!!!!!!!!!!!!!!!
	int tokenRandNum;
	int oceanRandNum;
	bool written;			//indica si ya se encontro en la lista entera lo que se buscaba en cada iteracion
	for (int i = 0; i < HEX_COUNT; i++)					//calculo random del mapa
	{
		resRandNum = rand() % NUMBER_OF_RESOURCES;
		tokenRandNum = rand() % (HEX_COUNT - 1);
		written = false;
		for (int j = 0; (j < NUMBER_OF_RESOURCES) && !written; j++)
		{
			if (allResources[(resRandNum + j) % NUMBER_OF_RESOURCES].resCount > 0)
			{
				hexagons[i].hexResource = allResources[(resRandNum + j) % NUMBER_OF_RESOURCES].res;
				allResources[(resRandNum + j) % NUMBER_OF_RESOURCES].resCount--;
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
	map <unsigned char, unsigned char> allResources = { {WOOD,0}, {BRICK,0}, {ORE,0}, {WHEAT,0}, {WOOL,0}, {DESSERT,0} };
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
					if (map_[i] == DESSERT)
					{
						error = (allResources[map_[i]]) > 1 ? true : false;
					}
					else if (allResources[map_[i]] > 3)
					{
						error = true;					//si se pasa de 3 uno que no sea un desierto hay error
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
	list<string>::iterator it;
	for (it = p1SimpleRoads.begin(); (it != p1SimpleRoads.end()) && !ret; it++)
	{
		ret = vertexAdjacentToRoad(vertex, *it);	//sale si encontro que el vertice es adyacente a algun camino
	}
	for (it = p2SimpleRoads.begin(); (it != p2SimpleRoads.end()) && !ret; it++)
	{
		ret = vertexAdjacentToRoad(vertex, *it);	//sale si encontro que el vertice es adyacente a algun camino
	}
	return ret;
}

/*Devuelve true si el vertice es adyacente a un road en cuyos vertices se puede construir*/
bool catanMapModel::adjacentToLongRoad(string vertex, char player)
{
	bool ret = false;
	list<string>::iterator it;
	if (player == 1)
	{
		for (it = p1LongRoads.begin() ; (it != p1LongRoads.end()) && !ret; it++)
		{
			ret = vertexAdjacentToRoad(vertex, *it);
		}
	}
	else if (player == 2)
	{
		for (it = p2LongRoads.begin(); (it != p2LongRoads.end()) && !ret; it++)
		{
			ret = vertexAdjacentToRoad(vertex, *it);
		}
	}
	return ret;
}

bool catanMapModel::checkAvailableRoad(string edge, char player)
{
	bool ret = false;
	if (existingEdge(edge))
	{
		if (freeEdge(edge))
		{
			if ((p1UsedVertexList.size() == 2) && (p1SimpleRoads.size() == 1))//capaz analizar ademas cuando tiene 1 settllement y 1 road
			{
				list<string>::iterator it = ++p1UsedVertexList.begin();
				if (vertexAdjacentToRoad(*it, edge)) //el road debe ser adyacente al segundo settlement construido
				{
					ret = true;
				}
			}
			else if ((p2UsedVertexList.size() == 2) && (p2SimpleRoads.size() == 1))
			{
				list<string>::iterator it = ++p2UsedVertexList.begin();
				if (vertexAdjacentToRoad(*it, edge)) //el road debe ser adyacente al segundo settlement construido
				{
					ret = true;
				}
			}
			else if ((adjacentToOwnBuilding(edge, player)) || (adjacentToOwnRoad(edge, player)))		//contiguo a vertices propios o a un road propio
			{
				ret = true;
			}
		}
	}

	return ret;
}

bool catanMapModel::buildRoad(string edge, char player)
{
	bool ret = false;
	if ((checkAvailableRoad(edge, player)) && ((player == 1) || (player == 2)))
	{
		ret = true;
		list<string>::iterator it;
		for (it = hiddenRoads.begin(); it != hiddenRoads.end(); it++)	//si era un hiddenRoad, pasara a ser uno simple o long, se borra de la lista de hidden
		{
			if (!it->compare(edge))
			{
				hiddenRoads.erase(it);
				break;									//consideramos necesario un break ya que se encontro lo buscado en la lista y fue eliminado
			}
		}
		if (adjacentToOwnBuilding(edge, player))	//si es simple road
		{
			if (player == 1)
			{
				p1SimpleRoads.push_back(edge);
			}
			else
			{
				p2SimpleRoads.push_back(edge);
			}
		}
		else	//sino es long road
		{
			if (player == 1)
			{
				p1LongRoads.push_back(edge);
			}
			else
			{
				p2LongRoads.push_back(edge);
			}
		}
	}
	return ret;
}

bool catanMapModel::buildSettlement(string vertex, char player)
{
	bool ret = false;
	if (checkAvailableSettlement(vertex, player) && ((player == 1) || (player == 2)))
	{
		ret = true;		//construccion valida
		list<string>::iterator it;
		for (it = allEdges.begin(); it != allEdges.end(); it++)	//marca como hiddenRoad a todos los vertices adyacentes al settlement que sera construido
		{
			if (vertexAdjacentToRoad(vertex, *it))
			{
				hiddenRoads.push_back(*it);
			}
		}
		for (it = p1SimpleRoads.begin(); it != p1SimpleRoads.end(); it++)	//actualiza la lista de longRoads del jugador 1, y los que encuentra los saca de la lista de hiddenRoads
		{
			if (vertexAdjacentToRoad(vertex, *it))	//si un longRoad es adyacente al nuevo settlement, pasa a ser simpleRoad NO HACE FALTA ESTE COMMENT
			{
				//p1SimpleRoads.push_back(*it);	//YA ESTA EN SIMPLE
				//p1LongRoads.erase(it);     //CREEMOS QUE NO ES NECESARIO BORRAR DE LAS LONG
				hiddenRoads.remove(*it);
			}
		}
		for (it = p2SimpleRoads.begin(); it != p2SimpleRoads.end(); it++)	//actualiza la lista de longRoads del jugador 2, y en los hiddenRoads quedan los que deben quedar
		{
			if (vertexAdjacentToRoad(vertex, *it))	//si un longRoad es adyacente al nuevo settlement, pasa a ser simpleRoad
			{
				//p2SimpleRoads.push_back(*it);
				//p2LongRoads.erase(it);
				hiddenRoads.remove(*it);
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
	if (checkAvailableCity(vertex, player) && ((player == 1) || (player == 2)))
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

list<string> catanMapModel::getP1BuiltVertexes()
{
	return p1UsedVertexList;
}

list<string> catanMapModel::getP1Cities()
{
	return p1Cities;
}

list<string> catanMapModel::getP2BuiltVertexes()
{
	return p2UsedVertexList;
}

list<string> catanMapModel::getP2Cities()
{
	return p2Cities;
}

/*Devuelve un diccionario con el costo (2, 3 o 4) de cada recurso para el jugador
El diccionario tiene las claves definidas en resourceType, menos DESSERT
*/
map<resourceType,unsigned char> catanMapModel::getBankTradeCosts(unsigned char player)
{
	map<resourceType, unsigned char> ret = { {BRICK,4},{WOOD,4},{WOOL,4},{ORE,4},{WHEAT,4} };
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
	for ( ; it != end ; it++)
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
				for (auto mapIt : ret)
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
	for (unsigned int i = 0 ; (i < 3) && !ret ; i++)
	{
		if (oceanPieces[i].hasOnePort())
		{
			portVertex[0] = greater2CharVertex(i);	//uno de los vertices con puerto es el de long 2, que tiene el numero de puerto y la letra mas grande
			portVertex[1]= middleCharVertex(portVertex[0]);	//el otro vertice sera el que tiene los mismos caracteres que el anterior, pero con una letra en el medio
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
		for(auto temp : portVertex)
		{
			if (vertex == temp)
			{
				ret = oceanPieces[i].getResource();
			}
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
			portVertex[3] = (i-1) + '0';
			portVertex[3] += portVertex[2];
		}
		for (auto temp : portVertex)
		{
			if (vertex == temp)
			{
				ret = oceanPieces[i].getResource();
			}
		}
	}
	return ret;
}

/*Devuelve para la pieza de mar pieceNum su vertice adyacente con la letra de mayor ASCII*/
string catanMapModel::greater2CharVertex(unsigned int pieceNum)
{
	string ret;
	ret += static_cast<char>(pieceNum + '0');	//en la primera posicion tiene el numero de la pieza
	list<string>::iterator it;
	char maxAscii = 0;
	char found = 0;
	bool finished = false;
	for (it = allVertexes.begin(); (it != allVertexes.end()) && !finished ; it++)
	{
		if( ((*it)[0] == pieceNum) && (it->length()==2) )	//si es un vertice adyacente a esa pieza de mar
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
	ret += static_cast<char>(pieceNum + '0');	//en la primera posicion tiene el numero de la pieza
	list<string>::iterator it;
	char minAscii = 'Z';
	char found = 0;
	bool finished = false;
	for (it = allVertexes.begin(); (it != allVertexes.end()) && !finished; it++)
	{
		if (((*it)[0] == pieceNum) && (it->length() == 2))	//si es un vertice adyacente a esa pieza de mar
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
			if( ((*it)[0] == vertex[0]) && ((*it)[2] == vertex[1]))
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
	for (it = allVertexes.begin(); (it != allVertexes.end()) && !done ; it++)
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
	list<string>::iterator it;
	for (it = p1SimpleRoads.begin(); (it != p1SimpleRoads.end()) && ret; it++)
	{
		ret = it->compare(edge);			//se encontro ret = false
	}
	for (it = p2SimpleRoads.begin(); (it != p2SimpleRoads.end()) && ret; it++)
	{
		ret = it->compare(edge);			//se encontro ret = false
	}
	for (it = p1LongRoads.begin(); (it != p1LongRoads.end()) && ret; it++)
	{
		ret = it->compare(edge);			//se encontro ret = false
	}
	for (it = p2LongRoads.begin(); (it != p2LongRoads.end()) && ret; it++)
	{
		ret = it->compare(edge);			//se encontro ret = false
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
	list<string>::iterator it;
	list<string>::iterator end;
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
		ret = adjacentRoads(edge, *it);
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
			ret = adjacentRoads(edge, *it);
		}
	}
	return ret;
}

bool catanMapModel::checkAvailableSettlement(string vertex, char player)
{
	bool validVertex = false;
	bool ret = false;
	if (existingVertex(vertex))
	{
		validVertex = true;
		if ((player == 1) || (player == 2))
		{
			if (!adjacentToHiddenRoad(vertex))
			{
				if (!adjacentToSimpleRoad(vertex))
				{
					if (adjacentToLongRoad(vertex, player) || ((player == 1) && (p1UsedVertexList.size() < 2)) || ((player == 2) && (p2UsedVertexList.size() < 2)))
					{
						ret = true;
					}
				}
			}
		}
	}
	if (!validVertex)
	{
		ret = false;
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
	else if (player == 2)
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
	return ret;
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
		matches = 0;
		for (unsigned int i = 0; i < vertex.length(); i++)
		{
			size_t found = road.find(vertex[i]);	//busca caracter a caracter del vertice en el camino siendo evaluado	
			if (found != string::npos)	//si lo encontro
			{
				matches++;
			}
		}
		if (matches >= 2)	//si dos letras del vertice coinciden con alguna del camino, son adyacentes
		{
			ret = true;
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
			matches = 0;
			for (unsigned int i = 0; i < it->length(); i++)
			{
				found = road1.find((*it)[i]);	//busca caracter a caracter del vertice siendo evaluado en el camino 
				if (found != string::npos)				//si lo encontro
				{
					matches++;
				}
			}
			if (matches >= 2)	//si dos letras del vertice coinciden con alguna del camino, son adyacentes
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