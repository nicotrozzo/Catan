#pragma once

#include <queue>
#include <list>
#include <allegro5/allegro.h>
#include "bossFSMEvents.h"

enum implInputEvent : inputEventTypes {MOUSE_EVENT, KEYBOARD_EVENT};

typedef struct
{
	float x;
	float y;
}point;

class mouseEvent : public inputEv 
{
	//guarda coordenadas del click
	//guarda coordenadas del mouse en caso opcional
public:
	mouseEvent(point p) : coords(p) {}
	inputEventTypes getInputEvType() { return MOUSE_EVENT; }
	point getClickCoords() { return coords; }
private:
	point coords;
};


class keyboardEvent : public inputEv
{
public:
	inputEventTypes getInputEvType() { return KEYBOARD_EVENT; }
	char getKey() { return key; }
private:
	//guarda tecla apretada
	char key;
};

class inputEventGenerator : public eventGenerator
{
public:
	inputEventGenerator();
	genericEvent * getEvent(void);

private:
	queue<genericEvent*> eventQueue;
	ALLEGRO_EVENT_QUEUE * allegroQueue;
};

