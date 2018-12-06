#pragma once
#include "EDAInputController.h"
#include "catanGameModel.h"

/*Controller de botones de PASS, OFFER_TRADE Y BANK_TRADE*/
class inputActionButtonController : public EDAInputController
{
public:
	inputActionButtonController(catanGameModel * game);
	/*si el click cae en alguno de estos botones, hay que:
	PASS: controllerEvent = new changeStateEv (evento para cambiar de estado en la fsm de playing, va a cambiar a WAITING_DICES
	OFFER_TRADE: controllerEvent = new tradeEv(OFFER_TRADE); gameModel->preparePlayerTrade(DESSERT,0); para que el modelo avise que empieza un trade
	BANK_TRADE: controllerEvent = new tradeEV(BANK_TRADE);	gameModel->prepareBankTrade(DESSERT,false); para que el modelo avise que empieza un trade	
	*/
	virtual void parseMouseEvent(mouseEvent * ev);
	virtual void parseKeyboardEvent(keyboardEvent * ev);
	inputControllerTypes getType() { return CTRL_ACTION_BUTTON; }
	~inputActionButtonController();

private:
	catanGameModel * gameModel;
};

