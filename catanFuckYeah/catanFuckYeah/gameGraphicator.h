#pragma once
#include "graphicator.h"
#include <allegro5/allegro.h>

class gameGraphicator : public graphicator
{
public:
	void refresh() { al_flip_display(); }
	~gameGraphicator() {};
};

