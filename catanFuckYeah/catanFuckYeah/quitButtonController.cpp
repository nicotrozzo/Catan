#include "quitButtonController.h"
#include "gameCoords.h"
#include "gameDefines.h"

quitButtonController::quitButtonController()
{
	controllerEvent = nullptr;
	startMenu = true;
}

bool quitButtonController::parseMouseEvent(mouseEvent * ev)
{
	bool ret = false;
	if (controllerEvent == nullptr)
	{
		point mouseCoords = ev->getClickCoords();
		coords dispCoords;
		if (startMenu)
		{
			dispCoords = gameCoords::buttonCoords["QUIT"];;
			if ((mouseCoords.x >= dispCoords.xCoord) && (mouseCoords.x - dispCoords.xCoord <= OFFSET_QUIT_X))
			{
				if ((mouseCoords.y >= dispCoords.yCoord) && (mouseCoords.y - dispCoords.yCoord <= OFFSET_QUIT_Y))
				{
					controllerEvent = new quitEv();
					ret = true;
				}
			}
			dispCoords = gameCoords::buttonCoords["PLAY"];
			if ((mouseCoords.x >= dispCoords.xCoord) && (mouseCoords.x - dispCoords.xCoord <= OFFSET_PLAY_X))
			{
				if ((mouseCoords.y >= dispCoords.yCoord) && (mouseCoords.y - dispCoords.yCoord <= OFFSET_PLAY_Y))
				{
					controllerEvent = new doneEv();
					ret = true;
				}
			}
		}
		else
		{
			dispCoords = gameCoords::buttonCoords["EXIT"];
			if ((mouseCoords.x >= dispCoords.xCoord) && (mouseCoords.x - dispCoords.xCoord <= OFFSET_QUIT_X))
			{
				if ((mouseCoords.y >= dispCoords.yCoord) && (mouseCoords.y - dispCoords.yCoord <= OFFSET_QUIT_Y))
				{
					controllerEvent = new quitEv();
					ret = true;
				}
			}
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
		else if (startMenu && (keyPressed == 'p' || keyPressed == 'P'))
		{
			controllerEvent = new doneEv();
			ret = true;
		}
	}
	return ret;
}

genericEvent * quitButtonController::getEvent()
{
	genericEvent * ret = nullptr;
	if (controllerEvent != nullptr)
	{
		ret = controllerEvent;
		controllerEvent = nullptr;
	}
	return ret;
}

void quitButtonController::toggleState()
{
	startMenu = !startMenu;
}
