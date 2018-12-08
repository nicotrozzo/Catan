#pragma once
#include "EDANetworkingController.h"
class netwRobberCardsController : public EDANetworkingController
{
public:
	netwRobberCardsController();
	bool parseNetworkingEvent(networkingEv * package);
	netwControllerTypes getType() { return CTRL_ROBBERCARDS; }
	~netwRobberCardsController();
private:
	catanGameModel *gameModel;
};

