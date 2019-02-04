#pragma once
#include "EDANetworkingController.h"
class netwYNController : public EDANetworkingController
{
public:
	netwYNController(catanGameModel * game);
	virtual bool parseNetworkingEvent(networkingEv * ev);
	virtual netwControllerTypes getType() { return CTRL_YN; }

	~netwYNController();
private:
	catanGameModel * gameModel;
};

