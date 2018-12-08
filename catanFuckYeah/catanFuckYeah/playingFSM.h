#pragma once

#include "genericFSM.h"
#include "networkingEvents.h"
#include "EDAInputController.h"
#include "EDANetworkingController.h"
#include <vector>

enum netwStates : stateTypes { MY_TURN, BUILDING, PREPARE_TRADE , WAITING_REPLY, MY_ROBBER, WAITING_DICES, OPP_TURN, OPP_ROBBER, WAITING_PLAYER  };

enum playingFSMEvTypes : eventTypes {CHANGE_STATE, CARDS_EV, TICK_EV,ROBBER_EV, ERROR_EV};

class playingFSMEvent : public genericEvent
{
public:
	playingFSMEvent(string info_ = "") : error(false) { info = info_; }
	playingFSMEvent(playingFSMEvTypes type_) { type = type_; }
	virtual eventTypes getType() { return type; }
	string getInfo() { return info; }
	bool getError() { return false; }
private:
	playingFSMEvTypes type;
	string info;
	bool error;
};

class playingFSMErrorEv : public playingFSMEvent
{
public:
	playingFSMErrorEv(string detail_ = "") : playingFSMEvent(ERROR_EV) { detail = detail_; }
	string getDetail() { return detail; }

private:
	string detail;
};

class playingFSMCardsEv : public playingFSMEvent
{
public:
	playingFSMCardsEv(bool offerTrade_) : playingFSMEvent(CARDS_EV) { offerTrade = offerTrade_; }
	bool isOfferTrade() { return offerTrade; }
private:
	bool offerTrade;	//true si es un offer trade, false sino
};

class playingFSM : public genericFSM
{


private:

#define TX(x) (static_cast<void (genericFSM::* )(genericEvent *)>(&bossFSM::x)) //casteo a funcion, por visual

/*	const fsmCell fsmTable[8][6] = {	
	//			OK								CANCEL								ROBBER								BUILD 									TRADE							UNEXPECTED_EVENT					
	{ { WAITING_DICES,TX(sendPass) },	  { MY_TURN,TX(nada) },				 { MY_ROBBER,TX(prepareMyRobber) },  { BUILDING,TX(mandoconstruccion) },{ PREPARE_TRADE,TX(verdesp) },			{ MY_TURN,TX(error) } },		 //MY_TURN
	{ { BUILDING,TX(JFSDJFLtHJS) },		  { MY_TURN,TX(cancelOperation) },   { BUILDING,TX(error) },		   { MY_TURN,TX(confirmOperation) },	{ BUILDING,TX(error) },					{ BUILDING,TX(error) } },		 //BUILDING
	{ { PREPARE_TRADE,TX(OfferOrconfirm)},{ MY_TURN,TX(cancelOpSepararcasos) },{ PREPARE_TRADE,TX(error) },		{ PREPARE_TRADE,TX(error) },		{ MY_TURN,TX(verdesp) },				{ PREPARE_TRADE,TX(error) } },   //PREPARE_TRADE
	{ { MY_ROBBER,TX(sendToRobber) },	  { MY_TURN,TX(verdesp) },			 { MY_ROBBER,TX(sendToRobber) },   { MY_ROBBER,TX(error) },				{ MY_ROBBER,TX(error) },				{ MY_ROBBER,TX(error) } },		 //MY_ROBBER
	{ { OPP_TURN,TX(sendDices) },		  { WAITING_DICES,TX(error) },		 { WAITING_DICES,TX(error) },	   { WAITING_DICES,TX(error) },			{ WAITING_DICES,TX(error) },			{ WAITING_DICES,TX(error) } },	 //WAITING_DICES
	{ { OPP_TURN,TX(moveRobber) },		  { OPP_ROBBER ,TX(verdesp)},		 { OPP_ROBBER,TX(sendToRobberFSM)},{ OPP_ROBBER,TX(error) },			{ OPP_ROBBER,TX(error) },				{ OPP_ROBBER,TX(error) } },		 //OPP_ROBBER
	{ {	MY_TURN,TX(changeTurn) },		  { OPP_TURN,TX(error) },			 { OPP_ROBBER,TX(prepareOppRobber) }, { OPP_TURN,TX(validate),			{ WAITING_ANSWER,TX(sendTradeOffer) },	{ OPP_TURN,TX(error) } } },		 //OPP_TURN
	{ { OPP_TURN,TX(sendAnswer) },		  { OPP_TURN,TX(sendAnswer2) },		 { WAITING_ANSWER,TX(error) },	   { WAITING_ANSWER,TX(error) },		{ WAITING_ANSWER,TX(error) },			{ WAITING_ANSWER,TX(error) } }	 //WAITING_ANSWER
	};

	//The action routines for the FSM
	void sendDices(genericEvent * ev);
	void prepareMyRobber(genericEvent * ev);
	void prepareOppRobber(genericEvent * ev);
	void error(genericEvent * ev);
	void sendToRobberFSM(genericEvent * ev);
	void sendTradeOffer(genericEvent * ev);
	void sendAnswer(genericEvent * ev);
	void changeTurn(genericEvent * ev);
	void validate(genericEvent * ev);
	void doNothing(genericEvent * ev) {}
	
	list<networkingEventTypes> expectedPackages;*/
	genericFSM * robberfsm;
	const fsmCell fsmTable[8][5] = {
	//			CHANGE_STATE							CARDS_EV									TICK_EV							ROBBER_EV							ERROR	
	{ { WAITING_DICES,TX(passControllers)}	,{PREPARE_TRADE,TX(tradeControllers)},{BUILDING,TX(buildControllers)},{MY_ROBBER,TX(myRobberControllers)},{MY_TURN,TX(error)} },		 //MY_TURN
	{ { MY_TURN,TX(myTurnControllers) }		,{BUILDING,TX(doNothing)}			 ,{BUILDING,TX(doNothing) }		,{BUILDING,TX(doNothing) }			,{BUILDING,TX(error)} },		 //BUILDING
	{ { MY_TURN,TX(myTurnControllers) }		,{PREPARE_TRADE,TX(doNothing)}		 ,{PREPARE_TRADE,TX(netwYNControllers) },{PREPARE_TRADE,TX(doNothing)},{PREPARE_TRADE,TX(error)} },	 //PREPARE_TRADE
	{ { MY_TURN,TX(myTurnControllers) },  { ,TX() },{ ,TX() },{ ,TX() },{MY_ROBBER,TX(error)} },		//MY_ROBBER
	{ { OPP_TURN,TX(oppTurnControllers)},  { ,TX()},{},{OPP_ROBBER,TX(oppRobberControllers)},{WAITING_DICES,TX(error)} },	//WAITING_DICES
	{ { MY_TURN,TX(myTurnPassControllers) },  {WAITING_PLAYER,TX(waitingControllers)},{},{,TX()},{OPP_TURN,TX(error)} },		 //OPP_TURN
	{ { OPP_TURN,TX(oppTurnControllers) },{OPP_ROBBER,TX()},{},{},{OPP_ROBBER,TX(error)} },		 //OPP_ROBBER
	{ { OPP_TURN,TX(oppTurnControllers) },{},{},{},{WAITING_PLAYER,TX(error)} }	 //WAITING_PLAYER
	};
	
	void passControllers(genericEvent* ev);
	void oppTurnControllers(genericEvent* ev);
	void tradeControllers(genericEvent* ev);
	void buildControllers(genericEvent* ev);
	void myRobberControllers(genericEvent* ev);
	void error(genericEvent* ev);
	void myTurnControllers(genericEvent* ev);
	void netwYNControllers(genericEvent* ev);
	void myTurnPassControllers(genericEvent* ev);
	
	void doNothing(genericEvent* ev) {}

	void oppRobberControllers(genericEvent* ev);	
	void waitingControllers(genericEvent* ev);
	void(genericEvent* ev);
	void(genericEvent* ev);

	catanGameModel * gameModel;
	
	std::vector<EDAInputController *> allInputControllers;
	std::vector<EDANetworkingController *> allNetworkingControllers;
	std::list<EDAInputController *> currentInputControllers;
	std::list<EDANetworkingController *> currentNetworkingControllers;

	EDAInputController * getInputController(inputControllerTypes type);		//busca el controller de input solicitado en el vector de controllers de input
	EDANetworkingController * getNetworkingController(netwControllerTypes type);	//busca el controller de networking solicitado en el vector de controller de networking

public:
	playingFSM(bool iStart, catanGameModel * game, std::vector<EDAInputController *> inputControllers, std::vector<EDANetworkingController *> networkingControllers );	//recibe como parametro true si le toca empezar al jugador propio	
	void sendToInputControllers(inputEv *input);
	void sendToNetwControllers(networkingEv *netwPackage);
};

enum robberStates : stateTypes { WAIT_USER, WAIT_OPPONENT, WAIT_ROBBMOVE };

enum robberFSMEvTypes : eventTypes { INCOMING_ROBBER_CARDS, INCOMING_ROBBER_MOVE, MY_CARDS, MY_CARDS_AND_WAIT };

class robberFSMEv : public genericEvent
{
public:
	robberFSMEv();
	robberFSMEv(robberFSMEvTypes type_); //if(valid) type(type_) {}
	robberFSMEvTypes getType() { return type; }
	bool getError();
private:
	//referencia al modelo de juego
	robberFSMEvTypes type;
	bool error = false;
};

class oppRobberFSM : public genericFSM
{
private:

#define TX(x) (static_cast<void (genericFSM::* )(genericEvent *)>(&bossFSM::x)) //casteo a funcion, por visual

	const fsmCell fsmTable[2][3] = {
	//	   PACKAGE							ACCEPT_CLICK						CARD_CLICK									
	{ { WAIT_USER,TX(error) },		    { WAIT_OPPONENT, TX(sendMyCards) }, { WAIT_MY_USER,TX(takeCard) } },	//WAIT_MY_USER
	{ { WAIT_OPPONENT,TX(savePackage)}, { WAIT_OPPONENT,TX(error) },		{ WAIT_OPPONENT,TX(error) } },		//WAIT_OPPONENT
	};

	//The action routines for the FSM

	void error(genericEvent * ev);
	void sendMyCards(genericEvent * ev);
	void savePackage(genericEvent * ev);
	void takeCard(genericEvent * ev);

	//expectedevent
public:
	oppRobberFSM(stateTypes initState);	
};


class myRobberFSM : public genericFSM
{
private:

#define TX(x) (static_cast<void (genericFSM::* )(genericEvent *)>(&bossFSM::x)) //casteo a funcion, por visual

	const fsmCell fsmTable[2][3] = {
		//	   PACKAGE							ACCEPT_CLICK							CARD_ROBBER_CLICK									
		{ { WAIT_MY_USER,TX(savePackage)}, { WAIT_OPPONENT_ANSWER,TX(error) },		{ WAIT_OPPONENT_ANSWER,TX(error) } },	//WAIT_OPPONENT_ANSWER
		{ { WAIT_MY_USER,TX(error) },	   { WAIT_OPPONENT_ANSWER,TX(sendMyMove) }, { WAIT_MY_ANSWER,TX(checkMyMove) } }	//WAIT_MY_USER
		};

	//The action routines for the FSM

	void savePackage(genericEvent * ev);
	void sendMyMove(genericEvent * ev);
	void checkMyMove(genericEvent * ev);
	void error(genericEvent * ev);
	void seveCards(genericEvent * ev);
	void sendCardsToOpponent(genericEvent * ev);
	void moveRobber(genericEvent * ev);
	int oppDiscard;
	int packageToSend    //paquete a enviar
public:
	myRobberFSM(stateTypes initState);
};