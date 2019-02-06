#include "netwConstructionController.h"
#include "playingFSM.h"


netwConstructionController::netwConstructionController(catanGameModel * game, netwEmisor * netEmisor) : gameModel(game)
{
	expectsOnePackage = false;
	emisor = netEmisor;
}

netwConstructionController::netwConstructionController(catanGameModel * game, netwEmisor * netEmisor, networkingEventTypes package) : EDANetworkingController(((package == CITY) || (package == SETTLEMENT) || (package == ROAD)) ? expectedPackage = package : static_cast<networkingEventTypes>(0)) , gameModel(game)
{
	expectedPackage = package;
	expectsOnePackage = true;
	emisor = netEmisor;
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
				bool prevInitState = gameModel->initState();
				gameModel->construct();
				if (!gameModel->gameOver())
				{
					emisor->sendPackage(ACK);
				}
				else
				{
					controllerEvent = new playingFSMEvent(CHANGE_STATE);
					emisor->sendPackage(YOU_WON);
				}
				if(gameModel->initState() && (ev->getHeader() == ROAD) )
				{
					if (!gameModel->hasToConstruct())
					{
						controllerEvent = new playingFSMEvent(CHANGE_STATE);
					}
				}
				else if( (!gameModel->initState() && prevInitState) && !gameModel->isPlayer1Playing())	//si acaba de salir del estado inicial, emite un tick event
				{
					controllerEvent = new playingFSMEvent(TICK_EV);
				}
			}
		}
	}
	return ret;
}

/*Devuelve true si es un paquete de contruccion*/
bool netwConstructionController::buildingPackage(networkingEventTypes package)
{
	return ((package == CITY) || (package == SETTLEMENT) || (package == ROAD));
}

netwConstructionController::~netwConstructionController()
{

}
