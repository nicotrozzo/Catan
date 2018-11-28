#pragma once
#include <iostream>
#include "eventHandling.h"
#include "genericFSM.h"

enum implStates : stateTypes { START_MENU, WAITING_CONNECTION, HANDSHAKING, PLAYING, REMATCH, WAITING_TO_QUIT };

using namespace std;

class bossFSM : public genericFSM
{


private:

#define TX(x) (static_cast<void (genericFSM::* )(genericEvent *)>(&bossFSM::x)) //casteo a funcion, por visual

	const fsmCell fsmTable[6][7] = {
	//	   INPUT_EVENT								DONE								OUT	 								QUIT							CLOSE_DISPLAY					 NETWORKING_EVENT							TIMER_EVENT
	{ { START_MENU,TX(sendToStartMenu)},{ WAITING_CONNECTION,TX(newEstablisher) },{ START_MENU,TX(stMnError) },			{ START_MENU,TX(closeStMn) },		{ START_MENU,TX(closeStMn) },		  { START_MENU,TX(doNothing) },				 { START_MENU,TX(refreshStMn) } },				//START_MENU
	{ { WAITING_CONNECTION,TX(sendQuitController)},{ HANDSHAKING,TX(newHandshaking) },{ START_MENU,TX(newStMn) },		{ START_MENU,TX(newStMn) },		{ WAITING_CONNECTION,TX(closeWaiting) },{ WAITING_CONNECTION,TX(doNothing) },  { WAITING_CONNECTION,TX(refreshWait) } },	//WAITING_CONNECTION
	{ { HANDSHAKING,TX(sendQuitController) },		{ PLAYING,TX(newGame) },		  { START_MENU,TX(closeConnection) },{ WAITING_TO_QUIT,TX(finishHandshaking) },		  { HANDSHAKING,TX(closeHandshaking) },	{ HANDSHAKING,TX(sendToNetwFSM) },	{ HANDSHAKING,TX(sendTimerEv) } },			//HANDSHAKING
	{ { PLAYING,TX(sendInputEv) },			{ REMATCH,TX(verdesp) },		  { START_MENU,TX(closeConnection) },	{ WAITING_TO_QUIT,TX(finishGame) },		  { PLAYING,TX(closeGame) },			  { PLAYING,TX(sendNetwEv) },					{ PLAYING,TX(sendTimerEv) } },				//PLAYING
	{ { REMATCH,TX(sendInputEv) },			{ HANDSHAKING,TX(verdesp) },		  { START_MENU,TX(closeConnection) },	{ WAITING_TO_QUIT,TX(sendGameOver) },{ REMATCH,TX(closeRematch) },			  { REMATCH,TX(sendNetwEv) },					{ REMATCH,TX(sendTimerEv) } },				//REMATCH
	{ { WAITING_TO_QUIT,TX(sendInputEv) },	{ START_MENU,TX(newStMn) },		  { START_MENU,TX(newStMn) },	{ WAITING_TO_QUIT,TX(doNothing) },		  { WAITING_TO_QUIT,TX(close) },	  { WAITING_TO_QUIT,TX(sendNetwEv) },			{ WAITING_TO_QUIT,TX(sendTimerEv) } }		//WAITING_TO_QUIT
	};

	//The action routines for the FSM

	void sendToStartMenu(genericEvent * ev);
	void newEstablisher(genericEvent * ev);
	void stMnError(genericEvent * ev);			//startMenuError
	void closeStMn(genericEvent * ev);
	void refreshStMn(genericEvent * ev);
	void sendQuitController(genericEvent * ev);
	void newHandshaking(genericEvent * ev);
	void newStMn(genericEvent * ev);
	void closeWaiting(genericEvent * ev);
	void refreshWait(genericEvent * ev);
	void newGame(genericEvent * ev);
	void closeConnection(genericEvent * ev);
	void finishHandshaking(genericEvent * ev);
	void closeHandshaking(genericEvent * ev);
	void sendToNetwFSM(genericEvent * ev);
	void sendTimerEv(genericEvent * ev);
	void sendInputEv(genericEvent * ev);
	void finishGame(genericEvent * ev);
	void closeGame(genericEvent * ev);
	void sendNetwEv(genericEvent * ev);
	void sendGameOver(genericEvent * ev);
	void closeRematch(genericEvent * ev);
	void(genericEvent * ev);
	void(genericEvent * ev);
	void(genericEvent * ev);





	void doNothing(genericEvent * ev) {}

	genericFSM * innerFSM;
public:
	bossFSM();	//crear fsm chica, display (en fsm chica), atachear fsm chica como fuente de eventos
};


