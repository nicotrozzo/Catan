#include "netwAckController.h"
#include "playingFSM.h"

netwAckController::netwAckController(catanGameModel * game)
{
	gameModel = game;
}

bool netwAckController::parseNetworkingEvent(networkingEv * ev)
{
	bool ret = false;
	if (ev->getHeader() == ACK)
	{
		switch (action)
		{
		case DICES_CASE:
			controllerEvent = new playingFSMEvent(CARDS_EV);
			ret = true;
			break;
		case ROBBER_CARDS_CASE:
			controllerEvent = new playingFSMEvent(ROBBER_EV);
			ret = true;
			break;
		case OTHER_CASE:
			controllerEvent = new playingFSMEvent(CHANGE_STATE);
			ret = true;
			break;
		}
	}
	return ret;
}

bool netwAckController::setAction(cases action_)
{
	bool ret = false;
	if (validAction(action_))
	{
		action = action_;
		ret = true;
	}
	return ret;
}

bool netwAckController::validAction(cases action_)
{
	return (action_ >= ROBBER_CARDS_CASE && action_ <= OTHER_CASE);
}

netwAckController::~netwAckController()
{
}
