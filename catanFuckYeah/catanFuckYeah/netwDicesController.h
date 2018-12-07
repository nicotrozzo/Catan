#pragma once
#include "EDANetworkingController.h"

class netwDicesController : public EDANetworkingController
{
public:
	netwDicesController(catanGameModel * game);
	virtual bool parseNetworkingEvent(networkingEv * ev);
	~netwDicesController();

private:
	catanGameModel * gameModel;
};

