#include "netwEvGenerator.h"
#include "networkingEvents.h"
#include <iostream>
#include <string>

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
	else if(header == BANK_TRADE)
	{
		messageToSend += info.length() - 1;
	}
	messageToSend += info;
	establishedConnector->sendMessage(messageToSend);
}

bool netwEmisor::variableLength(networkingEventTypes header)
{
	return ( (header == NAME_IS) || ((header >= SETTLEMENT) && (header <= CITY)) || (header == ROBBER_CARDS) );
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

netwEventGenerator::netwEventGenerator(connector * connect)
{
	establishedConnector = connect;
}

genericEvent * netwEvGenerator::getEvent(void)
{
	genericEvent * ret = nullptr;
	string messageReceived;
	if (!establishedConnector->messagePresent())
	{
		if (establishedConnector->receiveMessage())
		{
			messageReceived = establishedConnector->getMessage();
			ret = getNetwEv(messageReceived);
		}
	}
	return ret;
}

genericEvent * netwEvGenerator::getNetwEv(string message)
{
	genericEvent * ret = nullptr;
	networkingEventTypes header = message[0];
	if (!emptyPackage(header))
	{
		switch (header)
		{
		case NAME_IS:
			ret = new nameIsPckg(message);
			break;
		case MAP_IS:
			ret = new mapIsPckg(message);
			break;
		case CIRCULAR_TOKENS:
			ret = new circTokensPckg(message);
			break;
		case OFFER_TRADE:
			ret = new offerTradePckg(message);
			break;
		case BANK_TRADE:
			ret = new bankTradePckg(message);
			break;
		case DICES_ARE:
			ret = new dicesArePckg(message);
			break;
		case ROBBER_CARDS:
			ret = new robberCardsPckg(message);
			break;
		case ROBBER_MOVE:
			ret = new robberMovePckg(message);
			break;
		case SETTLEMENT: case ROAD: case CITY:
			ret = new buildPckg(message);
			break;
		}
	}
	else
	{
		ret = new networkingEv(header);
	}
	if (static_cast<networkingEv *>(ret)->getError())
	{
		delete ret;
		ret = new outEv("Networking error: wrong package or header");

	}
	return ret;
}

bool netwEvGenerator::emptyPackage(networkingEventTypes header)
{
	return ((header == ACK) || (header == NAME) || (header == PLAY_WITH_DEV) || (header == YOU_START) || (header == I_START) || (header == PASS) || (header >= YES));
}