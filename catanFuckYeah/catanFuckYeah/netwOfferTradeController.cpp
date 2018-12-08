#include "netwOfferTradeController.h"



netwOfferTradeController::netwOfferTradeController()
{
}

bool netwOfferTradeController::parseNetworkingEvent(networkingEv * ev)
{
	bool ret = false;
	if (ev->getHeader() == OFFER_TRADE)
	{
		offerTradePckg *offerPckg = static_cast<offerTradePckg *>(ev);
		if (gameModel->validSelectedCards(offerPckg->getOwnResources(), offerPckg->getOppResources()))
		{
			controllerEvent = new playingFSMEvent(CARDS_EV);
		}
		else
		{
			controllerEvent = new playingFSMErrorEv("Error en el trueque pedido");
		}
	}
	return ret;
}


netwOfferTradeController::~netwOfferTradeController()
{
}
