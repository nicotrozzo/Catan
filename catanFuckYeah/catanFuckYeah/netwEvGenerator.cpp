#include "netwEvGenerator.h"
#include "networkingEvents.h"
#include <iostream>
#include <string>

using namespace std;

netwEventGenerator::netwEventGenerator()
{
	establishedConnector = nullptr;
}

netwEventGenerator::netwEventGenerator(connector * connect)
{
	establishedConnector = connect;
}

genericEvent * netwEventGenerator::getEvent(void)
{
	genericEvent * ret = nullptr;
	if (establishedConnector != nullptr)
	{
		string messageReceived;
		if (!establishedConnector->messagePresent())
		{
			if (establishedConnector->receiveMessage())
			{
				messageReceived = parseMessage(establishedConnector->getMessage(), establishedConnector->getMessageLenght());
				ret = getNetwEv(messageReceived);
			}
		}
	}
	return ret;
}

void netwEventGenerator::setConnector(connector * con)
{
	if (establishedConnector == nullptr)
	{
		establishedConnector = con;
	}
}

string netwEventGenerator::parseMessage(char * buf, size_t len)
{
	if (buf[0] == CIRCULAR_TOKENS)
	{
		for (size_t i = 0; i < len; i++)
		{
			if (buf[i] == 0)
			{
				buf[i] = 7;		//cambio el \0 a 7 representando al robber para poder manejarnos con string
			}
		}
	}
	buf[len] = '\0';
	return to_string(buf);
}

genericEvent * netwEventGenerator::getNetwEv(string message)
{
	genericEvent * ret = nullptr;
	networkingEventTypes header = static_cast<networkingEventTypes>(message[0]);
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

bool netwEventGenerator::emptyPackage(networkingEventTypes header)
{
	return ((header == ACK) || (header == NAME) || (header == PLAY_WITH_DEV) || (header == YOU_START) || (header == I_START) || (header == PASS) || (header >= YES));
}