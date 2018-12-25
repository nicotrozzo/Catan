#pragma once
#include "inputEventGenerator.h"
#define FPS 1/50.0


inputEventGenerator::inputEventGenerator(ALLEGRO_DISPLAY * disp) : allegroQueue(nullptr)
{
	bool error = true;
	if (al_install_mouse())
	{
		if (al_install_keyboard())
		{
			allegroQueue = al_create_event_queue();
			if (allegroQueue != NULL)
			{
				timer = al_create_timer(FPS);
				if (timer != NULL)
				{
					error = false;
					al_start_timer(timer);
					al_register_event_source(allegroQueue, al_get_mouse_event_source());
					al_register_event_source(allegroQueue, al_get_keyboard_event_source());
					al_register_event_source(allegroQueue, al_get_timer_event_source(timer));
					al_register_event_source(allegroQueue, al_get_display_event_source(disp));
				}
				else
				{
					al_destroy_event_queue(allegroQueue);
				}
			}
		}
	}
	if (error)
	{
		lastEvent = new closeDisplayEv;
	}
}

genericEvent* inputEventGenerator::getEvent()
{
	genericEvent* ret = nullptr;
	bool empty = false;
	if (lastEvent != nullptr)
	{
		ret = lastEvent;
		lastEvent = nullptr;
	}
	while((ret == nullptr) && !empty)
	{
		if (al_get_next_event(allegroQueue, &ev))
		{
			unsigned char caracter;		//para el evento de teclado
			switch (ev.type)
			{
			case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
				if (ev.mouse.button == 1)
				{
					ret = new mouseEvent({ static_cast<float>(ev.mouse.x), static_cast<float>(ev.mouse.y) });
				}
				break;
			case ALLEGRO_EVENT_KEY_UP:
				caracter = allegroToAscii(ev.keyboard.keycode);
				if (caracter)
				{
					ret = new keyboardEvent(caracter);
				}
				break;
			case ALLEGRO_EVENT_TIMER:
				ret = new timerEv;
				break;
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				ret = new closeDisplayEv;
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

inputEventGenerator::~inputEventGenerator()
{
	if (allegroQueue != NULL)
	{
		al_destroy_event_queue(allegroQueue);
	}
	if (timer != NULL)
	{
		al_destroy_timer(timer);
	}
	if (lastEvent != nullptr)
	{
		delete lastEvent;
	}
}

/*Devuelve el ascii si es un numero o letra, 0 sino (solo se toman en cuenta numeros y letras)*/
char inputEventGenerator::allegroToAscii(int keyEv)
{
	char ret;
	if ((keyEv >= ALLEGRO_KEY_A) && (keyEv <= ALLEGRO_KEY_Z))
	{
		ret = 'A' + keyEv - ALLEGRO_KEY_A;
	}
	else if ((keyEv >= ALLEGRO_KEY_0) && (keyEv <= ALLEGRO_KEY_9))
	{
		ret = '0' + keyEv - ALLEGRO_KEY_0;
	}
	else if (keyEv == ALLEGRO_KEY_ENTER)
	{
		ret = '\n';
	}
	else
	{
		ret = 0;
	}
	return ret;
}
