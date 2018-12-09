#include "netwAckController.h"


netwAckController::netwAckController(catanGameModel * game)
{
	gameModel = game;
	numberOfCalls = 0;
	phases = F_PHASE;
	amountOfAck += ((gameModel->getOtherPlayer().getAmountOfCards() < 7) ? 1 : 0);
	amountOfAck += ((gameModel->getCurrentPlayer().getAmountOfCards() > 7) ? 1 : 0);
	amountOfAck += 1;		//le sumo el ack recibido por robber_move
}

bool netwAckController::parseNetworkingEvent(networkingEv * ev)
{
	bool ret = false;
	if (ev->getHeader() == CTRL_ACK)
	{
		switch (action)
		{
		case ROBBER_CASE:
			/*if (gameModel->isPlayer1Playing())
			{
				if (amountOfAck)
				{

				}
				
			}*/
			switch (numberOfCalls)
			{
			case 0:
				if (gameModel->getOtherPlayer().getAmountOfCards() > 7)
				{
					
				}
				break;
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			default:
				break;
			}
			numberOfCalls++;
			
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
