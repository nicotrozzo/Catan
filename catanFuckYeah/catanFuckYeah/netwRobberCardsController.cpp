#include "netwRobberCardsController.h"
#include "playingFSM.h"


netwRobberCardsController::netwRobberCardsController(catanGameModel * game,netwEmisor * emisor_)
{
	gameModel = game;
	emisor = emisor_;
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
			emisor->sendPackage(ACK);
		}
	}
	return ret;
}


netwRobberCardsController::~netwRobberCardsController()
{
}
