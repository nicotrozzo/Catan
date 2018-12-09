#pragma once

#include <queue>
#include <list>
#include <allegro5/allegro.h>
#include "bossFSMEvents.h"

enum implInputEvent : inputEventTypes {INP_MOUSE_EVENT, INP_KEYBOARD_EVENT};

typedef struct
{
	float x;
	float y;
}point;

class mouseEvent : public inputEv 
{
public:
	mouseEvent(point p) : coords(p) {}
	inputEventTypes getInputEvType() { return MOUSE_EVENT; }
	point getClickCoords() { return coords; }
private:
	//guarda coordenadas del click
	//guarda coordenadas del mouse en caso opcional
	point coords;
};


class keyboardEvent : public inputEv
{
public:
	keyboardEvent(char letterPressed) { key = letterPressed; }
	inputEventTypes getInputEvType() { return KEYBOARD_EVENT; }
	char getKey() { return key; }
private:
	//guarda tecla apretada
	char key;
};


class inputEventGenerator : public eventGenerator
{
public:
	inputEventGenerator(ALLEGRO_DISPLAY * display);
	genericEvent * getEvent(void);
	~inputEventGenerator();
private:
	//queue<genericEvent*> eventQueue;
	genericEvent * lastEvent;
	ALLEGRO_EVENT_QUEUE * allegroQueue;
	ALLEGRO_EVENT ev;
	ALLEGRO_TIMER * timer;
	char allegroToAscii(int keyEv);
};

