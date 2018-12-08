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
	point vCoords;
	point eCoords;
	for (auto x : gameCoords::myVertexCoords)
	{
		if ( ABS(mouseCoords.x - x.second.xCoord) <= OFFSET_VERTEX_X)
		{
			if (ABS(mouseCoords.y - x.second.yCoord) <= OFFSET_VERTEX_Y)
			{
				if (!gameModel->isConstructing())
				{
					if (ret = gameModel->validConstruction(SETTLEMENT, x.first))
					{
						controllerEvent = new playingFSMEvent(TICK_EV);
					}
				}
				else
				{
					ret = gameModel->validConstruction(SETTLEMENT, x.first);		//no generera evento, solo cambia la construccion
				}
			}
		}
	}
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
						controllerEvent = new playingFSMEvent(TICK_EV);
					}
				}
				else
				{
					ret = gameModel->validConstruction(ROAD, x.first);
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
