#include "netwAckController.h"


netwAckController::netwAckController(catanGameModel * game)
{
	gameModel = game;
	initial = 0;
	init();
}

void netwAckController::init()
{
	if (!initial)
	{
		phases = I_PHASE;
		amountOfAckExpected += ((gameModel->getOtherPlayer()->getAmountOfCards() <= 7) ? 1 : 0);
		amountOfAckExpected += ((gameModel->getCurrentPlayer()->getAmountOfCards() > 7) ? 1 : 0);
		amountOfAckExpected += 1;		//le sumo el ack recibido por robber_move
		initial = 1;
	}
}

bool netwAckController::parseNetworkingEvent(networkingEv * ev)
{
	bool ret = false;
	if (ev->getHeader() == CTRL_ACK)
	{
		switch (action)
		{
		case ROBBER_CASE:
			init();
			setPhase();
			if (checkPhase())
			{
				switch (phases)
				{
				case F_PHASE: //generar evento que se quede en el mismo lugar
					amountOfAckExpected--;
					break;
				case S_PHASE:	//generar evento que se quede en el mismo lugar
					amountOfAckExpected--;
					break;
				case T_PHASE:
					initial = 0;
					if (amountOfAckExpected == 0)
					{
						controllerEvent = new playingFSMEvent(CHANGE_STATE);
					}
					else
					{
						controllerEvent = new playingFSMErrorEv("Error reciving ack in robber final stage");
					}
					break;
				default:
					break;
				}
				ret = true;
			}
			else
			{
				controllerEvent = new playingFSMErrorEv("Error reciving ack in robber stage");
			}
			break;
		case OTHER_CASE:
			controllerEvent = new playingFSMEvent(CHANGE_STATE);
			break;
		}
	}
	return ret;
}

bool netwAckController::setAction(cases action_)
{
	if (validAction(action_))
	{
		action = action_;
	}
}

bool netwAckController::validAction(cases action_)
{
	return (action_ >= ROBBER_CASE && action_ <= OTHER_CASE);
}

bool netwAckController::checkPhase()
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
}

void netwAckController::setPhase()
{
	if ((gameModel->getOtherPlayer()->getAmountOfCards() <= 7) && (phases == I_PHASE))
	{
		phases == F_PHASE;
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
}

netwAckController::~netwAckController()
{
}
