#include "gameEventGenerator.h"
#include <cstring>
#include "allegro5.h"

gameEventGenerator::gameEventGenerator()
{
}


genericEvent * gameEventGenerator::getEvent()
{

	//return ev;
}

genericEvent * gameEventGenerator::playerTrade(string offer)
{
	if (al_get_next_event == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
	{
		unsigned char currentResources = offer[0];
		if (game.validSelectedCards(offer.substr(2, currentResources), offer.substr(currentResources + 1)))
		{
			return new tradeEvent(offer.substr(2, currentResources), offer.substr(currentResources + 1));
		}
	}
}

void gameEventGenerator::bankTrade(string offer)
{
	unsigned char currentResources = offer[0];
}

void gameEventGenerator

void 

gameEventGenerator::~gameEventGenerator()
{
}


