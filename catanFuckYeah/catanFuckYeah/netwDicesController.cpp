#include "netwDicesController.h"
#include "playingFSM.h"


netwDicesController::netwDicesController(catanGameModel * game) : gameModel(game)
{

}

bool netwDicesController::parseNetworkingEvent(networkingEv * ev)
{
	bool ret = false;
	if (ev->getHeader() == DICES_ARE)
	{
		dicesArePckg dicesPckg = *static_cast<dicesArePckg *>(ev);
		if (gameModel->dicesThrown(dicesPckg.getDice1(), dicesPckg.getDice2()))	//devuelve false si salio el rober
		{
			controllerEvent = new playingFSMEvent(CHANGE_STATE);
		}
		else	//si salio el robber
		{
			controllerEvent = new playingFSMEvent(ROBBER_EV);
		}
	}
	return ret;
}


netwDicesController::~netwDicesController()
{
}
