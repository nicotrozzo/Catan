#pragma once
#include "catanGameModel.h"


class catanGameSetter : public catanGameModel
{
public:
	void setMyName(string name);
	void setOppName(string name);
	bool setMap(string map_);
	string getCircularTokens();
	bool setCircularTokens(string tokens);
	void setInitialPlayer(unsigned char player);
};



