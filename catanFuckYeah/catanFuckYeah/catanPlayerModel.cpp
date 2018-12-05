#include "catanPlayerModel.h"


catanPlayerModel::catanPlayerModel() : myCards({ 0,0,0,0,0 })
{
	victoryPoints = 0;
}


void catanPlayerModel::setP1Name(string name)
{
	if (p1NameIs.length() == 0)
	{
		p1NameIs = name.substr(0, MAX_NAME_LENGTH);
	}
}
void catanPlayerModel::setP2Name(string name)
{
	if (p2NameIs.length() == 0)
	{
		p2NameIs = name.substr(0, MAX_NAME_LENGTH);
	}
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

bool catanPlayerModel::decResource(unsigned char resource)
{
	bool ret = true;
	switch (resource)
	{
	case ORE:
		if (myCards.ore > 0)
		{
			myCards.ore--;
		}
		else
		{
			ret = false;
		}
		break;
	case WOOD:
		if (myCards.wood > 0)
		{
			myCards.wood--;
		}
		else
		{
			ret = false;
		}
		break;
	case WOOL:
		if (myCards.wool > 0)
		{
			myCards.wool--;
		}
		else
		{
			ret = false;
		}
		break;
	case WHEAT:
		if (myCards.wheat > 0)
		{
			myCards.wheat--;
		}
		else
		{
			ret = false;
		}
		break;
	case BRICK:
		if (myCards.brick > 0)
		{
			myCards.brick--;
		}
		else
		{
			ret = false;
		}
		break;
	default:
		ret = false;
	}
	return ret;
}

catanPlayerModel::~catanPlayerModel()
{
}


