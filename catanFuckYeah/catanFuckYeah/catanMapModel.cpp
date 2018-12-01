#include "catanMapModel.h"



catanMapModel::catanMapModel()
{

}

catanMapModel::catanMapModel(string map)
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
	list<string>::iterator end;
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
		ret = vertexAdjacentToRoad(vertex, *it);
	}
	return ret;
}

/*bool catanMapModel::freeVertex(string vertex)
{
	bool ret = true;
	list<string>::iterator it;
	for (it = p1UsedVertexList.begin(); (it != p1UsedVertexList.end()) && ret; it++)
	{
		if (!(it->compare(vertex)))
		{
			ret = false;
		}
	}
	for (it = p2UsedVertexList.begin(); (it != p2UsedVertexList.end()) && ret; it++)
	{
		if (!(it->compare(vertex)))
		{
			ret = false;
		}
	}
	return ret;
}*/


bool catanMapModel::checkAvailableRoad(string edge, char player)
{
	bool ret = false;
	if (freeEdge(edge))
	{
		if ((adjacentToOwnBuilding(edge, player)) || (adjacentToOwnRoad(edge, player)))		//contiguo a vertices propios o a un road propio
		{
			ret = true;
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
	for ( ; (it != end) && !ret ; it++)
	{
		ret = vertexAdjacentToRoad(*it, edge);
	}
	return ret;
}

bool catanMapModel::adjacentToOwnRoad(string edge, char player)
{
	bool ret = false;
	//comparar el eje pedido con todos los roads del jugador
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
	for (; (it != end) && !ret ; it++)
	{
		ret = adjacentRoads(edge,*it);
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
	bool ret = false;
	if ((player == 1) || (player == 2))
	{
		if (!adjacentToHiddenRoad(vertex))
		{
			if (!adjacentToSimpleRoad(vertex))
			{
				if (adjacentToLongRoad(vertex, player))
				{
					ret = true;	//ACORDARSE AL PONER UN SETTLEMENT DE SACAR LOS LONG ROADS ADYACENTES DE LA LISTA
				}
			}
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

/*Devuelve true si el vertice y el eje recibidos son adyacentes*/
bool catanMapModel::vertexAdjacentToRoad(string vertex, string road)
{
	unsigned char matches;
	bool ret = false;
	if (vertex.length() == 3)
	{
		matches = 0;
		for (int i = 0; i < vertex.length(); i++)	
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
		for (it = static_cast<list<string>>(allVertexes).begin(); (it != allVertexes.end()) && !ret; it++)
		{
			matches = 0;
			for (int i = 0; i < it->length(); i++)
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
		for (it = static_cast<list<string>>(allVertexes).begin(); (it != allVertexes.end()) && !ret; it++)
		{
			if (it->length() == 2)
			{
				found = road1.find(*it);
				if (found == 0)
				{
					ret = vertexAdjacentToRoad(*it,road2);
				}
			}
			else
			{
				matches = 0;
				for (int i = 0; i < it->length(); i++)
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
