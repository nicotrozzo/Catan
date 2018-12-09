#include <iostream>
#include <allegro5/allegro.h>
#include "bossFSM.h"
#include "inputEventGenerator.h"
#include "timerEventGenerator.h"
#include "quitButtonController.h"
#include "connectionEstablisher.h"

#define TIMEOUT_SECS 150

int main(int argc,char * argv[])
{
	if (initFrontEnd())
	{
		inputEventGenerator inputEvGen;	//mouse, teclado y refresh de pantalla
		timerEventGenerator timeout(TIMEOUT_SECS);
		quitButtonController quitButton;
		connectionEstablisher establisher;
		mainEventGenerator eventGen;	//generador de eventos de TODO el programa

		eventGen.attach(&inputEvGen);	//registro fuente de eventos
		eventGen.attach(&timeout);
		eventGen.attach(&quitButton);
		bossFSM fsm(&quitButton,&establisher,);
		do
		{
			genericEvent * ev;
			ev = eventGen.getNextEvent();
			if (ev != nullptr)
			{
				fsm.cycle(ev);
				delete ev;
			}
		} while (!fsm.getEvent());
		delete fsm.getEvent();
	}
	else
	{
		cout << "No se pudo inicializar correctamente el juego" << endl;
	}
	return 0;
}

bool initFrontEnd()
{
	return al_init();
	srand(time(NULL));
}