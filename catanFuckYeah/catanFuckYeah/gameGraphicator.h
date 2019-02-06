#pragma once
#include "graphicator.h"
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <stdio.h>


class gameGraphicator : public graphicator
{
public:
	gameGraphicator();
	void refresh();
	void setMessage(string message_);
	~gameGraphicator();
private:
	string message;
	bool initOk;
	ALLEGRO_BITMAP * backgroundBitmap;
	ALLEGRO_FONT * fontForMessages;
};

