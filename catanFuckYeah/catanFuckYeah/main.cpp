#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "bossFSM.h"
#include "inputEventGenerator.h"
#include "timerEventGenerator.h"
#include "quitButtonController.h"
#include "connectionEstablisher.h"
#include "handShakingFSM.h"
#include "netwEvGenerator.h"
#include "gameCoords.h"

#define TIMEOUT_SECS 150
#define IP_MIN_LENGTH 10

void deleteFrontEnd(void * display);
void * initFrontEnd();
bool parseCmdLine(int argc, char * argv[],string& IP, string& name);
bool checkIP(char* IP);


int main(int argc,char * argv[])
{
	void * info = initFrontEnd();
	if (info != nullptr)
	{
		string name, ip;
		if (parseCmdLine(argc,argv,ip, name))
		{		
			inputEventGenerator inputEvGen(static_cast<ALLEGRO_DISPLAY *>(info));	//mouse, teclado y refresh de pantalla
			timerEventGenerator timeout(TIMEOUT_SECS);
			quitButtonController quitButton;
			connectionEstablisher establisher(ip);
			netwEventGenerator netwReceiver;
			mainEventGenerator eventGen;	//generador de eventos de TODO el programa
			eventGen.attach(&inputEvGen);	//registro fuentes de eventos
			eventGen.attach(&timeout);
			eventGen.attach(&quitButton);
			eventGen.attach(&netwReceiver);
			bossFSM fsm(&quitButton, &establisher, &eventGen, &netwReceiver, name, &timeout);
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
			cout << ip.c_str() << endl;
		}
	}
	else
	{
		cout << "No se pudo inicializar correctamente el juego." << endl;
	}
	return 0;
}

/*Recibe los argumentos de linea de comando, los interpreta, y si son correctos carga el primer argumento en el string ip y el segundo en el nombre
Si no son correctos, deja un mensaje de error en IP
Devuelve true si los argumentos estan bien, false si no lo estan.*/
bool parseCmdLine(int argc, char * argv[], string& ip, string& name)
{
	bool ret = false;
	if (argc >= 2)
	{
		if (argc >= 3)
		{
			string tempName = argv[2];
			for (int i = 0; i < tempName.length(); i++)
			{
				if (isalpha(tempName[i]))
				{
					name += tempName[i];
				}
			}
		}
		else
		{
			name = "Player1";
		}
		if (checkIP(argv[1]))
		{
			ret = true;
			ip = argv[1];
		}
		else
		{
			ip = "IP incorrecta";
		}
	}
	else
	{
		ip = "No hay suficientes argumentos de linea de comando.\n Ingrese como primer argumento la ip de su contrincante y como segundo su nombre (opcional).";
	}
	return ret;
}

bool checkIP(char * ip)
{
	bool ok = false, error = false;
	int i = 0, dots = 0, numbers = 0;
	if (strlen(ip) >= IP_MIN_LENGTH)
	{
		while (!error && (dots < 3))
		{
			for (int numbers = 0; numbers < 2; numbers++, i++)
			{
				if (!((ip[i] >= '0') && (ip[i] <= '9')))
				{
					error = true;
				}
			}
			if (ip[i++] != '.')
			{
				error = true;
			}
			else
			{
				dots++;
			}
		}
		if (dots == 3)
		{
			while (ip[i] != '\0')
			{
				if (!((ip[i] >= '0') && (ip[i] <= '9')))
				{
					error = true;
				}
				i++;
			}
			if (!error)
			{
				ok = true;
			}
		}
	}
	return ok;
}



void * initFrontEnd()
{
	void * ret = nullptr;
	srand(time(NULL));
	if (al_init())
	{
		if (al_init_font_addon())
		{
			if (al_init_ttf_addon())
			{
				if (al_init_image_addon())
				{
					ALLEGRO_DISPLAY * display = al_create_display(MY_DIS_W, MY_DIS_H);
					if (display != NULL)
					{
						ret = display;
					}
				}
			}
		}
	}
	return ret;
}

void deleteFrontEnd(void * display)
{
	if (display != nullptr)
	{
		al_destroy_display(static_cast<ALLEGRO_DISPLAY *>(display));
	}
}