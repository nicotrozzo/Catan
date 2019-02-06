#pragma once
#include "graphicator.h"
#include <string>
#include <allegro5/allegro.h>

using namespace std;

class gameGraphicator : public graphicator
{
public:
	gameGraphicator();
	void refresh();
	void setMessage(string message_);
	~gameGraphicator() {};
private:
	string message;
};

