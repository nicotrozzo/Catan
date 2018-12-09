#include "quitButtonController.h"
#include "gameCoords.h"
#include "gameDefines.h"

quitButtonController::quitButtonController()
{
	controllerEvent = nullptr;
}

bool quitButtonController::parseMouseEvent(mouseEvent * ev)
{
	bool ret = false;
	if (controllerEvent == nullptr)
	{
		point mouseCoords = ev->getClickCoords();
		coords dispCoords = gameCoords::buttonCoords["QUIT"];

		if ((mouseCoords.x >= dispCoords.xCoord) && (mouseCoords.x - dispCoords.xCoord <= OFFSET_QUIT_X) && startMenu)
		{
			if ((mouseCoords.y >= dispCoords.yCoord) && (mouseCoords.y - dispCoords.yCoord <= OFFSET_QUIT_Y))
			{
				ret = false;
			}
		}
		dispCoords = gameCoords::buttonCoords["EXIT"];
		if ((mouseCoords.x >= dispCoords.xCoord) && (mouseCoords.x - dispCoords.xCoord <= OFFSET_QUIT_X) && !startMenu)
		{
			if ((mouseCoords.y >= dispCoords.yCoord) && (mouseCoords.y - dispCoords.yCoord <= OFFSET_QUIT_Y))
			{
				ret = false;
			}
		}
		if (ret)
		{
			controllerEvent = new quitEv();
		}
	}
	return ret;
}

bool quitButtonController::parseKeyboardEvent(keyboardEvent * ev)
{
	bool ret = false;
	if (controllerEvent == nullptr)
	{
		char keyPressed = ev->getKey();
		if (keyPressed == 'q' || keyPressed == 'Q')
		{
			controllerEvent = new quitEv();
			ret = true;
		}
	}
	return ret;
}

genericEvent * quitButtonController::getEvent()
{
	return controllerEvent;
}

void quitButtonController::toggleState()
{
	startMenu = !startMenu;
}
