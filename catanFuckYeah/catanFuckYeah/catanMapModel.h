#pragma once
#include "EDASubject.h"

class hexagon
{
	unsigned char circularToken;
	unsigned char resource;
};



class catanMapModel : public EDASubject
{
public:
	catanMapModel();
	catanMapModel(string map);
	unsigned char getRobberPos() { return robberPos; }

	//bool freeVertex(string vertex);
	bool checkAvailableRoad(string edge, char player);	//devuelve true si el jugador indicado puede construir un camino en ese lado
	bool checkAvailableSettlement(string vertex, char player);	//devuelve true si el vertice seleccionado es valido para la construccion de un settlementdeu
	bool checkAvailableCity(string vertex, char player);	//devuelve true si el vertice seleccionado es valido para la construccion de una ciudad

	//freevertex();
	~catanMapModel();
private:
	unsigned char robberPos;
	string oceanPieces;
	list <hexagon> hexagons;
	list <string> hiddenRoads;		//caminos que son contiguos a un vertice ocupado, pero que no estan ocupados
	list <string> p1SimpleRoads;	//ejes construidos contiguos a un vertice ocupado por el jugador 1
	list <string> p1LongRoads;		//ejes construidos, a una distancia mayor a 1 de un vertice ocupado por el jugador 1
	list <string> p1UsedVertexList;	//cuando un settlement se transforma en city sigue estando en esta lista	
	list <string> p1Cities;			
	list <string> p2SimpleRoads;	//ejes construidos contiguos a un vertice ocupado por el jugador 2
	list <string> p2LongRoads;		//ejes construidos, a una distancia mayor a 1 de un vertice ocupado por el jugador 2
	list <string> p2UsedVertexList;	//cuando un settlement se transforma en city sigue estando en esta lista	
	list <string> p2Cities;
	bool adjacentToLongRoad(string vertex, char player);
	bool adjacentToHiddenRoad(string vertex);
	bool adjacentToSimpleRoad(string vertex);
	bool vertexAdjacentToRoad(string vertex, string it);
	bool adjacentRoads(string road1, string road2);
	bool adjacentToOwnBuilding(string edge, char player);
	bool adjacentToOwnRoad(string edge, char player);
	bool freeEdge(string edge);
	const list< string > allVertexes = {
	"0A", "0B", "01C",
	"05A", "0AB", "0BC", "1C",
	"5AD", "3AB", "BCF", "1CG",
	"5D", "ADE", "BEF", "CFG", "1G",
	"5DH", "DEI", "EFJ", "FGK", "1GL",
	"5H", "DHI", "EIJ", "FJK", "GKL", "12L",
	"45H", "HIM", "IJN", "JKO", "KLP", "2L",
	"4HM", "IMN", "JNO", "KOP", "2LP",
	"4M", "NMQ", "NOR", "OPS", "2P",
	"4MQ", "NQR", "ORS", "2PS",
	"4Q", "3QR", "3RS", "23S",
	"34Q", "3R", "3S"
	};

	const list< string > allEdges = {
			"0A5", "0AB", "0BA", "0BC", "0C", "1C0",
			"5A", "AB", "BC", "1CG",
			"5DA", "AD", "AE", "BE", "BF", "CF", "CG", "1GC",
			"5DH", "DE", "EF", "FG", "1GL",
			"5HD", "DH", "DI", "EI", "EJ", "FJ", "FK", "GK", "GL", "1L",
			"5H4", "HI", "IJ", "JK", "KL", "2L1",
			"H4", "HM", "IM", "IN", "JN", "JO", "KO", "KP", "LP", "2LP",
			"4MH", "MN", "NO", "OP", "2PL",
			"4MQ", "MQ", "NQ", "NR", "OR", "OS", "PS", "2PS",
			"4QM", "QR", "RS", "2S",
			"4Q3", "3Q", "3RQ", "3RS", "3SR", "3S2"
	};
};

