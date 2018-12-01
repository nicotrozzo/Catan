#pragma once
#include "EDASubject.h"
#include "gameDefines.h"

class cards
{
public:
	cards();
	unsigned char ore;
	unsigned char wood;
	unsigned char wheat;
	unsigned char wool;
	unsigned char brick;
	
};


class catanPlayerModel : public EDASubject
{
public:
	catanPlayerModel();
	unsigned char getAmountOfCards() { return (myCards.ore + myCards.wheat + myCards.wood + myCards.wool + myCards.brick); }
	cards getCards() { return myCards; }
	unsigned char getVictoryPoints() { return victoryPoints; }
	void setVictoryPoints(unsigned char points) { victoryPoints = points; }
	void setName(string name);
	string getName() { return nameIs; }
	unsigned char getPlayerNumber() { return playerNumber; }
	bool incResource (unsigned char amount, char resource);
	bool decResource(unsigned char amount, char resource);
	~catanPlayerModel();
private:
	cards myCards;
	unsigned char victoryPoints;
	unsigned char playerNumber;
	//list <string> roads;					DEJAMOS COMENTADO PORQUE VAMOS A VER DE HACER GRAFO EN MODELO MAPA
	//list <string> city;
	//list <string> settlements;
	string nameIs;
};

