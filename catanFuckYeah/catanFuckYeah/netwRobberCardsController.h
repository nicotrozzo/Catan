#pragma once
#include "EDANetworkingController.h"
class netwRobberCardsController : public EDANetworkingController
{
public:
	netwRobberCardsController(catanGameModel * game);
	bool parseNetworkingEvent(networkingEv * package);
	netwControllerTypes getType() { return CTRL_ROBBERCARDS; }
	~netwRobberCardsController();
private:
	catanGameModel *gameModel;
};

