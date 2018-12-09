#pragma once
#include "graphicator.h"
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#define PI 3.14159265359


class waitingGame : public graphicator
{
public:
	waitingGame();
	void refresh();
	bool getInitOk();
	void setMessage(std::string message);
private:
	ALLEGRO_BITMAP * bitmapArray[4];
	ALLEGRO_BITMAP * refreshBitmap;
	ALLEGRO_FONT * fontForMessage;
	std::string message;
	void showMessage();
	void showWallpapers();
	void showRefresh();
	int tickCountForWallpaper;
	int tickCountForRefresh;
	int i;
	float angle;
	bool initOk;
};

