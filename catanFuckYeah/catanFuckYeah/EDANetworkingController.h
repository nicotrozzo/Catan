#pragma once
#include "networkingEvents.h"
#include "eventHandling.h"
#include "catanGameModel.h"

typedef enum netwControllerTypes { GENERIC_NETW_CONTROLLER,CTRL_CONSTRUCTION };

class EDANetworkingController : public eventGenerator 
{
public:
	EDANetworkingController();
	EDANetworkingController(networkingEventTypes package);
	virtual bool parseNetworkingEvent(networkingEv * ev);
	virtual netwControllerTypes getType() { return GENERIC_NETW_CONTROLLER; }
	genericEvent* getEvent();
protected:
	networkingEventTypes expectedPackage;
	genericEvent * controllerEvent;
};