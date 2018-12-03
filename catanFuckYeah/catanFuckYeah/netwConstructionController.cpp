#include "netwConstructionController.h"



netwConstructionController::netwConstructionController()
{
	expectsOnePackage = false;
}

netwConstructionController::netwConstructionController(networkingEventTypes package) : EDANetworkingController(((package == CITY) || (package == SETTLEMENT) || (package == ROAD)) ? expectedPackage = package : static_cast<networkingEventTypes>(0) )
{
	expectsOnePackage = true;
}

bool netwConstructionController::setExpectedPackage(networkingEventTypes package)
{
	bool ret = false;
	if (buildingPackage(package))
	{
		expectedPackage = package;
		expectsOnePackage = true;
		ret = true;
	}
	return ret;
}

bool netwConstructionController::parseNetworkingEvent(networkingEv * ev)
{
	bool ret = false;
	if (buildingPackage(ev->getHeader()))
	{
		if (!expectsOnePackage || (ev->getHeader() == expectedPackage))	//si espera cualquier paquete o llego el paquete esperado
		{
			ret = true;
			if (!gameModel->construction(ev->getHeader(), static_cast<buildPckg *>(ev)->getCoords()))
			{
				controllerEvent = new playingError;
			}
		}
	}
}

bool netbuildingPackage(networkingEventTypes package)
{
	return ((package == CITY) || (package == SETTLEMENT) || (package == ROAD));
}

netwConstructionController::~netwConstructionController()
{

}
