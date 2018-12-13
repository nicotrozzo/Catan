#pragma once
#include "eventHandling.h"
#pragma once
#include "networkingEvents.h"
#include "connector.h"

class netwEventGenerator : public eventGenerator
{
public:
	netwEventGenerator();
	netwEventGenerator(connector *);
	void setConnector(connector *);
	genericEvent * getEvent();
private:
	connector * establishedConnector;
	genericEvent * getNetwEv(string message,networkingEventTypes header);
	bool emptyPackage(networkingEventTypes header);
	string parseMessage(unsigned char * buf, size_t len,networkingEventTypes & header);
};	



