#include "EDANetworkingController.h"

EDANetworkingController::EDANetworkingController(catanGameModel* game) : controllerEvent(nullptr), gameModel(game)
{
	expectedPackage = static_cast<networkingEventTypes>(0);
}

EDANetworkingController::EDANetworkingController(catanGameModel* game,networkingEventTypes package) : controllerEvent(nullptr), gameModel(game)
{
	expectedPackage = package;
}

bool EDANetworkingController::parseNetworkingEvent(networkingEv * ev) 
{
	bool ret = false;
	if (ev->getHeader() == expectedPackage)
	{
		controllerEvent = new finishEvent;
		ret = true;
	}
	return ret;
}

genericEvent* EDANetworkingController::getEvent(void)
{
	return controllerEvent;
}