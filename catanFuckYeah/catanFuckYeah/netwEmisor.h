#pragma once
#include "connector.h"
#include "bossFSMEvents.h"

class netwEmisor
{
public:
	netwEmisor(connector *);
	void sendPackage(networkingEventTypes header, string info = "");
private:
	connector * establishedConnector;
	bool variableLength(networkingEventTypes header);
	void sendTrade(networkingEventTypes header, int ownResCount, string ownRes, int oppResCount, string oppRes);
};
