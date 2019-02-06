#pragma once

#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "graphicator.h"


class startMenu : public graphicator
{
public:
	startMenu();
	void refresh();
	bool getInitOk();
	~startMenu();

private:
	bool initOk;
	ALLEGRO_BITMAP * menuBitmap;
	ALLEGRO_BITMAP *playBitmap;
	ALLEGRO_BITMAP *exitBitmap;
};

