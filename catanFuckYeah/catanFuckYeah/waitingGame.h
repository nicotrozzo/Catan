#pragma once
#include "graphicator.h"
#include <allegro5/allegro.h>

class waitingGame : public graphicator
{
public:
	waitingGame(ALLEGRO_DISPLAY * disp);

private:
	ALLEGRO_DISPLAY * display;
};