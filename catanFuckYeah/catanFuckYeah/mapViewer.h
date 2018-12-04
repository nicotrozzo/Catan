#pragma once
#include "catanMapModel.h"
#include "allegroInit.h"
#include "observer.h"
#include <allegro5/allegro_color.h>
#include <string>
#include "gameCoords.h"


class mapViewer : public observer
{
public:
	mapViewer(catanMapModel myMap);
	void update();
	~mapViewer();
private:
	bool initError;
	catanMapModel myMap;
	ALLEGRO_BITMAP * robberBitmap;
	ALLEGRO_BITMAP * settlement1Bitmap;
	ALLEGRO_BITMAP * settlement2Bitmap;
	ALLEGRO_BITMAP * road1Bitmap;
	ALLEGRO_BITMAP * road2Bitmap;
	ALLEGRO_BITMAP * city1Bitmap;
	ALLEGRO_BITMAP * city2Bitmap;
	void viewHex();
	void viewTokens();
	void viewBuildings();
	void viewRobber();
	void viewBankTrade();			//no se donde hacer tema trades
};

