#pragma once
#include "EDANetworkingController.h"
#include "networkingEvents.h"
#include "netwEmisor.h"

class netwRematchController : public EDANetworkingController
{
public:
	netwRematchController(netwEmisor * emisor_);
	virtual bool parseNetworkingEvent(networkingEv * ev);
	virtual netwControllerTypes getType() { return CTRL_NETWREMATCH; }
	void setPlayAgain(bool playAgain);
	void expectEvent();
	void dontExpectEvent();
private:
	bool expectingEvent;
	bool waitingPlayAgain;
	netwEmisor * emisor;
};
