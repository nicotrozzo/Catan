#pragma once
#include "inputEventGenerator.h"



inputEventGenerator::inputEventGenerator() : allegroQueue(nullptr)
{
	bool error = true;
	if (al_install_mouse())
	{
		if (al_install_keyboard())
		{
			allegroQueue = al_create_event_queue();
			if (allegroQueue != NULL)
			{
				al_register_event_source(allegroQueue, al_get_mouse_event_source());
				al_register_event_source(allegroQueue, al_get_keyboard_event_source());
			}
		}
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
	bool empty = false;
	while((ret == nullptr) && !empty)
	{
		if (al_get_next_event(allegroQueue, &ev))
		{
			switch (ev.type)
			{
			case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
				if (ev.mouse.button == 1)
				{
					ret = new mouseEvent({ static_cast<float>(ev.mouse.x), static_cast<float>(ev.mouse.y) });
				}
				break;
			case ALLEGRO_EVENT_KEY_UP:
				unsigned char caracter = allegroToAscii(ev.keyboard.keycode);
				if (caracter)
				{
					ret = new keyboardEvent(caracter);
				}
				
				break;
			}
		}
		else
		{
			empty = true;
		}
	}
	return ret;
}
