#pragma once
#include "networkingEvents.h"
#include "eventHandling.h"
#include "catanGameModel.h"

class EDANetworkingController : public eventGenerator 
{
public:
	EDANetworkingController(catanGameModel * game);
	EDANetworkingController(catanGameModel * game, networkingEventTypes package);
	virtual bool parseNetworkingEvent(networkingEv * ev);
	genericEvent* getEvent();
protected:
	catanGameModel * gameModel;
	networkingEventTypes expectedPackage;
	genericEvent * controllerEvent;
};