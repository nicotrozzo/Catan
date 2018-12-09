#include "catanGameSetter.h"

catanGameSetter::catanGameSetter()
{
}

void catanGameSetter::setMyName(string name)
{
	player1.setName(name);
}

void catanGameSetter::setOppName(string name)
{
	player2.setName(name);
}

bool catanGameSetter::setMap(string map_)
{
	return map.setMap(map_);
}

string catanGameSetter::getCircularTokens()
{
	return map.getCircularTokens();
}

void catanGameSetter::setInitialPlayer(unsigned char player)
{
	if (player == 1)
	{
		player1playing = true;
	}
	else if (player == 2)
	{
		player1playing = false;
	}
}

bool catanGameSetter::setCircularTokens(string tokens)
{
	return map.setCircularToken(tokens);
}

catanGameSetter::~catanGameSetter()
{
}
