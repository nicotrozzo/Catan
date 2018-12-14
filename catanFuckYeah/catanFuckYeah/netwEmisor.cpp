#include "netwEmisor.h"
#include <iostream>
#include <string>

using namespace std;

netwEmisor::netwEmisor()
{
	establishedConnector = nullptr;
}

netwEmisor::netwEmisor(connector * establishedConnector_)
{
	establishedConnector = establishedConnector_;
}

void netwEmisor::setConnector(connector * con)
{
	if (establishedConnector == nullptr)
	{
		establishedConnector = con;
	}
}

void netwEmisor::sendPackage(networkingEventTypes header, string info)
{
	messageToSend[0] = static_cast<unsigned char>(header);	//siempre el primer byte del paquete sera el header
	int nwritten = 1;
	if (variableLength(header))
	{
		messageToSend[nwritten] = info.length();
		nwritten++;
	}
	else if (header == BANK_TRADE)
	{
		messageToSend[nwritten] = info.length() - 1;
		nwritten++;
	}
	if (info.length() > 0)
	{
		memcpy(&messageToSend[nwritten], info.c_str(), info.length());
		nwritten += info.length();
	}
	if (header == CIRCULAR_TOKENS)	//hay que cambiar el 7 por un \0
	{
		size_t cero = info.find(7);
		if (cero != string::npos)
		{
			messageToSend[cero + 1] = '\0';
		}
	}
	establishedConnector->sendMessage(messageToSend,nwritten);
}

bool netwEmisor::variableLength(networkingEventTypes header)
{
	return ((header == NAME_IS) || ((header >= SETTLEMENT) && (header <= CITY)) || (header == ROBBER_CARDS));
}

void netwEmisor::
sendTrade(networkingEventTypes header, unsigned char ownResCount, string ownRes, unsigned char oppResCount, string oppRes)
{
	if (header == OFFER_TRADE)	//por las dudas
	{
		messageToSend[0] = header;
		memcpy(&messageToSend[1], &ownResCount,1);
		memcpy(&messageToSend[2], &oppResCount,1);
		memcpy(&messageToSend[3], (ownRes + oppRes).c_str(), (ownRes + oppRes).length());
		establishedConnector->sendMessage(messageToSend,strlen(reinterpret_cast<char*>(messageToSend)));
	}
}
