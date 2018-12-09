#pragma once
#include "EDANetworkingController.h"
class netwOfferTradeController : public EDANetworkingController
{
public:
	netwOfferTradeController();
	virtual bool parseNetworkingEvent(networkingEv * ev);
	virtual netwControllerTypes getType() { return CTRL_OFFERTRADE; }
	~netwOfferTradeController();
private:
	catanGameModel *gameModel;
};

