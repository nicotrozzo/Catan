#include "netwRobberCardsController.h"



netwRobberCardsController::netwRobberCardsController()
{
}

bool netwRobberCardsController::parseNetworkingEvent(networkingEv * package)
{
	bool ret = false;
	if (package->getHeader() == ROBBER_CARDS)
	{
		robberCardsPckg *robberPckg = static_cast<robberCardsPckg *>(package);
		if (!(ret = gameModel->discardPlayer2(robberPckg->getCards())))
		{
			controllerEvent = new playingFSMErrorEv("Error en las cartas descartadas por robber adversario");
		}
	}
	return ret;
}


netwRobberCardsController::~netwRobberCardsController()
{
}
