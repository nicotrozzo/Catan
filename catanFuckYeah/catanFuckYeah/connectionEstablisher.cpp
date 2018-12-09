#include "connectionEstablisher.h"
#include "Client.h"
#include "Server.h"
#include "bossFSMEvents.h"
#include <allegro5/allegro.h>
#include <cstdlib>
#include <ctime>

#define IP_STR "25.67.43.3"

connectionEstablisher::connectionEstablisher() : host(IP_STR)
{
	srand(time(NULL));
	topEvent = nullptr;
	if ((timer = al_create_timer((rand() % 3000 + 2000) / 1000.0)) != NULL) //crea un timer con un evento en un tiempo aleatorio entre 2000 y 5000ms
	{
		if ((queue = al_create_event_queue()) != NULL)
		{
			al_register_event_source(queue, al_get_timer_event_source(timer));
		}
		else
		{
			al_destroy_timer(timer);
			topEvent = new outEv("Couldn't create allegro event queue");
		}
	}
	else
	{
		topEvent = new outEv("Couldn't create allegro timer");
	}
}

void connectionEstablisher::startConnecting()
{
	if (topEvent == nullptr)		//si no hubo un error en la inicializacion
	{
		clientToHear = new client;
		clientToHear->startConnection(host.c_str());
		if (clientToHear->isConnected())
		{
			topEvent = new doneEv;
		}
		currentConnector = clientToHear;
		al_start_timer(timer);
	}
}

genericEvent * connectionEstablisher::getEvent()
{
	if(topEvent == nullptr)	
	{
		if (currentConnector->getType() == CLIENT)
		{
			if (!al_is_event_queue_empty(queue))
			{
				ALLEGRO_EVENT ret_event;
				al_get_next_event(queue, &ret_event);
				if (ret_event.type == ALLEGRO_EVENT_TIMER)
				{
					changeConnector();		//pasa de escuchar un client a un server
				}
			}
		}
		genericEvent* ret = nullptr;
		if (!currentConnector->isConnected())	
		{
			ret = getConnectionEv();
		}
		return ret;
	}
	else if (topEvent->getType() == DONE_EV)	//si entra aca significa que se conecto en el primer intento, o que se siguio llamando despues de emitir el DONE_EV
	{
		genericEvent* temp = topEvent;
		topEvent = nullptr;
		return temp;
	}
	else
	{
		return topEvent;		//si hubo error devuelve el outEv
	}
}

/*Pregunta al connector si esta conectado*/
genericEvent *connectionEstablisher::getConnectionEv()
{
	genericEvent *ret = nullptr;
	if (currentConnector->getType() == CLIENT)
	{
		clientToHear->startConnection(host.c_str());
		if (clientToHear->isConnected())
		{
			ret = new doneEv;
		}
	}
	else
	{
		serverToHear->startConnection();
		if (serverToHear->isConnected())
		{
			ret = new doneEv;
		}
	}
	return static_cast<genericEvent *>(ret);
}


void connectionEstablisher::changeConnector()
{
	al_destroy_event_queue(queue);
	al_destroy_timer(timer);
	serverToHear = new server;
	currentConnector = static_cast<connector *>(serverToHear);
	delete clientToHear;
}

void connectionEstablisher::stopConnection()
{
	delete currentConnector;	//si deciden parar la conexion, hay que destruir al connector que estaba escuchando
}

connector *connectionEstablisher::getConnector()
{
	if (currentConnector->isConnected())
	{
		return currentConnector;
	}
	else
	{
		return nullptr;
	}
}
connectionEstablisher::~connectionEstablisher()
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
