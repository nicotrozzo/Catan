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
	ALLEGRO_BITMAP * dice1;
	ALLEGRO_BITMAP * dice2;
	ALLEGRO_BITMAP * dice3;
	ALLEGRO_BITMAP * dice4;
	ALLEGRO_BITMAP * dice5;
	ALLEGRO_BITMAP * dice6;
	void viewDices();
	bool initOk;
};

