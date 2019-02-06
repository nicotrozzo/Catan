#include "inputRematchController.h"
#include "rematchFSM.h"


inputRematchController::inputRematchController(netwEmisor * emisor_)
{
	emisor = emisor_;
	expectingEvent = false;
}

bool inputRematchController::parseMouseEvent(mouseEvent * ev)
{
	bool ret = false;
	if (expectingEvent)
	{
		point clickCoords = ev->getClickCoords();
		if( (clickCoords.y >= REMATCH_Y) && (clickCoords.y <= REMATCH_Y + OFFSET_REMATCH_Y) )
		{
			if( (clickCoords.x >= TICK_REMATCH_X) && (clickCoords.x <= TICK_REMATCH_X + OFFSET_TICK_REMATCH_X) )
			{
				controllerEvent = new rematchEv(CHANGE);
				emisor->sendPackage(PLAY_AGAIN);
				ret = true;
			}
			else if ((clickCoords.x >= CROSS_REMATCH_X) && (clickCoords.x <= CROSS_REMATCH_X + OFFSET_CROSS_REMATCH_X))
			{
				controllerEvent = new rematchEv(END);
				emisor->sendPackage(GAME_OVER);
				ret = true;
			}
		}
	}
	return ret;
}

bool inputRematchController::parseKeyboardEvent(keyboardEvent * ev)
{
	bool ret = false;
	if (expectingEvent)
	{
		if (ev->getKey() == 'Y')
		{
			controllerEvent = new rematchEv(CHANGE);
			emisor->sendPackage(PLAY_AGAIN);
			ret = true;
		}
		else if (ev->getKey() == 'N')
		{
			controllerEvent = new rematchEv(END);
			emisor->sendPackage(GAME_OVER);
			ret = true;
		}
	}
	return ret;
}

void inputRematchController::expectEvent()
{
	expectingEvent = true;
}

void inputRematchController::dontExpectEvent()
{
	expectingEvent = false;
}
