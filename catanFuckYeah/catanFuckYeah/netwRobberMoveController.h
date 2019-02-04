#pragma once
#include "EDANetworkingController.h"
#include "netwEmisor.h"

class netwRobberMoveController : public EDANetworkingController
{
public:
	netwRobberMoveController(catanGameModel * game,netwEmisor * emisor_);
	virtual bool parseNetworkingEvent(networkingEv * ev);
	virtual netwControllerTypes getType() { return CTRL_ROBBERMOVE; }
	~netwRobberMoveController();
private:
	catanGameModel *gameModel;
	netwEmisor * emisor;
};

