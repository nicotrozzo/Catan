#pragma once
#include "EDASubject.h"
#include <map>
#include "gameDefines.h"
#include <array>
#include <vector>
#include <ctime>

typedef struct
{
	unsigned char circularToken;
	unsigned char hexResource;
}hexagon;

typedef struct
{
	unsigned char letter;
	unsigned char hexResource;
}pepe;

typedef struct 
{
	unsigned char res;
	unsigned char resCount;
}resource_t;


class oceanPiece
{
public:
	bool hasOnePort();
	void setResource(unsigned char resource_);
	resourceType getResource();
private:
	resourceType resource;
	bool hasTwoPorts;
};

class catanMapModel : public EDASubject
{
public:
	catanMapModel();
	unsigned char getRobberPos() { return robberPos; }
	void setRobberPos(unsigned char robberPos_) { robberPos = robberPos_; }
	string getMap();
	string getCircularTokens();
	bool setMap(string map_);						//EL MODELO ES MODIFICADO
													//bool setCircularTokens(string circTokens);	//EL MODELO ES MODIFICADO
	bool buildRoad(string edge, char player);		//EL MODELO ES MODIFICADO
	bool buildSettlement(string edge, char player);	//EL MODELO ES MODIFICADO
	bool buildCity(string vertex, char player);		//EL MODELO ES MODIFICADO				
	list<string> getP1BuiltVertexes();	//devuelve todos los vertices ocupados por el jugador, tanto settlements como cities
	list<string> getP1Settlements();
	list<string> getP1Cities();			//devuelve todos los cities contruidos por el jugador 1
	list<string> getP2BuiltVertexes();
	list<string> getP2Settlements();
	list<string> getP2Cities();
	list<string> getP1Roads();
	list<string> getP2Roads();
	map<resourceType, unsigned char> getBankTradeCosts(unsigned char player);	//Devuelve un diccionario con el costo (2, 3 o 4) de cada recurso para el jugador pedido
	bool checkAvailableRoad(string edge, char player);	//devuelve true si el jugador indicado puede construir un camino en ese lado
	bool checkAvailableSettlement(string vertex, char player);	//devuelve true si el vertice seleccionado es valido para la construccion de un settlementdeu
	bool checkAvailableCity(string vertex, char player);	//devuelve true si el vertice seleccionado es valido para la construccion de una ciudad
	list<pepe> getSelectedHex(unsigned int diceValue);
	~catanMapModel();
private:
	unsigned char robberPos;
	array <oceanPiece, NUMBER_OF_OCEAN_PIECES> oceanPieces;
	array <hexagon, HEX_COUNT> hexagons;
	list <string> hiddenRoads;		//caminos que son contiguos a un vertice ocupado, pero que no estan ocupados
	list <string> p1SimpleRoads;	//ejes construidos contiguos a un vertice ocupado por el jugador 1
	list <string> p1LongRoads;		//ejes construidos, a una distancia mayor a 1 de un vertice ocupado por el jugador 1
	list <string> p1UsedVertexList;	//cuando un settlement se transforma en city sigue estando en esta lista	
	list <string> p1Cities;
	list <string> p2SimpleRoads;	//ejes construidos contiguos a un vertice ocupado por el jugador 2
	list <string> p2LongRoads;		//ejes construidos, a una distancia mayor a 1 de un vertice ocupado por el jugador 2
	list <string> p2UsedVertexList;	//cuando un settlement se transforma en city sigue estando en esta lista	
	list <string> p2Cities;
	/*Metodos para chequeo de construcciones*/
	bool adjacentToLongRoad(string vertex, char player);
	bool adjacentToHiddenRoad(string vertex);
	bool adjacentToSimpleRoad(string vertex);
	bool vertexAdjacentToRoad(string vertex, string road);
	bool adjacentRoads(string road1, string road2);
	bool adjacentToOwnBuilding(string edge, char player);
	bool adjacentToOwnRoad(string edge, char player);
	bool freeEdge(string edge);
	bool existingVertex(string vertex);
	bool existingEdge(string edge);
	/*Metodos para buscar vertices con puerto*/
	string greater2CharVertex(unsigned int pieceNum);
	string less2CharVertex(unsigned int pieceNum);
	string middleCharVertex(string vertex);
	char thirdLetter(string vertex);

	resourceType connectsToPort(string edge);

	list< string > allVertexes = {
		"0A", "0B", "01C",
		"05A", "0AB", "0BC", "1C",
		"5AD", "ABE", "BCF", "1CG",
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

	list< string > allEdges = {
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

