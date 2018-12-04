#pragma once
#include "catanPlayerModel.h"
#include "allegroInit.h"
#include "observer.h"
#include <allegro5/allegro_color.h>
#include <string>


class player2Viewer
{
public:
	player2Viewer(catanPlayerModel * player2);
	void update();
	~player2Viewer();
private:
	catanPlayerModel* player;
	ALLEGRO_FONT * fontForVictoryPoints;
	ALLEGRO_FONT * fontForName;
	ALLEGRO_FONT * fontForAmountOfCards;
	void viewNameIs();
	void viewLongestRoad();
	void viewAmountOfCards();
	void viewVictoryPoints();
	bool initOk;
};

