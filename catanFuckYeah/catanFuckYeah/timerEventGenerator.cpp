#include "timerEventGenerator.h"
#include "bossFSMEvents.h"

timerEventGenerator::timerEventGenerator(double speed_secs)
{
	bool error = true;
	queue = al_create_event_queue();
	if (queue != NULL)
	{
		timer = al_create_timer(speed_secs);
		if (timer != NULL)
		{
			al_register_event_source(queue,al_get_timer_event_source(timer));
			al_start_timer(timer);
			error = false;
			timerStarted = false;
		}
		else
		{
			al_destroy_event_queue(queue);
		}
	}
	if (error)
	{
		lastEvent = new closeDisplayEv;
	}
}

void timerEventGenerator::startTimer()
{
	al_start_timer(timer);
	timerStarted = true;
}

void timerEventGenerator::stopTimer()
{
	al_stop_timer(timer);
	timerStarted = false;
}

genericEvent * timerEventGenerator::getEvent()
{
	genericEvent * ret = nullptr;
	if (timerStarted)
	{
		bool empty = false;
		while ((!empty) && (ret == nullptr))
		{
			if (al_get_next_event(queue, &ev))
			{
				ret = new timerEv(false);	//emite evento de timer en false para avisar que no es de refresh de pantalla
			}
		}
	}
	return ret;
}

timerEventGenerator::~timerEventGenerator()
{
	if (queue != NULL)
	{
		al_destroy_event_queue(queue);
	}
	if (timer != NULL)
	{
		al_destroy_timer(timer);
	}
}
