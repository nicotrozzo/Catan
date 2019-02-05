#pragma once
#include "EDANetworkingController.h"
#include "netwEmisor.h"

class netwRobberCardsController : public EDANetworkingController
{
public:
	netwRobberCardsController(catanGameModel * game,netwEmisor * emisor_);
	bool parseNetworkingEvent(networkingEv * package);
	netwControllerTypes getType() { return CTRL_ROBBERCARDS; }
	~netwRobberCardsController();
private:
	catanGameModel *gameModel;
	netwEmisor * emisor;
};

