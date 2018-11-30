#pragma once
#include "eventHandling.h"
#include "networkingEvents.h"
#include "connector.h"

class netwEventGenerator : public eventGenerator
{
public:
	netwEventGenerator(connector *);
	genericEvent * getEvent();
private:
	connector * establishedConnector;
	genericEvent * getNetwEv(string message);
	bool emptyPackage(networkingEventTypes header);
};	



