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
	//	   INPUT_EVENT								DONE								OUT	 							QUIT							CLOSE_DISPLAY					 NETWORKING_EVENT							TIMER_EVENT
	{ { START_MENU,TX(sendToStartMenu)},{ WAITING_CONNECTION,TX(newEstablisher) },{ START_MENU,TX(stMnError) },		{ START_MENU,TX(endStMn) },		{ START_MENU,TX(endStMn) },		  { START_MENU,TX(doNothing) },				 { START_MENU,TX(refreshStMn) } },				//START_MENU
	{ { WAITING_CONNECTION,TX(sendToInnerFSM)},{ HANDSHAKING,TX(newHandshaking) },{ START_MENU,TX() },{ START_MENU,TX(verdsp) },			  { WAITING_CONNECTION,TX(end2) },{ WAITING_CONNECTION,TX(fijarsesierror) },{ WAITING_CONNECTION,TX(refresh) } },	//WAITING_CONNECTION
	{ { HANDSHAKING,TX(mandar) },		{ PLAYING,TX(verdespues) },			  { START_MENU,TX(verdespues) },{ WAITING_TO_QUIT,TX(verdsp) },		  { HANDSHAKING,TX(end2) },		  { HANDSHAKING,TX(mandar) },				{ HANDSHAKING,TX(mandar) } },			//HANDSHAKING
	{ { PLAYING,TX(mandar) },			{ REMATCH,TX(avisarquiengano) },	  { START_MENU,TX(verdesp) },	{ WAITING_TO_QUIT,TX(verdsp) },		  { PLAYING,TX(end2) },			  { PLAYING,TX(mandar) },					{ PLAYING,TX(mandar) } },				//PLAYING
	{ { REMATCH,TX(mandar) },			{ HANDSHAKING,TX(verdesp) },		  { START_MENU,TX(verdesp) },	{ WAITING_TO_QUIT,TX(mandogameover) },{ REMATCH,TX(end2) },			  { REMATCH,TX(mandar) },					{ REMATCH,TX(mandar) } },				//REMATCH
	{ { WAITING_TO_QUIT,TX(mandar) },	{ START_MENU,TX(xqllegoack) },		  { START_MENU,TX(xqerror) },	{ WAITING_TO_QUIT,TX(nada) },		  { WAITING_TO_QUIT,TX(end2) },	  { WAITING_TO_QUIT,TX(mandar) },			{ WAITING_TO_QUIT,TX(mandar) } }		//WAITING_TO_QUIT
	};

	//The action routines for the FSM

	void sendToStartMenu(genericEvent * ev);
	void newEstablisher(genericEvent * ev);
	void stMnError(genericEvent * ev);			//startMenuError
	void endStMn(genericEvent * ev);
	void refreshStMn(genericEvent * ev);
	void sendToInnerFSM(genericEvent * ev);
	void newHandshaking(genericEvent * ev);
	void(genericEvent * ev);
	void(genericEvent * ev);
	void(genericEvent * ev);
	void(genericEvent * ev);
	void doNothing(genericEvent * ev) {}

	genericFSM * innerFSM;
public:
	bossFSM();	//crear fsm chica, display (en fsm chica), atachear fsm chica como fuente de eventos
};


