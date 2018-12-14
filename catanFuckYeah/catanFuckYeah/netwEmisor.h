#pragma once
#include "connector.h"
#include "bossFSMEvents.h"

class netwEmisor
{
public:
	netwEmisor();
	netwEmisor(connector *);
	void setConnector(connector *);
	void sendPackage(networkingEventTypes header, string info = "");
	void sendTrade(networkingEventTypes header, unsigned char ownResCount, string ownRes, unsigned char oppResCount, string oppRes);
private:
	connector * establishedConnector;
	unsigned char messageToSend[512];
	bool variableLength(networkingEventTypes header);
};
