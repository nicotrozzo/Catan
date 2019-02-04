#include "netwRobberMoveController.h"
#include "playingFSM.h"

netwRobberMoveController::netwRobberMoveController(catanGameModel * game,netwEmisor * emisor_) : gameModel(game)
{
	emisor = emisor_;
}

bool netwRobberMoveController::parseNetworkingEvent(networkingEv * ev)
{
	bool ret = false;
	if (ev->getHeader() == ROBBER_MOVE)
	{
		ret = true;
		robberMovePckg *robberPckg = static_cast<robberMovePckg *>(ev);
		if (gameModel->robberMoved(robberPckg->getNewRobberPos()))
		{
			controllerEvent = new playingFSMEvent(CHANGE_STATE);
			emisor->sendPackage(ACK);
		}
		else
		{
			controllerEvent = new playingFSMErrorEv("Error en la posicion del robber que me llega");
		}
	}
	return ret;
}


netwRobberMoveController::~netwRobberMoveController()
{
}
