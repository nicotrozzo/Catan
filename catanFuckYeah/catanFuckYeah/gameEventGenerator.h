#pragma once
#include "eventHandling.h"
#include "catanGameModel.h"

typedef enum { PLAYER_TRADE_EVENT, BANK_TRADE_EVENT, PASS, BUILD_EVENT } eventType; 
typedef enum { ROAD, SETTLEMENT, CITY } buidType;

class gameEventGenerator : public eventGenerator
{
public:
	gameEventGenerator();
	genericEvent * getEvent();
	~gameEventGenerator();
private:
	catanGameModel game;
	//genericEvent * ev;		//cuidado, elimiar el evento una vez que se lo agarra
	genericEvent * playerTrade(unsigned char player, string offer);
	genericEvent * buil();
};

class tradeEvent : public genericEvent
{
public:
	//tradeEvent(string currentResources_, string otherResources_) { currentResources = currentResources_; otherResources = otherResources_; }
	eventType getType() { return ; }
private:
	eventType evento;
}

class buildEvent : public genericEvent
{
public:
	eventType getType() { return BUILD_EVENT; }
	buildType getBuilding{ return building; }
private:
	buildType building;
};