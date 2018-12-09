#include "netwConstructionController.h"



netwConstructionController::netwConstructionController(catanGameModel * game) : gameModel(game)
{
	expectsOnePackage = false;
}

netwConstructionController::netwConstructionController(catanGameModel * game, networkingEventTypes package) : EDANetworkingController(((package == CITY) || (package == SETTLEMENT) || (package == ROAD)) ? expectedPackage = package : static_cast<networkingEventTypes>(0)) , gameModel(game)
{
	expectedPackage = package;
	expectsOnePackage = true;
}

/*Asigna un paquete esperado al controller, ahora pasara a reaccionar solo ante la llegada de dicho paquete*/
void netwConstructionController::setExpectedPackage(networkingEventTypes package)
{
	if (buildingPackage(package))
	{
		expectedPackage = package;
		expectsOnePackage = true;
	}
}

bool netwConstructionController::parseNetworkingEvent(networkingEv * ev)
{
	bool ret = false;
	if (buildingPackage(ev->getHeader()))
	{
		if (!expectsOnePackage || (ev->getHeader() == expectedPackage))	//si espera cualquier paquete o llego el paquete esperado
		{
			ret = true;
			if (!gameModel->validConstruction(ev->getHeader(), static_cast<buildPckg *>(ev)->getCoords()))
			{
				controllerEvent = new playingFSMErrorEv("Error en construccion");
			}
			else
			{
				gameModel->construct();
			}
		}
	}
}

/*Devuelve true si es un paquete de contruccion*/
bool netwConstructionController::buildingPackage(networkingEventTypes package)
{
	return ((package == CITY) || (package == SETTLEMENT) || (package == ROAD));
}

netwConstructionController::~netwConstructionController()
{

}
