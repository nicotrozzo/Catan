#pragma once

#include "connector.h"
#include "eventHandling.h"
#include <allegro5/allegro.h>
#include "Client.h"
#include "Server.h"

class connectionEstablisher : public eventGenerator
{
public:
	connectionEstablisher();	
	void startConnecting();
	virtual genericEvent * getEvent();
	connector * getConnector();					//devuelve un connector (client o server) si se pudo conectar, sino nullptr 
	void stopConnection();				//en caso que se quiera cortar la conexion
	~connectionEstablisher();

private:
	connector * currentConnector;
	client* clientToHear;
	server* serverToHear;
	const string host;
	ALLEGRO_TIMER * timer;
	ALLEGRO_EVENT_QUEUE * queue;
	void changeConnector();						//cambia de client a server
	bool connectionEstablished();				//devuelve true si se establecio la conexion
	genericEvent *getConnectionEv();			
	genericEvent * topEvent;
};

