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
	if ((package == CITY) || (package == SETTLEMENT) || (package == ROAD))
	{
		expectedPackage = package;
		expectsOnePackage = true;
		ret = true;
	}
	return ret;
}

void netwConstructionController::parseNetworkingEvent(networkingEv * ev)
{
	if (!expectsOnePackage || (ev->getHeader() == expectedPackage))	//si espera cualquier paquete o llego el paquete esperado
	{
		switch (ev->getHeader())
		{
		case SETTLEMENT:
			gameModel->validSelectedCards();
			break;
		case ROAD:

			break;
		case CITY:

			break;
		}
	}
}

netwConstructionController::~netwConstructionController()
{
}
