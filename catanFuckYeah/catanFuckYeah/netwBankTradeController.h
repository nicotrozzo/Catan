#pragma once
#include "EDANetworkingController.h"
class netwBankTradeController : public EDANetworkingController
{
public:
	netwBankTradeController();
	bool parseNetworkingEvent(networkingEv * package);
	netwControllerTypes getType() { return CTRL_BANKTRADE; }
	~netwBankTradeController();
private:
	catanGameModel *gameModel;
};
