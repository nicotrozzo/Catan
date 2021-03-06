#pragma once
#include "EDAInputController.h"
#include "catanGameModel.h"
#include "netwEmisor.h"
#include "timerEventGenerator.h"

typedef enum tickActions_t{ TICK_OPP_TRADE, TICK_BANK_TRADE, TICK_OWN_TRADE, TICK_BUILD, TICK_ROBB_CARDS, TICK_INVALID_TRADE };

class inputTickAndXController :	public EDAInputController
{
public:
	inputTickAndXController(catanGameModel * game, netwEmisor * emisor, timerEventGenerator * ansTimer);
	virtual inputControllerTypes getType() { return CTRL_TICKANDX; }
	/*La variable actionToDo indica que debe hacer cuando aprietan:
		-TICK_OPP_TRADE:	* tick hace la transaccion ( playerTrade() ), si devuelve false ALTO ERROR. NO PREGUNTAR PLAYERTRADEREADY() 
							* cruz cancela la transaccion ( clearTrades() )
		-TICK_BANK_TRADE:	* tick pregunta si esta lista la transaccion ( metodo bankTradeReady() ), si es valida la hace ( bankTrade() ), sino ignora
							* cruz cancela la seleccion ( clearTrades() ) 
		-TICK_OWN_TRADE:	* tick pregunta si esta lista la transaccion ( metodo playerTradeReady() ), si esta lista la hace ( playerTrade() ), sino ignora
							* cruz cancela la seleccion ( clearTrades() ) 
		-TICK_BUILD:		* tick construye (metodo construct() ), si devuelve false es ERROR, EMITE EVENTO A PLAYING FSM
							* cruz cancela (metodo cancelConstruction() ), 
		-TICK_ROBB_CARDS:	* tick pregunta si ya selecciono la cantidad necesaria de cartas (metodo robberCardsReady()), si devuelve true, lo descarta ( metodo discardCurrentPlayer() )
							* cruz cancela la seleccion (metodo clearRobberCards() )
	SIEMPRE QUE HAGA ALGO EMITIR EVENTO CHANGE_STATE
	*/
	virtual bool parseMouseEvent(mouseEvent * ev);
	virtual bool parseKeyboardEvent(keyboardEvent * ev);
	void setActionToDo(tickActions_t action);	

private:
	catanGameModel * gameModel;
	timerEventGenerator * answerTimer;
	tickActions_t actionToDo;
	bool validAction(tickActions_t action);
	bool selectionCall(bool yes);
	netwEmisor * netEmisorEv;
};

