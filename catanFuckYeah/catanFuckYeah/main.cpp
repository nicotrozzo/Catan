#include <iostream>
#include <allegro5/allegro.h>
#include "bossFSM.h"
#include "inputEventGenerator.h"
#include "timerEventGenerator.h"
#include "quitButtonController.h"
#include "connectionEstablisher.h"
#include "handShakingFSM.h"
#include "netwEvGenerator.h"

#define TIMEOUT_SECS 150
#define DISPLAY_WIDHT	1642
#define DISPLAY_HEIGHT	1000

int main(int argc,char * argv[])
{
	void * info = initFrontEnd();
	if (info != nullptr)
	{
		string name;
		inputEventGenerator inputEvGen(static_cast<ALLEGRO_DISPLAY *>(info));	//mouse, teclado y refresh de pantalla
		timerEventGenerator timeout(TIMEOUT_SECS);
		quitButtonController quitButton;
		connectionEstablisher establisher;
		netwEventGenerator netwReceiver;
		mainEventGenerator eventGen;	//generador de eventos de TODO el programa
		eventGen.attach(&inputEvGen);	//registro fuente de eventos
		eventGen.attach(&timeout);
		eventGen.attach(&quitButton);
		eventGen.attach(&netwReceiver);
		bossFSM fsm(&quitButton,&establisher,&eventGen,&netwReceiver,name);
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
		deleteFrontEnd(info);
	}
	else
	{
		cout << "No se pudo inicializar correctamente el juego" << endl;
	}
	return 0;
}

void * initFrontEnd()
{
	void * ret = nullptr;
	srand(time(NULL));
	if (al_init())
	{
		ALLEGRO_DISPLAY * display = al_create_display(DISPLAY_WIDHT,DISPLAY_HEIGHT);
		if (display != NULL)
		{
			ret = display;
		}
	}
	return ret;
}

void deleteFrontEnd(void * display)
{
	if (display != nullptr)
	{
		al_destroy_display(static_cast<ALLEGRO_DISPLAY *>(display))
	}
}