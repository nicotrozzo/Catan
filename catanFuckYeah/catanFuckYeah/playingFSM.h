#pragma once

#include "genericFSM.h"
#include "networkingEvents.h"
#include "EDAInputController.h"
#include "EDANetworkingController.h"
#include "gameModelViewer.h"
#include "mapViewer.h"
#include "player1Viewer.h"
#include "player2Viewer.h"
#include <vector>

enum netwStates : stateTypes { MY_TURN, BUILDING, PREPARE_TRADE , MY_ROBBER, WAITING_DICES, OPP_TURN, OPP_ROBBER, WAITING_PLAYER  };

enum playingFSMEvTypes : eventTypes {CHANGE_STATE, CARDS_EV, TICK_EV,ROBBER_EV, ERROR_EV};

class playingFSMEvent : public genericEvent
{
public:
	playingFSMEvent(string info_ = "") : error(false) { info = info_; }
	playingFSMEvent(playingFSMEvTypes type_) : error(false) { type = type_; }
	playingFSMEvent(playingFSMEvTypes type_, bool error_) : error(error_) { type = type_; }
	virtual eventTypes getType() { return type; }
	string getInfo() { return info; }
	bool getError() { return error; }
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

#define TX(x) (static_cast<void (genericFSM::* )(genericEvent *)>(&playingFSM::x)) //casteo a funcion, por visual

	const fsmCell fsmTable[8][5] = {
	//			CHANGE_STATE							CARDS_EV									TICK_EV							ROBBER_EV							ERROR	
	{ { WAITING_DICES,TX(passControllers)},	{PREPARE_TRADE,TX(tradeControllers)},	{BUILDING,TX(buildControllers)},		{MY_ROBBER,TX(doNothing)},	{MY_TURN,TX(error)} },		 //MY_TURN																														 
	{ { MY_TURN,TX(finishedBuilding) },	{BUILDING,TX(doNothing) },				{BUILDING,TX(ackController)},			{BUILDING,TX(doNothing)},				{BUILDING,TX(error)} },		 //BUILDING
	{ { MY_TURN,TX(myTurnControllers) },	{PREPARE_TRADE,TX(ackController)},		{PREPARE_TRADE,TX(netwYNControllers)},	{PREPARE_TRADE,TX(doNothing)},			{PREPARE_TRADE,TX(error)} },	 //PREPARE_TRADE
	{ { MY_TURN,TX(myTurnControllers) },	{MY_ROBBER,TX(oppCardsReady) },				{MY_ROBBER,TX(robbCardsReady) },	{MY_ROBBER,TX(prepareRobbMove)},	{MY_ROBBER,TX(error)} },		//MY_ROBBER
	{ { OPP_TURN,TX(oppTurnControllers)},	{WAITING_DICES,TX(doNothing)},			{WAITING_DICES, TX(doNothing)},			{OPP_ROBBER,TX(oppRobberControllers)},	{WAITING_DICES,TX(error)} },	//WAITING_DICES
	{ { MY_TURN,TX(myTurnPassControllers)},	{WAITING_PLAYER,TX(waitingControllers)},{WAITING_DICES, TX(dicesController)},			{OPP_TURN,TX(doNothing)},				{OPP_TURN,TX(error)} },		 //OPP_TURN
	{ { OPP_TURN,TX(oppTurnControllers) },	{OPP_ROBBER,TX(waitRobbMove)},				{OPP_ROBBER, TX(myCardsSent)},			{OPP_ROBBER, TX(doNothing)},			{OPP_ROBBER,TX(error)} },		 //OPP_ROBBER
	{ { OPP_TURN,TX(oppTurnControllers) },	{WAITING_PLAYER,TX(doNothing)},			{WAITING_PLAYER, TX(tradeControllers)},	{WAITING_PLAYER, TX(doNothing)},		{WAITING_PLAYER,TX(error)} }	 //WAITING_PLAYER
	};
	
	void passControllers(genericEvent* ev);
	void oppTurnControllers(genericEvent* ev);
	void tradeControllers(genericEvent* ev);
	void buildControllers(genericEvent* ev);
	void myRobberControllers(genericEvent* ev);
	void robbCardsReady(genericEvent* ev);
	void myCardsSent(genericEvent* ev);
	void prepareRobbMove(genericEvent* ev);
	void waitRobbMove(genericEvent* ev);
	void error(genericEvent* ev);
	void myTurnControllers(genericEvent* ev);
	void finishedBuilding(genericEvent* ev);
	void netwYNControllers(genericEvent* ev);
	void ackController(genericEvent * ev);
	void dicesController(genericEvent * ev);
	void oppCardsReady(genericEvent * ev);
	void myTurnPassControllers(genericEvent* ev);
	
	void doNothing(genericEvent* ev) {}

	void oppRobberControllers(genericEvent* ev);	
	void waitingControllers(genericEvent* ev);

	void myRobberCards();
	void myRobberMove();

	catanGameModel * gameModel;
	
	std::vector<EDAInputController *> allInputControllers;
	std::vector<EDANetworkingController *> allNetworkingControllers;
	std::list<EDAInputController *> currentInputControllers;
	std::list<EDANetworkingController *> currentNetworkingControllers;

	gameModelViewer * gameViewer;
	mapViewer * mapView;
	player1Viewer * p1view;
	player2Viewer * p2view;
	
	EDAInputController * getInputController(inputControllerTypes type);		//busca el controller de input solicitado en el vector de controllers de input
	EDANetworkingController * getNetworkingController(netwControllerTypes type);	//busca el controller de networking solicitado en el vector de controller de networking
	netwEmisor * emisor;
public:
	playingFSM(bool iStart, catanGameModel * game, std::vector<EDAInputController *> inputControllers, std::vector<EDANetworkingController *> networkingControllers, netwEmisor * emisor );	//recibe como parametro true si le toca empezar al jugador propio	
	void sendToInputControllers(inputEv *input);
	void sendToNetwControllers(networkingEv *netwPackage);
	~playingFSM();
};