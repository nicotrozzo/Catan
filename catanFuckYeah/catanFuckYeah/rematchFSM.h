#pragma once
#include "genericFSM.h"
#include "netwRematchController.h"
#include "inputRematchController.h"
#include "netwEmisor.h"
#include "rematchGraphicator.h"

enum rematchStates : stateTypes {WAIT_INPUT, WAIT_NETW };

enum rematchEvTypes : eventTypes { CHANGE,END };

class rematchEv : public genericEvent
{
public:
	rematchEv(rematchEvTypes type_) : type(type_) {}
	eventTypes getType() { return type; }
private:
	rematchEvTypes type;
};

class rematchFSM :	public genericFSM
{


private:

#define TX(x) (static_cast<void (genericFSM::* )(genericEvent *)>(&rematchFSM::x)) //casteo a funcion, por visual

	const fsmCell fsmTable[2][2] = {
	//			CHANGE						 	END
	{ { WAIT_NETW, TX(netwController) },{ WAIT_NETW,TX(waitAck) } },		//WAIT_INPUT		
	{ { WAIT_INPUT,TX(inputController) },{ WAIT_NETW,TX(finish) } }		//WAIT_NETW
	};

	//The action routines for the FSM
	void netwController(genericEvent * ev);
	void inputController(genericEvent * ev);
	void waitAck(genericEvent * ev);
	void finish(genericEvent * ev);

	netwRematchController * netwCont;
	inputRematchController * inputCont;
	netwEmisor * emisor;
	rematchGraphicator * graficador;
	bool iwon;
public:
	rematchFSM(bool iWon, netwRematchController * netwCont_, inputRematchController * inputCont_, netwEmisor * emisor_, rematchGraphicator * graficador_);
	void sendToInputController(inputEv *input);
	void sendToNetwController(networkingEv *netwPackage);
	bool iWon();
};

