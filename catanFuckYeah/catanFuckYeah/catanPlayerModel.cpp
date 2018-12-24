#include "catanPlayerModel.h"


catanPlayerModel::catanPlayerModel() : myCards({ 0,0,0,0,0 })
{
	victoryPoints = 0;
	NameIs = "";
}

unsigned char catanPlayerModel::getAmountOfCards()
{
	return myCards.totalCardsCount();
}

cards catanPlayerModel::getCards()
{
	return myCards;
}

unsigned char catanPlayerModel::getVictoryPoints()
{
	return victoryPoints;
}

void catanPlayerModel::setVictoryPoints(unsigned char points)
{
	victoryPoints = points; 
}

void catanPlayerModel::setName(string name)
{
	if (name.length() > MAX_NAME_LENGTH)
	{
		NameIs = name.substr(0, MAX_NAME_LENGTH);
	}
	else
	{
		NameIs = name;
	}
}

void catanPlayerModel::setLongestRoad(unsigned char longRoad)
{
	longestRoad = longRoad;
}

unsigned char catanPlayerModel::getLongestRoad()
{
	return longestRoad;
}

string catanPlayerModel::getName()
{
	return NameIs;
}

unsigned char catanPlayerModel::getPlayerNumber()
{
	return playerNumber;
}

bool catanPlayerModel::incResource(unsigned char resource)
{
	bool ret = true;
	switch (resource)
	{
	case ORE:
		myCards.ore++;
		break;
	case WOOD:
		myCards.wood++;
		break;
	case WOOL:
		myCards.wool++;
		break;
	case WHEAT:
		myCards.wheat++;
		break;
	case BRICK:
		myCards.brick++;
		break;
	default:
		ret = false;
	}
	return ret;
}

bool catanPlayerModel::incResource(unsigned char resource, unsigned char count)
{
	bool ret = true;
	if (count > 0)
	{
		switch (resource)
		{
		case ORE:
			myCards.ore += count;
			break;
		case WOOD:
			myCards.wood += count;
			break;
		case WOOL:
			myCards.wool += count;
			break;
		case WHEAT:
			myCards.wheat += count;
			break;
		case BRICK:
			myCards.brick += count;
			break;
		default:
			ret = false;
		}
	}
	return ret;
}

bool catanPlayerModel::decResource(unsigned char resource)
{
	bool ret = false;
	switch (resource)
	{
	case ORE:
		if (myCards.ore > 0)
		{
			myCards.ore--;
			ret = true;
		}
		break;
	case WOOD:
		if (myCards.wood > 0)
		{
			myCards.wood--;
			ret = true;
		}
		break;
	case WOOL:
		if (myCards.wool > 0)
		{
			myCards.wool--;
			ret = true;
		}
		break;
	case WHEAT:
		if (myCards.wheat > 0)
		{
			myCards.wheat--;
			ret = true;
		}
		break;
	case BRICK:
		if (myCards.brick > 0)
		{
			myCards.brick--;
			ret = true;
		}
		break;
	}
	return ret;
}

bool catanPlayerModel::decResource(unsigned char resource, unsigned char count)
{
	bool ret = true;
	if (count > 0)
	{
		switch (resource)
		{
		case ORE:
			if (myCards.ore - count >= 0)
			{
				myCards.ore -= count;
			}
			else
			{
				ret = false;
			}
			break;
		case WOOD:
			if (myCards.wood - count >= 0)
			{
				myCards.wood -= count;
			}
			else
			{
				ret = false;
			}
			break;
		case WOOL:
			if (myCards.wool - count >= 0)
			{
				myCards.wool -= count;
			}
			else
			{
				ret = false;
			}
			break;
		case WHEAT:
			if (myCards.wheat - count >= 0)
			{
				myCards.wheat-= count;
			}
			else
			{
				ret = false;
			}
			break;
		case BRICK:
			if (myCards.brick - count >= 0)
			{
				myCards.brick-= count;
			}
			else
			{
				ret = false;
			}
			break;
		default:
			ret = false;
		}
	}
	return ret;
}

catanPlayerModel::~catanPlayerModel()
{
}
