#include "netwEmisor.h"
#include <iostream>

using namespace std;

netwEmisor::netwEmisor(connector * establishedConnector_)
{
	establishedConnector = establishedConnector_;
}

void netwEmisor::sendPackage(networkingEventTypes header, string info)
{
	messageToSend[0] = static_cast<char>(header);	//siempre el primer byte del paquete sera el header
	int nwritten = 1;
	if (variableLength(header))
	{
		messageToSend[nwritten] = info.length();
		nwritten++;
		strcpy(&messageToSend[nwritten], info.c_str());
	}
	else if (header == BANK_TRADE)
	{
		messageToSend[nwritten] = info.length() - 1;
		nwritten++;
	}
	strcpy(&messageToSend[nwritten], info.c_str());
	if (header == CIRCULAR_TOKENS)	//hay que cambiar el 7 por un \0
	{
		size_t cero = info.find(7);
		messageToSend[cero+1] = '\0';
	}
	establishedConnector->sendMessage(messageToSend,info.length());
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
		string messageToSend;
		messageToSend += header;
		messageToSend += ownResCount;
		messageToSend += oppResCount;
		messageToSend += ownRes + oppRes;
		establishedConnector->sendMessage(messageToSend.c_str(),messageToSend.length());
	}
}
