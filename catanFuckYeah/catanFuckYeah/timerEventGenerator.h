#pragma once
#include "eventHandling.h"
#include <allegro5/allegro.h>

class timerEventGenerator : public eventGenerator
{
public:
	timerEventGenerator(double speed_secs);
	void startTimer();
	void stopTimer();
	genericEvent * getEvent();
	~timerEventGenerator();
private:
	ALLEGRO_EVENT_QUEUE * queue;
	ALLEGRO_TIMER * timer;
	ALLEGRO_EVENT ev;
	genericEvent * lastEvent;
	bool timerStarted;
};