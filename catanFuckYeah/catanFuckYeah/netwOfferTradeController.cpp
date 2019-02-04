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
			controllerEvent = new playingFSMEvent(CARDS_EV);
		}
		/*else
		{
			controllerEvent = new playingFSMErrorEv("Error en el trueque pedido");
		}*/
	}
	return ret;
}


netwOfferTradeController::~netwOfferTradeController()
{
}
