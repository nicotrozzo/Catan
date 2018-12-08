#pragma once
#include "inputEventGenerator.h"



inputEventGenerator::inputEventGenerator() : allegroQueue(nullptr)
{
	bool error = true;
	allegroQueue = al_create_event_queue();
	if (allegroQueue != NULL)
	{
		al_register_event_source(allegroQueue, al_get_mouse_event_source());
		//blabla seguir
	}
	if (error)
	{
		eventQueue.empty();
		eventQueue.push(new closeDisplayEv);	//si hay un error en las inicializaciones de allegro se cierra todo
	}
}

genericEvent* inputEventGenerator::getEvent()
{
	genericEvent* ret = nullptr;
	al_register_event_source(allegroQueue, al_get_mouse_event_source());
	al_register_event_source(allegroQueue, al_get_keyboard_event_source());
	al_get_next_event(allegroQueue, &ev);
	switch (ev.type)
	{
	case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
		break;
	case ALLEGRO_EVENT_KEY_CHAR:
		break;
	}
}
