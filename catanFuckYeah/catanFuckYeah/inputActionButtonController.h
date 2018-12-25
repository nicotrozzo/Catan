#pragma once
#include "EDAInputController.h"
#include "catanGameModel.h"
#include "netwEmisor.h"
#include "timerEventGenerator.h"

/*Controller de botones de PASS, OFFER_TRADE Y BANK_TRADE*/
class inputActionButtonController : public EDAInputController
{
public:
	inputActionButtonController(catanGameModel * game, netwEmisor * emisor, timerEventGenerator * ansTimer);
	/*si el click cae en alguno de estos botones, hay que:
	PASS: controllerEvent = new changeStateEv (evento para cambiar de estado en la fsm de playing, va a cambiar a WAITING_DICES
	OFFER_TRADE: controllerEvent = new tradeEv(OFFER_TRADE); gameModel->preparePlayerTrade(DESSERT,0); para que el modelo avise que empieza un trade
	BANK_TRADE: controllerEvent = new tradeEV(BANK_TRADE);	gameModel->prepareBankTrade(DESSERT,false); para que el modelo avise que empieza un trade	
	*/
	virtual bool parseMouseEvent(mouseEvent * ev);
	virtual bool parseKeyboardEvent(keyboardEvent * ev);
	inputControllerTypes getType() { return CTRL_ACTION_BUTTON; }
	~inputActionButtonController();

private:
	catanGameModel * gameModel;
	timerEventGenerator * answerTimer;
	netwEmisor * netEmisorEv;
};

