#pragma once
#include "EDANetworkingController.h"
#include "networkingEvents.h"

class netwConstructionController :	public EDANetworkingController
{
public:
	netwConstructionController();
	netwConstructionController(networkingEventTypes package);	//si recibe un paquete en especifico, solo va a reaccionar a los eventos de dicho paquete
	bool setExpectedPackage(networkingEventTypes package);
	bool parseNetworkingEvent(networkingEv * package);
	~netwConstructionController();
private:
	bool expectsOnePackage;
	bool buildingPackage(networkingEventTypes package);
};

