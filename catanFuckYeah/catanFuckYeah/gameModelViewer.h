#pragma once
#include "catanGameModel.h"
#include "allegroInit.h"
#include "observer.h"
#include "gameCoords.h"
#include <allegro5/allegro_color.h>


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
	ALLEGRO_BITMAP * tradeMenuBitmap;
	ALLEGRO_FONT * fontForAmountOfCards;
	void viewDices();
	void viewTrade();
	void viewSelecteCards();
	bool initOk;
};

