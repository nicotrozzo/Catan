#include "netwBankTradeController.h"
#include "playingFSM.h"

netwBankTradeController::netwBankTradeController(catanGameModel*game, netwEmisor * emisor_)
{
	gameModel = game;
	emisor = emisor_;
}

bool netwBankTradeController::parseNetworkingEvent(networkingEv * package)
{
	bool ret = false;
	if (package->getHeader() == BANK_TRADE)
	{
		bankTradePckg *bankPckg = static_cast<bankTradePckg *>(package);
		if (!(ret = gameModel->bankTrade(bankPckg->getOppResources(), static_cast<resourceType>(bankPckg->getBankResource()))))
		{
			controllerEvent = new playingFSMErrorEv("Error en lo que se recibe del trueque del oponente con el banco");
		}
		else
		{
			emisor->sendPackage(ACK);
		}
	}
	return ret;
}

netwBankTradeController::~netwBankTradeController()
{

}