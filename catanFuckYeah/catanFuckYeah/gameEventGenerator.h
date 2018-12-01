#pragma once
#include "eventHandling.h"
#include "catanGameModel.h"



class gameEventGenerator : public eventGenerator
{
public:
	gameEventGenerator();
	genericEvent * getEvent();
	void playerTrade(unsigned char player, string offer);	
	~gameEventGenerator();
private:
	catanGameModel game;
	genericEvent * ev;		//cuidado, elimiar el evento una vez que se lo agarra
};

