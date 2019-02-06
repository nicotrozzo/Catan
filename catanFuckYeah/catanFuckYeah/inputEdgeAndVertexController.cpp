#include "inputEdgeAndVertexController.h"
#include "gameDefines.h"
#include "gameCoords.h"
#include "playingFSM.h"

#define ABS(x) ((x) > 0 ? (x) : -(x))

inputEdgeAndVertexController::inputEdgeAndVertexController(catanGameModel * game) : gameModel(game)
{
}


bool inputEdgeAndVertexController::parseMouseEvent(mouseEvent * ev)
{
	bool ret = false;
	point mouseCoords = ev->getClickCoords();
	for (auto x : gameCoords::myVertexCoords)
	{
		if ( ABS(mouseCoords.x - x.second.xCoord) <= OFFSET_VERTEX_X)
		{
			if (ABS(mouseCoords.y - x.second.yCoord) <= OFFSET_VERTEX_Y)
			{
				if (!gameModel->isConstructing())
				{
					if( (ret = gameModel->validConstruction(SETTLEMENT, x.first)) || (ret = gameModel->validConstruction(CITY, x.first)) )
					{
						string message = "Do you want to build?";
						controllerEvent = new playingFSMEvent(TICK_EV,message);
					}
				}
				else
				{
					if (!(ret = gameModel->validConstruction(SETTLEMENT, x.first)))	//no generera evento, solo cambia la construccion
					{
						ret = gameModel->validConstruction(CITY, x.first);
					}
				}
				break;
			}
		}
	}
	if (!ret)
	{
		for (auto x : gameCoords::myEdgesCoords)
		{
			if (ABS(mouseCoords.x - x.second.xCoord) <= OFFSET_EDGE_X)
			{
				if (ABS(mouseCoords.y - x.second.yCoord) <= OFFSET_EDGE_Y)
				{
					if (!gameModel->isConstructing())
					{
						if (ret = gameModel->validConstruction(ROAD, x.first))
						{
							string message = "Do you want to build?";
							controllerEvent = new playingFSMEvent(TICK_EV,message);
						}
					}
					else
					{
						ret = gameModel->validConstruction(ROAD, x.first);
					}
				}
			}
		}
	}
	return ret;
}

bool inputEdgeAndVertexController::parseKeyboardEvent(keyboardEvent * ev)
{
	bool ret = false;
	return ret;
}

inputEdgeAndVertexController::~inputEdgeAndVertexController()
{
}
