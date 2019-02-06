#include "netwYNController.h"
#include "playingFSM.h"


netwYNController::netwYNController(catanGameModel * game) : gameModel(game)
{

}

bool netwYNController::parseNetworkingEvent(networkingEv * ev)
{
	bool ret = false;
	string evMessage;
	if (static_cast<networkingEv *>(ev)->getHeader() == YES)
	{
		if (gameModel->isSelecting() == OFFER_TRADE)
		{
			gameModel->playerTrade();
			ret = true;
			evMessage = "Opponent accepted your trade";
		}
	}
	else if (static_cast<networkingEv *>(ev)->getHeader() == NO)
	{
		if (gameModel->isSelecting() == OFFER_TRADE)
		{
			gameModel->clearTrades();
			ret = true;
			evMessage = "Opponent declined your trade";
		}
	}
	if (ret)
	{
		controllerEvent = new playingFSMEvent(CHANGE_STATE,evMessage);
	}
	return ret;
}



netwYNController::~netwYNController()
{
}
