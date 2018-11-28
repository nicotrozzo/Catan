#include <iostream>
#include "bossFSM.h"

#define FPS 1




int main(void)
{
	bossFSM fsm;
	//simpleEventGenerator s;	//generador de UN tipo de eventos
	mouseEventGenerator m;	//mouse
	timerEventGenerator refreshTimer(FPS);	//timer para refrescar pantalla
	//timerEventGenerator timeout(); ver en que momento crearlo
	keyboardEventGenerator k;	//keyboard 
	
	mainEventGenerator eventGen;	//generador de eventos de TODO el programa

	eventGen.attach(&a);	//registro fuente de eventos

	do
	{
		genericEvent * ev;
		ev = eventGen.getNextEvent();
		if (ev->getType != NO_EVENT)
		{
			fsm.cycle(ev);
		}
		delete ev;
	} while (!fsm.getEvent());
	delete fsm.getEvent();

	return 0;
}

/*
{} 
{}
{}
{}
*/
