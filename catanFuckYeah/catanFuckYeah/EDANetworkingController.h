#pragma once
#include "networkingEvents.h"
#include "eventHandling.h"
#include "catanGameModel.h"

class EDANetworkingController : public eventGenerator 
{
public:
	EDANetworkingController();
	EDANetworkingController(networkingEventTypes package);
	virtual bool parseNetworkingEvent(networkingEv * ev);
	genericEvent* getEvent();
protected:
	networkingEventTypes expectedPackage;
	genericEvent * controllerEvent;
};