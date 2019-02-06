#include "inputRematchController.h"
#include "rematchFSM.h"
#include "gameDefines.h"
#include "gameCoords.h"

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
		if( (clickCoords.y >= gameCoords::buttonCoords["REMATCH/PLAY_AGAIN"].yCoord ) && (clickCoords.y <= gameCoords::buttonCoords["REMATCH/PLAY_AGAIN"].yCoord + OFFSET_REMATCH_Y) )
		{
			if( (clickCoords.x >= gameCoords::buttonCoords["REMATCH/PLAY_AGAIN"].xCoord) && (clickCoords.x <= gameCoords::buttonCoords["REMATCH/PLAY_AGAIN"].xCoord + OFFSET_PLAY_AGAIN_X) )
			{
				controllerEvent = new rematchEv(CHANGE);
				emisor->sendPackage(PLAY_AGAIN);
				ret = true;
			}
			else if ((clickCoords.x >= gameCoords::buttonCoords["SCAPE"].xCoord) && (clickCoords.x <= gameCoords::buttonCoords["SCAPE"].xCoord + OFFSET_SCAPE_X))
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
