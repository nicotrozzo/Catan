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
	genericEvent * getNetwEv(string message);
	bool emptyPackage(networkingEventTypes header);
	string parseMessage(char * buf, size_t len);
};	



