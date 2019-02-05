#pragma once
#include <iostream>
#include "eventHandling.h"
#include "genericFSM.h"
#include "quitButtonController.h"
#include "startMenu.h"
#include "handShakingFSM.h"
#include "netwEvGenerator.h"
#include "netwEmisor.h"
#include "playingFSM.h"
#include "EDAInputController.h"
#include "EDANetworkingController.h"
#include "connectionEstablisher.h"
#include "timerEventGenerator.h"


enum implStates : stateTypes { START_MENU, WAITING_CONNECTION, HANDSHAKING, PLAYING, REMATCH, WAITING_TO_QUIT };

class bossFSM : public genericFSM
{


private:

#define TX(x) (static_cast<void (genericFSM::* )(genericEvent *)>(&bossFSM::x)) //casteo a funcion, por visual

	const fsmCell fsmTable[6][7] = {
	//	   INPUT_EVENT								DONE_EV								OUT_EV	 								QUIT							CLOSE_DISPLAY								 NETWORKING_EVENT											TIMER_EVENT
	{ { START_MENU,TX(sendToStMnControllers)},{ WAITING_CONNECTION,TX(newEstablisher) },{ START_MENU,TX(stMnError) },			{ START_MENU,TX(closeStMn) },		{ START_MENU,TX(closeStMn) },		  { START_MENU,TX(doNothing) },				 { START_MENU,TX(refreshStMn) } },			//START_MENU
	{ { WAITING_CONNECTION,TX(sendQuitController)},{	 HANDSHAKING,TX(newHandshaking) },{ START_MENU,TX(newStMn1) },		{ START_MENU,TX(newStMn1) },		{ WAITING_CONNECTION,TX(closeWaiting) },{ WAITING_CONNECTION,TX(doNothing) },  { WAITING_CONNECTION,TX(sendTimerEv) } },			//WAITING_CONNECTION
	{ { HANDSHAKING,TX(sendQuitController) },		{ PLAYING,TX(newGame) },		  { START_MENU,TX(newStMn2) },{ WAITING_TO_QUIT,TX(finishHandshaking) },		  { HANDSHAKING,TX(closeHandshaking) },	{ HANDSHAKING,TX(sendToHandFSM) },	{ HANDSHAKING,TX(sendTimerEv) } },				//HANDSHAKING
	{ { PLAYING,TX(sendInputEv) },			{ REMATCH,TX(rematch) }, { START_MENU,TX(newStMn2) },	{ WAITING_TO_QUIT,TX(finishGame) },		  { PLAYING,TX(closeGame) },			  { PLAYING,TX(sendNetwEv) },					{ PLAYING,TX(sendTimerEvent) } },			//PLAYING
	{ { REMATCH,TX(sendInputEv) },			{ HANDSHAKING,TX(playAgain) }, { START_MENU,TX(dontPlayAgain) },	{ WAITING_TO_QUIT,TX(sendGameOver) },		{ REMATCH,TX(closeRematch) },						 { REMATCH,TX(parseNetwEv) },					{ REMATCH,TX(sendTimerEv) } },	//REMATCH
	{ { WAITING_TO_QUIT,TX(sendInputEv) },	{ START_MENU,TX(newStMn2) },		  { START_MENU,TX(newStMn2) },	{ WAITING_TO_QUIT,TX(doNothing) },		  { WAITING_TO_QUIT,TX(closeWaitingAck) },				{ START_MENU,TX(destroyAll) },			{ WAITING_TO_QUIT,TX(sendTimerEv) } }	//WAITING_TO_QUIT
	};

	//The action routines for the FSM

	void sendToStMnControllers(genericEvent * ev);
	void newEstablisher(genericEvent * ev);
	void stMnError(genericEvent * ev);
	void closeStMn(genericEvent * ev);
	void refreshStMn(genericEvent * ev);
	void sendQuitController(genericEvent * ev);
	void newHandshaking(genericEvent * ev);
	void newStMn1(genericEvent * ev);
	void newStMn2(genericEvent * ev);
	void closeWaiting(genericEvent * ev);
	void newGame(genericEvent * ev);
	void rematch(genericEvent * ev);
	void playAgain(genericEvent * ev);
	void dontPlayAgain(genericEvent * ev);
	void closeConnection(genericEvent * ev);
	void finishHandshaking(genericEvent * ev);
	void closeHandshaking(genericEvent * ev);
	void sendToHandFSM(genericEvent * ev);
	void sendTimerEv(genericEvent * ev);
	void sendTimerEvent(genericEvent * ev);
	void sendInputEv(genericEvent * ev);
	void finishGame(genericEvent * ev);
	void closeGame(genericEvent * ev);
	void closeWaitingAck(genericEvent * ev);
	void destroyAll(genericEvent * ev);
	void sendNetwEv(genericEvent * ev);
	void parseNetwEv(genericEvent * ev);
	void sendGameOver(genericEvent * ev);
	void closeRematch(genericEvent * ev);
	void doNothing(genericEvent * ev) {}

	graphicator * graficador;
	string name;

	mainEventGenerator playingFSMEvGen;
	quitButtonController * quitController;
	connectionEstablisher * establisher;
	handShakingFSM * handFSM;
	netwEventGenerator * netwReceiver;
	timerEventGenerator * answerTimer;
	netwEmisor * emisor;
	playingFSM * gameFSM;
	mainEventGenerator& evGen;

public:
	bossFSM(quitButtonController * qControl,connectionEstablisher * establish,mainEventGenerator * eventGen, netwEventGenerator * netwEvG, string name, timerEventGenerator * timeout);
};


