#include "netwRematchController.h"
#include "rematchFSM.h"

netwRematchController::netwRematchController(netwEmisor * emisor_)
{
	emisor = emisor_;
	expectingEvent = false;
}

bool netwRematchController::parseNetworkingEvent(networkingEv * ev)
{
	bool ret = false;
	if (expectingEvent)
	{
		if (waitingPlayAgain)
		{
			if (ev->getHeader() == PLAY_AGAIN)
			{
				controllerEvent = new rematchEv(CHANGE);
				ret = true;
			}
			else if (ev->getHeader() == GAME_OVER)
			{
				controllerEvent = new rematchEv(END);
				emisor->sendPackage(ACK);
				ret = true;
			}
		}
		else if (ev->getHeader() == ACK)
		{
			controllerEvent = new rematchEv(END);
			ret = true;
		}
	}
	return ret;
}


void netwRematchController::setPlayAgain(bool playAgain)
{
	waitingPlayAgain = playAgain;
}

void netwRematchController::expectEvent()
{
	expectingEvent = true;
}

void netwRematchController::dontExpectEvent()
{
	expectingEvent = false;
}

