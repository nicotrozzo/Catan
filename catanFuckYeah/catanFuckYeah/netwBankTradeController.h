#pragma once
#include "EDANetworkingController.h"
#include "catanGameModel.h"
#include "netwEmisor.h"

class netwBankTradeController : public EDANetworkingController
{
public:
	netwBankTradeController(catanGameModel * game,netwEmisor * emisor_);
	bool parseNetworkingEvent(networkingEv * package);
	netwControllerTypes getType() { return CTRL_BANKTRADE; }
	~netwBankTradeController();
private:
	catanGameModel *gameModel;
	netwEmisor * emisor;
};
