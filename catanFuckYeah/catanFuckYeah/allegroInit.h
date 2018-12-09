#pragma once
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>




class allegroInit
{
public:
	allegroInit();
	void initializer();
	ALLEGRO_DISPLAY * getDisplay() { return display; }
	bool getInitializationOk();
	~allegroInit();
private:
	ALLEGRO_DISPLAY * display;
	ALLEGRO_EVENT_QUEUE * queue;
	ALLEGRO_EVENT event;
	ALLEGRO_FONT * font;
	bool initializationOk;
};
