#pragma once
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define DISPLAY_WIDHT	1642
#define DISPLAY_HEIGHT	1000



class allegroInit
{
public:
	allegroInit();
	void initializer();
	ALLEGRO_DISPLAY * getDisplay() { return display; }
	bool getInitializationError();
	~allegroInit();
private:
	ALLEGRO_DISPLAY * display;
	ALLEGRO_EVENT_QUEUE * queue;
	ALLEGRO_EVENT event;
	ALLEGRO_FONT * font;
	bool initializationError;
};

