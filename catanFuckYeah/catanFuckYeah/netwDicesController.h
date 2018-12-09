#pragma once
#include "EDANetworkingController.h"

class netwDicesController : public EDANetworkingController
{
public:
	netwDicesController(catanGameModel * game);
	virtual bool parseNetworkingEvent(networkingEv * ev);
	netwControllerTypes getType() { return CTRL_DICES; }
	~netwDicesController();

private:
	catanGameModel * gameModel;
};

