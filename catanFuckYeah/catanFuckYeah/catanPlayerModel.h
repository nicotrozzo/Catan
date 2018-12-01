#pragma once
#include "EDASubject.h"
#include <iostream>
#define MAX_NAME_LENGTH 255

class cards
{
public:
	cards();
	unsigned char stone;
	unsigned char wood;
	unsigned char wheat;
	unsigned char wool;
	unsigned char brick;
	
};


class catanPlayerModel : public EDASubject
{
public:
	catanPlayerModel();
	unsigned char getAmountOfCards() { return (myCards.stone + myCards.wheat + myCards.wood + myCards.wool + myCards.brick); }
	unsigned char getVictoryPoints() { return victoryPoints; }
	void setVictoryPoints(unsigned char points) { victoryPoints = points; }
	void setName(string name);
	string getName() { return nameIs; }
	bool incResource (unsigned char amount, char resource);
	bool decResource(unsigned char amount, char resource);
	~catanPlayerModel();
private:
	cards myCards;
	unsigned char victoryPoints;
	//list <string> roads;					DEJAMOS COMENTADO PORQUE VAMOS A VER DE HACER GRAFO EN MODELO MAPA
	//list <string> city;
	//list <string> settlements;
	string nameIs;
};

