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

}

timerEventGenerator::timerEventGenerator(double speed)
{
	//al_create_timer(speed);
}

genericEvent *timerEventGenerator::getEvent(void)
{

}
