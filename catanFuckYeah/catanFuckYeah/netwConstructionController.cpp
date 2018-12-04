#include "netwConstructionController.h"



netwConstructionController::netwConstructionController(catanGameModel * game) : gameModel(game)
{
	expectsOnePackage = false;
}

netwConstructionController::netwConstructionController(catanGameModel * game,networkingEventTypes package) : EDANetworkingController(((package == CITY) || (package == SETTLEMENT) || (package == ROAD)) ? expectedPackage = package : static_cast<networkingEventTypes>(0)) , gameModel(game)
{
	expectsOnePackage = true;
}

/*Asigna un paquete esperado al controller, ahora pasara a reaccionar solo ante la llegada de dicho paquete*/
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

/*Devuelve true si es un paquete de contruccion*/
bool netwConstructionController::netbuildingPackage(networkingEventTypes package)
{
	return ((package == CITY) || (package == SETTLEMENT) || (package == ROAD));
}

netwConstructionController::~netwConstructionController()
{

}
