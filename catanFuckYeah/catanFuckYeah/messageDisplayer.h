#pragma once
#include "graphicator.h"
#include <iostream>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#define PI 3.14159265359

class messageDisplayer : public graphicator
{
public:
	messageDisplayer();
	void refresh();
	bool getInitOk();
	void setMessage(std::string message);
	~messageDisplayer();
private:
	bool initOk;
	ALLEGRO_BITMAP * messageShowBitmap;
	ALLEGRO_BITMAP * refreshBitmap;
	ALLEGRO_FONT * fontForMessageShow;
	void showMessage();
	void showRefresh();
	std::string message;
	int tickCountForRefresh;
	float angle;
};

