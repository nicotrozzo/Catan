#include "netwRobberMoveController.h"



netwRobberMoveController::netwRobberMoveController()
{
}

bool netwRobberMoveController::parseNetworkingEvent(networkingEv * ev)
{
	bool ret = false;
	if (ev->getHeader() == ROBBER_MOVE)
	{
		robberMovePckg *robberPckg = static_cast<robberMovePckg *>(ev);
		if (gameModel->robberMoved(robberPckg->getNewRobberPos()))
		{
			controllerEvent = new playingFSMEvent(CHANGE_STATE);
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
