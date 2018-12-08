#pragma once
#include "EDANetworkingController.h"
class netwYNController : public EDANetworkingController
{
public:
	netwYNController(catanGameModel * game);
	virtual bool parseNetworkingEvent(genericEvent * ev);
	virtual netwControllerTypes getType() { return CTRL_YN; }

	~netwYNController();
private:
	catanGameModel * gameModel;
};

