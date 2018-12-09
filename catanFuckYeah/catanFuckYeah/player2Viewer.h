#pragma once
#include "catanPlayerModel.h"
#include "observer.h"
#include <allegro5/allegro_color.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>


class player2Viewer : public observer
{
public:
	player2Viewer(catanPlayerModel * player2);
	void update();
	bool getInitOk();
	~player2Viewer();
private:
	catanPlayerModel * player;
	ALLEGRO_FONT * fontForVictoryPoints;
	ALLEGRO_FONT * fontForName;
	ALLEGRO_FONT * fontForAmountOfCards;
	ALLEGRO_FONT * fontForLongestRoad;
	void viewNameIs();
	void viewLongestRoad();
	void viewAmountOfCards();
	void viewVictoryPoints();
	bool initOk;
};


