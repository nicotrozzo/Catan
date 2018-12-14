#include "netwRobberCardsController.h"



netwRobberCardsController::netwRobberCardsController(catanGameModel * game)
{
	gameModel = game;
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
		else
		{
			controllerEvent = new playingFSMEvent(CARDS_EV);
		}
	}
	return ret;
}


netwRobberCardsController::~netwRobberCardsController()
{
}
