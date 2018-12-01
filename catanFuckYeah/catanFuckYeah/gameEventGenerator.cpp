#include "gameEventGenerator.h"
#include <cstring>


gameEventGenerator::gameEventGenerator()
{
}

genericEvent * gameEventGenerator::getEvent()
{
	return ev;

}

void gameEventGenerator::playerTrade(string offer)
{
	unsigned char currentResources = offer[0];
	if (game.validSelectedCards(offer.substr(2, currentResources), offer.substr(currentResources+1)))
	{
		ev = new tradeEvent(offer.substr(2, currentResources), offer.substr(currentResources + 1));
	}
}

void gameEventGenerator::bankTrade(unsigned char player, string offer)
{
	unsigned char currentResources = offer[0];
}

void 

gameEventGenerator::~gameEventGenerator()
{
}



class tradeEvent : public genericEvent
{
public:
	tradeEvent(string currentResources_, string otherResources_) { currentResources = currentResources_; otherResources = otherResources_; }
	eventType getType() { return TRADE_EVENT; }
private:
	string currentResources;
	string otherResources;
}