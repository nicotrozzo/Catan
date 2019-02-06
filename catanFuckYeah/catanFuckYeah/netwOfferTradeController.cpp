#include "netwOfferTradeController.h"
#include "playingFSM.h"


netwOfferTradeController::netwOfferTradeController(catanGameModel * game)
{
	gameModel = game;
}

bool netwOfferTradeController::parseNetworkingEvent(networkingEv * ev)
{
	bool ret = false;
	if (ev->getHeader() == OFFER_TRADE)
	{
		ret = true;
		offerTradePckg *offerPckg = static_cast<offerTradePckg *>(ev);
		if (gameModel->playersTrade(offerPckg->getOppResources(), offerPckg->getOwnResources()))
		{
			controllerEvent = new playingFSMEvent(CARDS_EV,false,"Opponent offered a trade");
		}
		else
		{
			controllerEvent = new playingFSMEvent(CARDS_EV,true,"Opponent offered an invalid trade");	//carga error en true, porque mandaron un trade invalido
		}
	}
	return ret;
}


netwOfferTradeController::~netwOfferTradeController()
{
}
