#pragma once
#include "catanGameModel.h"
class catanGameSetter : public catanGameModel
{
public:
	void setMyName(string name) { player1.setName(name); }
	void setOppName(string name) { player2.setName(name); }
	void setMap(string map_) { map.setMap(map_); };
	string getMap() { return map.getMap(); }
	string getCircularTokens() { return map.getCircularTokens(); };
	void setStartingPlayer(char player);
};



