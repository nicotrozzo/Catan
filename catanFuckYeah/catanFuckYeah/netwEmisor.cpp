#include "netwEmisor.h"
#include <iostream>

using namespace std;

netwEmisor::netwEmisor(connector * establishedConnector_)
{
	establishedConnector = establishedConnector_;
}

void netwEmisor::sendPackage(networkingEventTypes header, string info)
{
	string messageToSend = header;	//siempre el primer byte del paquete sera el header
	if (variableLength(header))
	{
		messageToSend += info.length();
	}
	else if (header == BANK_TRADE)
	{
		messageToSend += info.length() - 1;
	}
	messageToSend += info;
	establishedConnector->sendMessage(messageToSend);
}

bool netwEmisor::variableLength(networkingEventTypes header)
{
	return ((header == NAME_IS) || ((header >= SETTLEMENT) && (header <= CITY)) || (header == ROBBER_CARDS));
}

void netwEmisor::
sendTrade(networkingEventTypes header, int ownResCount, string ownRes, int oppResCount, string oppRes)
{
	if (header == OFFER_TRADE)	//por las dudas
	{
		string messageToSend = header + ownResCount + oppResCount;
		messageToSend += ownRes + oppRes;
		establishedConnector->sendMessage(messageToSend);
	}
}
