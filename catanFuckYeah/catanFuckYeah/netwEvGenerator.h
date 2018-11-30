#pragma once
#include "eventHandling.h"
#include "networkingEvents.h"
#include "connector.h"
//connector
//emitir eventos de networking,  

class  netwEmisor
{
public:
	netwEmisor(connector * );
	void sendPackage(networkingEventTypes header, string info = "");
private:
	connector * establishedConnector;
	bool variableLength(networkingEventTypes header);
	void sendTrade(networkingEventTypes header, int ownResCount, string ownRes, int oppResCount, string oppRes);
};

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

netwEventGenerator::netwEventGenerator(connector *establishedConnector_)
{
	establishedConnector = establishedConnector_;
}

genericEvent* netwEventGenerator::getEvent()
{
	establishedConnector->receive()

}



