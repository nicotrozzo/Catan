#pragma once
#include "catanGameModel.h"
#include "allegroInit.h"
#include "observer.h"
#include "gameCoords.h"


class gameModelViewer : public observer
{
public:
	gameModelViewer(catanGameModel *myGame);
	void update();
	~gameModelViewer();
private:
	catanGameModel * myGame;
	ALLEGRO_BITMAP * diceValue1;
	ALLEGRO_BITMAP * diceValue2;
	ALLEGRO_BITMAP * diceValue3;
	ALLEGRO_BITMAP * diceValue4;
	ALLEGRO_BITMAP * diceValue5;
	ALLEGRO_BITMAP * diceValue6;
	void viewDices();
	bool initOk;
};

