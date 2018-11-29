#pragma once

#include "genericFSM.h"
#include "networkingEvents.h"

enum netwStates : stateTypes { MY_TURN, BUILDING, PREPARE_TRADE , WAITING_REPLY, MY_ROBBER,  WAITING_DICES, OPP_ROBBER, OPP_TURN, WAITING_ANSWER  };

enum netwFSMEvTypes : eventTypes {OK, DICES7, STAY, UNEXPECTED_EVENT};

class netwFSMEv : public genericEvent
{
public:
	netwFSMEv() : error(false) {}
	netwFSMEv(netwFSMEvTypes type_) { }//if(valid)type = type_; }
	virtual eventTypes getType() { return type; }
	bool getError() { return false; }
private:
	netwFSMEvTypes type;
	bool error;
};

class unexpectedNetwEvent : public netwFSMEv
{
public:
	unexpectedNetwEvent(string detail_ = "") : netwFSMEv(UNEXPECTED_EVENT) { detail = detail_; }
	string getDetail() { return detail; }

private:
	string detail;
};

class playingFSM : public genericFSM
{


private:

#define TX(x) (static_cast<void (genericFSM::* )(genericEvent *)>(&bossFSM::x)) //casteo a funcion, por visual

	const fsmCell fsmTable[8][6] = {	
	//			OK								CANCEL								ROBBER								BUILD 									TRADE					UNEXPECTED_EVENT					
	{ { WAITING_DICES,TX(sendPass) },	  { MY_TURN,TX(nada) },				 { MY_ROBBER,TX(prepareRobber) },  { BUILDING,TX(mandoconstruccion) },	{ PREPARE_TRADE,TX(verdesp) },	{ MY_TURN,TX(error) } },		 //MY_TURN
	{ { BUILDING,TX(JFSDJFLtHJS) },		  { MY_TURN,TX(cancelOperation) },   { BUILDING,TX(error) },		   { MY_TURN,TX(confirmOperation) },	{ BUILDING,TX(error) },			{ BUILDING,TX(error) } },		 //BUILDING
	{ { PREPARE_TRADE,TX(OfferOrconfirm)},{ MY_TURN,TX(cancelOpSepararcasos) },{ PREPARE_TRADE,TX(error) },		{ PREPARE_TRADE,TX(error) },			{ MY_TURN,TX(verdesp) },	{ PREPARE_TRADE,TX(error) } },			//PREPARE_TRADE
	{ { MY_ROBBER,TX(sendToRobber) },	  { MY_TURN,TX(verdesp) },			 { MY_ROBBER,TX(sendToRobber) },   { MY_ROBBER,TX(error) },				{ MY_ROBBER,TX(error) },		{ MY_ROBBER,TX(error) } },		 //MY_ROBBER
	{ { OPP_TURN,TX(sendDices) },		  { WAITING_DICES,TX(error) },		 { WAITING_DICES,TX(error) },	   { WAITING_DICES,TX(error) },			{ WAITING_DICES,TX(error) },	{ WAITING_DICES,TX(error) } },	 //WAITING_DICES
	{ { OPP_TURN,TX(moveRobber) },		  { OPP_ROBBER ,TX(verdesp)},		 { OPP_ROBBER,TX(sendToRobberFSM)},{ OPP_ROBBER,TX(error) },			{ OPP_ROBBER,TX(error) },		{ OPP_ROBBER,TX(error) } },		 //OPP_ROBBER
	{ {	MY_TURN,TX(changeTurn) },		  { OPP_TURN,TX(error) },			 { OPP_ROBBER,TX(prepareRobber) }, { OPP_TURN,TX(validate),				{ WAITING_ANSWER,TX(sendTradeOffer) },{ OPP_TURN,TX(error) } } },//OPP_TURN
	{ { OPP_TURN,TX(sendAnswer) },		  { OPP_TURN,TX(sendAnswer2) },		 { WAITING_ANSWER,TX(error) },	   { WAITING_ANSWER,TX(error) },		{ WAITING_ANSWER,TX(error) },	{ WAITING_ANSWER,TX(error) } }	 //WAITING_ANSWER
	};

	//The action routines for the FSM
	void sendDices(genericEvent * ev);
	void prepareRobber(genericEvent * ev);
	void error(genericEvent * ev);
	void sendToRobberFSM(genericEvent * ev);
	void sendTradeOffer(genericEvent * ev);
	void sendAnswer(genericEvent * ev);
	void changeTurn(genericEvent * ev);
	void validate(genericEvent * ev);
	void doNothing(genericEvent * ev) {}

	list<networkingEventTypes> expectedPackages;
	genericFSM * robberfsm;
public:
	playingFSM();	//attachear modelo como generador de eventos
	list<networkingEv> getExpectedPackages();
};

enum robberStates : stateTypes { WAIT_USER, WAIT_OPPONENT, WAIT_ROBBMOVE };

enum robberFSMEvTypes : eventTypes { ROBBER_CARDS, ROBBER_MOVE, MY_CARDS, MY_CARDS_AND_WAIT };

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

	const fsmCell fsmTable[2][2] = {
	//	   PACKAGE							USER_INPUT									
	{ { WAIT_USER,TX(error) },		    { WAIT_OPPONENT, TX(sendMyCards) } },	//WAIT_MY_USER
	{ { WAIT_OPPONENT,TX(sendPackage)}, { WAIT_OPPONENT,TX(error) },			//WAIT_OPPONENT
	};

	//The action routines for the FSM

	void error(genericEvent * ev);
	void sendMyCards(genericEvent * ev);
	void sendPackage(genericEvent * ev);

	//expectedevent
public:
	oppRobberFSM(stateTypes initState);	
};


class myRobberFSM : public genericFSM
{
private:

#define TX(x) (static_cast<void (genericFSM::* )(genericEvent *)>(&bossFSM::x)) //casteo a funcion, por visual

	/*const fsmCell fsmTable[3][2] = {
		//	   OK							ROBBER_MOVE								MY_CARDS									MY_CARDS_AND_WAIT									
		{ { WAIT_USER,TX(error) },		 { WAIT_USER,TX(error) },			{ WAIT_ROBBMOVE,TX(sendCardsToOpponent) },	{ WAIT_ROBBCARDS,TX(sendCardsToOpponent) } },	//WAIT_OPP_CARDS
		{ { WAIT_ROBBMOVE,TX(sendCards)},{ WAIT_ROBBCARDS,TX(error) },		{ WAIT_ROBBCARDS,TX(error) },				{ WAIT_ROBBCARDS,TX(error) } },					//WAIT_ROBBCARDS
		{ { WAIT_ROBBMOVE,TX(error) },	 { WAIT_ROBBMOVE,TX(moveRobber) },	{ WAIT_ROBBMOVE,TX(error) },				{ WAIT_ROBBMOVE,TX(error) } }					//WAIT_ROBBMOVE
	};*/

	const fsmCell fsmTable[2][2] = {
		//	   PACKAGE							USER_INPUT									
		{ { WAIT_USER,TX(error) },		    { WAIT_OPPONENT, TX(sendMyCards) } },	//WAIT_MY_USER
		{ { WAIT_OPPONENT,TX(sendPackage)}, { WAIT_OPPONENT,TX(error) },			//WAIT_OPPONENT
		};

	//The action routines for the FSM

	void error(genericEvent * ev);
	void sendCards(genericEvent * ev);
	void sendCardsToOpponent(genericEvent * ev);
	void moveRobber(genericEvent * ev);
	int oppDiscard;
public:
	myRobberFSM(stateTypes initState);
};