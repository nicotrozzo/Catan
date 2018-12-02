#pragma once

#include <iostream>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define DISPLAY_WIDHT	1642
#define DISPLAY_HEIGHT	1000

using namespace std;

class point
{
public:
	point(unsigned int x, unsigned int y) : px(x), py(y) {}
	unsigned int getX() { return px; }
	unsigned int getY() { return py; }
private:
	unsigned int px;
	unsigned int py;
};


class rectangle
{
public:
	rectangle(point p, unsigned int h, unsigned int w) : myPoint(p), height(h), width(w) {}
	bool inRectangle(point p) { return (p.getX() >= myPoint.getX() && p.getX() <= (myPoint.getX() + width) && p.getY() >= myPoint.getY() && p.getY() <= (myPoint.getY() - width)); }
private:
	point myPoint;
	unsigned int height;
	unsigned int width;
};


class dibujator
{
public:
	dibujator();
	void menuInit();
	bool menuImageLoad();
	bool getInitializationError();
	~dibujator();

private:
	ALLEGRO_BITMAP * menuBitmap;
	ALLEGRO_BITMAP *playBitmap;
	ALLEGRO_BITMAP *exitBitmap;
	ALLEGRO_DISPLAY * display;
	ALLEGRO_EVENT_QUEUE * queue;
	ALLEGRO_EVENT event;
	ALLEGRO_FONT * font;
	bool initializationError;
};

