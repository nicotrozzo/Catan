#include "EDANetworkingController.h"
#include "playingFSM.h"

EDANetworkingController::EDANetworkingController() : controllerEvent(nullptr)
{
	expectedPackage = ACK;	//por defecto espera un ACK
}

EDANetworkingController::EDANetworkingController(networkingEventTypes package) : controllerEvent(nullptr)
{
	expectedPackage = package;
}

void EDANetworkingController::setExpectedPackage(networkingEventTypes package)
{
	expectedPackage = package;
}

bool EDANetworkingController::parseNetworkingEvent(networkingEv * ev) 
{
	bool ret = false;
	if (ev->getHeader() == expectedPackage)
	{
		controllerEvent = new playingFSMEvent(CHANGE_STATE);
		ret = true;
	}
	return ret;
}

genericEvent* EDANetworkingController::getEvent(void)
{
	genericEvent * temp = nullptr;
	if (controllerEvent != nullptr)
	{
		temp = controllerEvent;
		controllerEvent = nullptr;
	}
	return temp;
}