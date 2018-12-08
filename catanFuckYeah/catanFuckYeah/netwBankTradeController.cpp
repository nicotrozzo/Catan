#include "netwBankTradeController.h"

netwBankTradeController::netwBankTradeController()
{

}

bool netwBankTradeController::parseNetworkingEvent(networkingEv * package)
{
	bool ret = false;
	if (package->getHeader() == BANK_TRADE)
	{
		bankTradePckg *bankPckg = static_cast<bankTradePckg *>(package);
		if (gameModel->validSelectedCards("", bankPckg->getOppResources()))
		{

		}
		else
		{
			controllerEvent = new playingFSMErrorEv("Error en lo que se recibe del trueque del oponente con el banco");
		}
	}
	return ret;
}

netwBankTradeController::~netwBankTradeController()
{

}