#include "rematchFSM.h"
#include "bossFSMEvents.h"

rematchFSM::rematchFSM(bool iWon, netwRematchController * netwCont_, inputRematchController * inputCont_, netwEmisor * emisor_, rematchGraphicator * graficador_) :  genericFSM(&fsmTable[0][0], 2,2 ,iWon ? WAIT_INPUT: WAIT_NETW)
{
	iwon = iWon;
	netwCont = netwCont_;
	inputCont = inputCont_;
	emisor = emisor_;
	graficador = graficador_;
	if (iWon)
	{
		inputCont->expectEvent();
	}
	else
	{
		netwCont->expectEvent();
		netwCont->setPlayAgain(true);
	}
}

void rematchFSM::netwController(genericEvent * ev)
{
	if (iwon)
	{
		inputCont->dontExpectEvent();
		netwCont->expectEvent();
		graficador->toggleState();
		netwCont->setPlayAgain(true);
	}
	else
	{
		netwCont->dontExpectEvent();
		inputCont->dontExpectEvent();
		fsmEvent = new doneEv;
	}
}

void rematchFSM::inputController(genericEvent * ev)
{
	if (iwon)
	{
		netwCont->dontExpectEvent();
		inputCont->dontExpectEvent();
		fsmEvent = new doneEv;
	}
	else
	{
		netwCont->dontExpectEvent();
		inputCont->expectEvent();
		graficador->toggleState();
	}
}

void rematchFSM::waitAck(genericEvent * ev)
{
	inputCont->dontExpectEvent();
	netwCont->expectEvent();
	netwCont->setPlayAgain(false);
}

void rematchFSM::finish(genericEvent * ev)
{
	netwCont->dontExpectEvent();
	inputCont->dontExpectEvent();
	fsmEvent = new outEv;
}


void rematchFSM::sendToInputController(inputEv * input)
{
	if (input->getInputEvType() == INP_KEYBOARD_EVENT)
	{
		inputCont->parseKeyboardEvent(static_cast<keyboardEvent *>(input));
	}
	else if (input->getInputEvType() == INP_MOUSE_EVENT)
	{
		inputCont->parseMouseEvent(static_cast<mouseEvent *>(input));
	}
}

void rematchFSM::sendToNetwController(networkingEv * netwPackage)
{
	if (!netwCont->parseNetworkingEvent(netwPackage))
	{
		if (netwPackage->getHeader() == QUIT)
		{
			fsmEvent = new outEv("Opponent left game");
			emisor->sendPackage(ACK);
		}
		else if (netwPackage->getHeader() == ERROR_PCKG)
		{
			fsmEvent = new outEv("Opponent left after a communication error");
		}
		else
		{
			fsmEvent = new outEv("Unexpected networking package");
		}
	}
}

bool rematchFSM::iWon()
{
	return iwon;
}
