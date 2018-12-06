#pragma once
#include "EDANetworkingController.h"

class netwDicesController : public EDANetworkingController
{
public:
	netwDicesController();
	virtual bool parseNetworkingEvent(networkingEv * ev);
	~netwDicesController();
};

