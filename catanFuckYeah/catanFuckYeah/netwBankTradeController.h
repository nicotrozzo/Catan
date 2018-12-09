#pragma once
#include "EDANetworkingController.h"
#include "catanGameModel.h"
class netwBankTradeController : public EDANetworkingController
{
public:
	netwBankTradeController(catanGameModel * game);
	bool parseNetworkingEvent(networkingEv * package);
	netwControllerTypes getType() { return CTRL_BANKTRADE; }
	~netwBankTradeController();
private:
	catanGameModel *gameModel;
};
