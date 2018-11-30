#include "networkingEvents.h"

#define PORT_COUNT 6
#define TERRAIN_COUNT 19

/*		NAME_IS		*/
nameIsPckg::nameIsPckg(string name_) : networkingEv(NAME_IS)
{
	error = true;
	if (name_.length() > 1)
	{
		name = name_.substr(1, name_[1]);
		if (name.length() == name_[1])
		{
			error = false;
		}
	}
}

string nameIsPckg::getName(void) 
{ 
	return name; 
}


/*		MAP_IS		*/	
mapIsPckg::mapIsPckg(string map_) : networkingEv(MAP_IS)
{
	map = map_.substr(1, PORT_COUNT + TERRAIN_COUNT);
	if (map.length() != (PORT_COUNT + TERRAIN_COUNT))
	{
		error = true;
	}
}

string mapIsPckg::getMap()
{
	return map;
}


/*		CIRCULAR_TOKENS		*/	
circTokensPckg::circTokensPckg(string tokens) : networkingEv(CIRCULAR_TOKENS)
{
	circTokens = tokens.substr(1);
	if (circTokens.length() != TERRAIN_COUNT)
	{
		error = true;
	}
}

string circTokensPckg::getTokens(void)
{
	return circTokens;
}

/*		OFFER_TRADE		*/
offerTradePckg::offerTradePckg(string offer) : networkingEv(OFFER_TRADE)
{
	if (offer.length() >= (offer[1] + offer[2] + 3))
	{
		ownRes = offer.substr(3, offer[1]);
		oppRes = offer.substr(3 + offer[1], offer[2]);
	}
	else
	{
		error = true;
	}
}

string offerTradePckg::getOwnResources(void) 
{
	return ownRes; 
}

string offerTradePckg::getOppResources(void) 
{
	return oppRes; 
}

/*		BANK_TRADE		*/	
bankTradePckg::bankTradePckg(string offer) : networkingEv(BANK_TRADE)
{
	if (offer.length() >= offer[1] + 3)
	{
		ownRes = offer.substr(2, offer[1]);
		bankRes = offer[2 + offer[1]];
	}
	else
	{
		error = true;
	}
}

string bankTradePckg::getOwnResources(void)
{ 
	return ownRes; 
}

unsigned char bankTradePckg::getBankResource(void)
{
	return bankRes;
}

/*		DICES_ARE		*/
dicesArePckg::dicesArePckg(string dices) : networkingEv(DICES_ARE)
{
	if (dices.length() >= 2)
	{
		dice1 = dices[1] - '0';
		dice2 = dices[2] - '0';
	}
	else
	{
		error = true;
	}
}

unsigned char dicesArePckg::getDicesSum(void)
{
	return dice1 + dice2;
}

/*		ROBBER_CARDS		*/
robberCardsPckg::robberCardsPckg(string robbCards) : networkingEv(ROBBER_CARDS)
{
	error = true;
	if (robbCards.length() > 1)
	{
		cardCount = robbCards[1];
		cards = robbCards.substr(2, cardCount);
		if (cards.length() == cardCount)
		{
			error = false;	//paquete bien formado
		}
	}
}

string robberCardsPckg::getCards(void)
{ 
	return cards; 
}

/*			ROBBER_MOVE			*/
robberMovePckg::robberMovePckg(string move) : networkingEv(ROBBER_MOVE)
{
	error = true;
	if (move.length() > 1)
	{
		newPos = move[1];
		error = !((newPos >= 'A') && (newPos <= 'S'));
	}
}

unsigned char robberMovePckg::getNewRobberPos(void)
{ 
	return newPos; 
}

/*			SETTLEMENT,ROAD,CITY		*/
buildPckg::buildPckg(string pckg) : networkingEv(static_cast<networkingEventTypes>(pckg[0]))
{
	if(!error)
	{
		coords = pckg.substr(2, pckg[1]);
		if (coords.length() != pckg[1])
		{
			error = true;
		}
	}
}

string buildPckg::getCoords(void)
{
	return coords;
}