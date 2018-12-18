#include "inputHexagonController.h"
#include "gameDefines.h"
#include "gameCoords.h"


inputHexagonController::inputHexagonController(catanGameModel * game, netwEmisor* emisor) : gameModel(game)
{
	netEmisor = emisor;
}


bool  inputHexagonController::parseMouseEvent(mouseEvent * ev)
{
	bool ret = false;
	point mouseCoords = ev->getClickCoords();
	point clickCoords;
	for (int i = 0; i < HEX_COUNT; i++)
	{
		clickCoords.x = gameCoords::myHexagonCoords['A' + i].xCoord;
		clickCoords.y = gameCoords::myHexagonCoords['A' + i].yCoord;
		if (abs(mouseCoords.x - clickCoords.x) <= OFFSET_HEXAGON_X/2)
		{
			if (abs(mouseCoords.y - clickCoords.y) <= OFFSET_HEXAGON_Y/2)
			{
				if (ret = gameModel->robberMoved('A' + i))
				{
					string send;
					send += 'A' + i;
					netEmisor->sendPackage(ROBBER_MOVE, send);
				}
			}
		}
		
	}
	return ret;
}

inputControllerTypes inputHexagonController::getType()
{
	return CTRL_HEXAGON;
}

inputHexagonController::~inputHexagonController()
{

}
