#include "EDANetworkingController.h"

EDANetworkingController::EDANetworkingController() : controllerEvent(nullptr)
{
	expectedPackage = static_cast<networkingEventTypes>(0);
}

EDANetworkingController::EDANetworkingController(networkingEventTypes package) : controllerEvent(nullptr)
{
	expectedPackage = package;
}

bool EDANetworkingController::parseNetworkingEvent(networkingEv * ev) 
{
	bool ret = false;
	if (ev->getHeader() == expectedPackage)
	{
		controllerEvent = new finishEvent;	//despues ver que significa este evento
		ret = true;
	}
	return ret;
}

genericEvent* EDANetworkingController::getEvent(void)
{
	return controllerEvent;
}