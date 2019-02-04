#include "netwYNController.h"
#include "playingFSM.h"


netwYNController::netwYNController(catanGameModel * game) : gameModel(game)
{

}

bool netwYNController::parseNetworkingEvent(networkingEv * ev)
{
	bool ret = false;
	if (static_cast<networkingEv *>(ev)->getHeader() == YES)
	{
		if (gameModel->isSelecting() == OFFER_TRADE)
		{
			gameModel->playerTrade();
			ret = true;
		}
	}
	else if (static_cast<networkingEv *>(ev)->getHeader() == NO)
	{
		if (gameModel->isSelecting() == OFFER_TRADE)
		{
			gameModel->clearTrades();
			ret = true;
		}
	}
	if (ret)
	{
		controllerEvent = new playingFSMEvent(CHANGE_STATE);
	}
	return ret;
}



netwYNController::~netwYNController()
{
}
