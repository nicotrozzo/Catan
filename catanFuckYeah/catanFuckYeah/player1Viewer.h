#pragma once
#include "catanPlayerModel.h"
#include "allegroInit.h"

class player1Viewer
{
public:
	player1Viewer();
	bool viewVictoryPoints();
	~player1Viewer();
private:
	ALLEGRO_BITMAP * victoryPoints;
	catanPlayerModel player1;
};

