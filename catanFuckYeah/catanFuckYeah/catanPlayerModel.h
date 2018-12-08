#pragma once
#include "EDASubject.h"
#include "gameDefines.h"

typedef struct 
{
	unsigned char ore;
	unsigned char wood;
	unsigned char wheat;
	unsigned char wool;
	unsigned char brick;
	unsigned char totalCardsCount() { return ore + wood + wheat + wool + brick; }
}cards;


class catanPlayerModel : public EDASubject
{
public:
	catanPlayerModel();
	unsigned char getAmountOfCards();
	cards getCards();
	unsigned char getVictoryPoints();
	void setVictoryPoints(unsigned char points);
	void setName(string name);
	void setLongestRoad(unsigned char longRoad);
	unsigned char getLongestRoad();
	string getName();
	unsigned char getPlayerNumber();
	bool incResource(unsigned char resource);
	bool incResource(unsigned char resource, unsigned char count);
	bool decResource(unsigned char resource);
	bool decResource(unsigned char resource, unsigned char count);
	void notify();
	~catanPlayerModel();
private:
	cards myCards;
	unsigned char victoryPoints;
	unsigned char playerNumber;
	unsigned char longestRoad;
	string NameIs;
};
