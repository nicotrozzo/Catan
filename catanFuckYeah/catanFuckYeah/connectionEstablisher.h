#pragma once

#include "connector.h"
#include "eventHandling.h"
#include <allegro/allegro5.h>

class connectionEstablisher : public eventGenerator
{
public:
	connectionEstablisher(const char * host);	
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
	ALLEGRO_QUEUE * queue;
	void changeConnector();						//cambia de client a server
	bool connectionEstablished();				//devuelve true si se establecio la conexion
	genericEvent *getConnectionEv();			
	genericEvent * topEvent;
};

