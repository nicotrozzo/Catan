#pragma once

#include <queue>
#include <list>
#include <allegro5/allegro.h>
#include "bossFSMEvents.h"

enum implInputEvent : inputEventTypes {MOUSE_EVENT, KEYBOARD_EVENT};

class mouseEvent : public inputEv 
{
	//guarda coordenadas del click
	//guarda coordenadas del mouse en caso opcional
public:
	inputEventTypes getInputEvType() { return MOUSE_EVENT; }
};

class keyboardEvent : public inputEv
{
	//guarda tecla apretada
public:
	inputEventTypes getInputEvType() { return KEYBOARD_EVENT; }
};

class inputEventGenerator : public eventGenerator
{
public:
	inputEventGenerator();
	genericEvent * getEvent(void);

private:
	queue<inputEv*> eventQueue;
	ALLEGRO_EVENT_QUEUE * allegroQueue;
};

inputEventGenerator::inputEventGenerator() : allegroQueue(nullptr)
{
	bool error = true;
	allegroQueue = al_create_event_queue();
	if (allegroQueue != NULL)
	{
		al_register_event_source(allegroQueue, al_get_mouse_event_source());
		
	}
}