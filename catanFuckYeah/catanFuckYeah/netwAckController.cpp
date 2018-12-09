#include "netwAckController.h"


netwAckController::netwAckController(catanGameModel * game)
{
	gameModel = game;
	phases = F_PHASE;
}

bool netwAckController::parseNetworkingEvent(networkingEv * ev)
{
	bool ret = false;
	if (ev->getHeader() == CTRL_ACK)
	{
		switch (action)
		{
		case ROBBER_CASE:
			/*currentAmountCards = gameModel->getCurrentPlayer().getAmountOfCards();
			otherAmountCards = gameModel->getOtherPlayer().getAmountOfCards()
			if (currentAmountCards >= 7 && otherAmountCards >= 7)
			{

			}
			else if (currentAmountCards <= 7 && otherAmountCards >= 7)
			{

			}*/
			bool flag;
			if (gameModel->isPlayer1Playing())
			{
				flag = ((gameModel->getOtherPlayer().getAmountOfCards() < 7) ? true : false);
				queueOfAck.push(flag);
				flag = ((gameModel->getCurrentPlayer().getAmountOfCards() > 7) ? true : false);
				queueOfAck.push(flag);
			}
			if (!queueOfAck.empty())
			{

			}
			break;
		case OTHER_CASE:
			controllerEvent = new playingFSMEv(CHANGE_STATE);
			break;
		}
	}
	return ret;
}

bool netwAckController::setAction(cases action_)
{
	if (validAction(action_))
	{
		action = action_
	}
}

bool netwAckController::validAction(cases action_)
{
	return (action_ >= ROBBER_CASE && action_ <= OTHER_CASE);
}

netwAckController::~netwAckController()
{
}
