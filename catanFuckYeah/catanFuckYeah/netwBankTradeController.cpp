#include "netwBankTradeController.h"
#include "playingFSM.h"

netwBankTradeController::netwBankTradeController(catanGameModel*game)
{
	gameModel = game;
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
	}
	return ret;
}

netwBankTradeController::~netwBankTradeController()
{

}