#pragma once
#include "connector.h"
#include "bossFSMEvents.h"

class netwEmisor
{
public:
	netwEmisor(connector *);
	void sendPackage(networkingEventTypes header, string info = "");
	void sendTrade(networkingEventTypes header, int ownResCount, string ownRes, int oppResCount, string oppRes);
private:
	connector * establishedConnector;
	char messageToSend[512];
	bool variableLength(networkingEventTypes header);
};
