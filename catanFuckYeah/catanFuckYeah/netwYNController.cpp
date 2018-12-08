#include "netwYNController.h"



netwYNController::netwYNController(catanGameModel * game) : gameModel(game)
{

}

bool netwYNController::parseNetworkingEvent(genericEvent * ev)
{
	bool ret = false;
	if (static_cast<networkingEv *>(ev)->getHeader() == YES)
	{
		gameModel->isSelecting()
	}
	else if (static_cast<networkingEv *>(ev)->getHeader() == NO)
	{

	}
	return ret;
}



netwYNController::~netwYNController()
{
}
