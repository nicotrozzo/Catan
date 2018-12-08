#include "inputHexagonController.h"
#include "gameDefines.h"
#include "gameCoords.h"


inputHexagonController::inputHexagonController(catanGameModel * game) : gameModel(game)
{

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
		if (abs(mouseCoords.x - clickCoords.x) <= OFFSET_HEXAGON_X)
		{
			if (abs(mouseCoords.y - clickCoords.y) <= OFFSET_HEXAGON_Y)
			{
				ret = gameModel->robberMoved('A' + i);
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
