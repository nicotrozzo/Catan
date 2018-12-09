#include "netwYNController.h"



netwYNController::netwYNController(catanGameModel * game) : gameModel(game)
{

}

bool netwYNController::parseNetworkingEvent(genericEvent * ev)
{
	bool ret = false;
	if (static_cast<networkingEv *>(ev)->getHeader() == YES)
	{
		if (gameModel->isSelecting() == OFFER_TRADE)
		{
			gameModel->playerTrade();
		}
		else
		{
			controllerEvent = new playingFSMErrorEv("Error en respuesta de la oferta enviada");
		}
	}
	else if (static_cast<networkingEv *>(ev)->getHeader() == NO)
	{
		if (gameModel->isSelecting() == OFFER_TRADE)
		{
			gameModel->clearTrades();
		}
		else
		{
			controllerEvent = new playingFSMErrorEv("Error en respuesta de la oferta enviada");
		}
	}
	return ret;
}



netwYNController::~netwYNController()
{
}