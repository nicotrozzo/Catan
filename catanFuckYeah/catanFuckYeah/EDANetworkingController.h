#pragma once
#include "networkingEvents.h"
#include "eventHandling.h"
#include "catanGameModel.h"
#include "playingFSM.h"

typedef enum netwControllerTypes { GENERIC_NETW_CONTROLLER,CTRL_CONSTRUCTION, CTRL_DICES,CTRL_BANKTRADE,CTRL_OFFERTRADE, CTRL_ROBBERCARDS, CTRL_YN};

class EDANetworkingController : public eventGenerator 
{
public:
	EDANetworkingController();
	EDANetworkingController(networkingEventTypes package);
	virtual bool parseNetworkingEvent(networkingEv * ev);
	virtual void setExpectedPackage(networkingEventTypes package);
	virtual netwControllerTypes getType() { return GENERIC_NETW_CONTROLLER; }
	genericEvent* getEvent();
protected:
	networkingEventTypes expectedPackage;
	genericEvent * controllerEvent;
};