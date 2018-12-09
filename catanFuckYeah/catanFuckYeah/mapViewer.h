#pragma once
#include "catanMapModel.h"
#include "observer.h"
#include <allegro5/allegro_color.h>
#include <string>
#include <map>


class mapViewer : public observer
{
public:
	mapViewer(catanMapModel * myMap);
	void update();
	~mapViewer();
private:
	bool initOk;
	catanMapModel * myMap;
	ALLEGRO_BITMAP * montañas;
	ALLEGRO_BITMAP * colinas;
	ALLEGRO_BITMAP * pasto;
	ALLEGRO_BITMAP * campos;
	ALLEGRO_BITMAP * bosques;
	ALLEGRO_BITMAP * desierto;
	ALLEGRO_BITMAP * seaN;
	ALLEGRO_BITMAP * seaL;
	ALLEGRO_BITMAP * seaM;
	ALLEGRO_BITMAP * seaO;
	ALLEGRO_BITMAP * seaP;
	ALLEGRO_BITMAP * seaT;
	ALLEGRO_BITMAP * robberBitmap;
	ALLEGRO_BITMAP * settlement1Bitmap;
	ALLEGRO_BITMAP * settlement2Bitmap;
	ALLEGRO_BITMAP * road1Bitmap;
	ALLEGRO_BITMAP * road2Bitmap;
	ALLEGRO_BITMAP * city1Bitmap;
	ALLEGRO_BITMAP * city2Bitmap;
	ALLEGRO_BITMAP * wallpaperBitmap;
	ALLEGRO_BITMAP * tokens[10];
	ALLEGRO_FONT * fontForAmountOfBuildings;
	map<unsigned char, ALLEGRO_BITMAP*> oceanHex;
	map<unsigned char, ALLEGRO_BITMAP*> resourcesHex;
	void viewWallpaper();
	void viewHex();
	void viewTokens();
	void viewBuildings();
	void viewRobber();
	void viewPendingConstruction();
	void viewAmountOfBuildingsLeft();
};


