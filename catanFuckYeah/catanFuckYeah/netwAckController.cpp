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

/*bool netwAckController::checkPhase()
{
	bool ret = false;
	if ((amountOfAckExpected == 3) && (phases == I_PHASE))
	{
		ret = true;
	}
	else if ((amountOfAckExpected == 2) && (phases == F_PHASE))
	{
		ret = true;
	}
	else if ((amountOfAckExpected == 1) && (phases == S_PHASE))
	{
		ret = true;
	}
	else
	{
		ret = false;
	}
	return ret;
}*/

/*void netwAckController::setPhase()
{
	if ((gameModel->getOtherPlayer()->getAmountOfCards() <= 7) && (phases == I_PHASE))
	{
		phases = F_PHASE;
	}
	else if ((phases == I_PHASE) && (gameModel->getCurrentPlayer()->getAmountOfCards() > 7))
	{
		phases = S_PHASE;
	}
	else if (phases == I_PHASE)
	{
		phases = T_PHASE;
	}
	else if ((gameModel->getCurrentPlayer()->getAmountOfCards() > 7) && (phases == F_PHASE))
	{
		phases = S_PHASE;
	}
	else if ((gameModel->getCurrentPlayer()->getAmountOfCards() <= 7) && (phases == F_PHASE))
	{
		phases = T_PHASE;
	}
}*/

netwAckController::~netwAckController()
{
}
