#pragma once
#include "EDANetworkingController.h"
#include "networkingEvents.h"
#include "catanGameModel.h"
#include "netwEmisor.h"

class netwConstructionController :	public EDANetworkingController
{
public:
	netwConstructionController(catanGameModel * game,netwEmisor * netemisor);
	netwConstructionController(catanGameModel * game,netwEmisor * netemisor,networkingEventTypes package);	//si recibe un paquete en especifico, solo va a reaccionar a los eventos de dicho paquete
	void setExpectedPackage(networkingEventTypes package);
	bool parseNetworkingEvent(networkingEv * package);
	netwControllerTypes getType() { return CTRL_CONSTRUCTION; }
	~netwConstructionController();
private:
	bool expectsOnePackage;
	bool buildingPackage(networkingEventTypes package);
	catanGameModel * gameModel;
	netwEmisor *emisor;
};

