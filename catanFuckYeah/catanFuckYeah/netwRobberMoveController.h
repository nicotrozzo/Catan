#pragma once
#include "EDANetworkingController.h"
class netwRobberMoveController : public EDANetworkingController
{
public:
	netwRobberMoveController();
	virtual bool parseNetworkingEvent(networkingEv * ev);
	virtual netwControllerTypes getType() { return CTRL_ROBBERMOVE; }
	~netwRobberMoveController();
private:
	catanGameModel *gameModel;
};

