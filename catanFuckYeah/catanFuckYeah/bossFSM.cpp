#include "bossFSM.h"
#include "bossFSMEvents.h"
#include "connectionEstablisher.h"
#include "handShakingFSM.h"
#include "waitingGame.h"

/*Para crear controllers de playingFSM*/
#include "inputActionButtonController.h"
#include "inputCardsController.h"
#include "inputEdgeAndVertexController.h"
#include "inputHexagonController.h"
#include "inputStateController.h"
#include "inputTickAndXController.h"
#include "input"

bossFSM::bossFSM(quitButtonController * qControl, connectionEstablisher * establish, mainEventGenerator * eventGen, netwEventGenerator * netw,string name) : evGen(*eventGen),genericFSM(&fsmTable[0][0], 6, 7, START_MENU)
{
	graficador = new startMenu;
	quitController = qControl;
	establisher = establish;
	netwReceiver = netw;
	this->name = name;
	if (!static_cast<startMenu *>(graficador)->getInitOk())
	{
		delete graficador;
		fsmEvent = new closeDisplayEv;
	}
}

/*Action routines*/
void bossFSM::sendToStMnControllers(genericEvent * ev)
{
	if (static_cast<inputEv *>(ev)->getInputEvType() == INP_MOUSE_EVENT)
	{
		quitController->parseMouseEvent(static_cast<mouseEvent *>(ev));
	}
	else if (static_cast<inputEv *>(ev)->getInputEvType() == INP_KEYBOARD_EVENT)
	{
		quitController->parseKeyboardEvent(static_cast<keyboardEvent *>(ev));
	}
}

void bossFSM::newEstablisher(genericEvent * ev)
{	
	delete graficador;
	graficador = new waitingGame;
	establisher->startConnecting();
	static_cast<waitingGame *>(graficador)->setMessage("Buscando oponente...");
	quitController->toggleState();
}

void bossFSM::stMnError(genericEvent * ev)
{
	closeStMn(ev);
}

void bossFSM::closeStMn(genericEvent * ev)
{
	delete graficador;
	fsmEvent = new outEv;
}

void bossFSM::refreshStMn(genericEvent * ev)
{
	if (static_cast<timerEv *>(ev)->refreshEvent())
	{
		graficador->refresh();
	}
}

void bossFSM::sendQuitController(genericEvent * ev)
{
	if (ev->getType() == INPUT_EVENT)
	{
		inputEv *inEvent = static_cast<inputEv *>(ev);
		if (inEvent->getInputEvType() == INP_MOUSE_EVENT)
		{
			mouseEvent * mEvent = static_cast<mouseEvent *>(inEvent);
			quitController->parseMouseEvent(mEvent);
		}
		else if (inEvent->getInputEvType() == INP_KEYBOARD_EVENT)
		{
			keyboardEvent * kEvent = static_cast<keyboardEvent *>(inEvent);
			quitController->parseKeyboardEvent(kEvent);
		}
	}
}

void bossFSM::newHandshaking(genericEvent * ev)
{
	connector * connect = establisher->getConnector();
	netwReceiver->setConnector(connect);
	emisor = new netwEmisor(connect);
	if (connect->getType() == SERVER)
	{
		handFSM = new handShakingServerFSM(name,emisor);
	}
	else
	{
		handFSM = new handShakingClientFSM(name,emisor);
	}
	evGen.detach(establisher);
	evGen.attach(handFSM);
	static_cast<waitingGame *>(graficador)->setMessage("Oponente encontrado.\nPreparando juego...");

	//crear/attachear/arrancar generador de eventos de timer de 2,5 minutos
}

void bossFSM::newStMn(genericEvent * ev)
{
	delete graficador;
	graficador = new startMenu;		
	quitController->toggleState();
	if (!static_cast<startMenu *>(graficador)->getInitOk())
	{
		delete graficador;
		fsmEvent = new closeDisplayEv;
	}
}

void bossFSM::closeWaiting(genericEvent * ev)
{
	delete graficador;
}

void bossFSM::refreshWait(genericEvent * ev)
{
	graficador->refresh();
}

/*Crea la fsm de playing*/
void bossFSM::newGame(genericEvent * ev)
{
	delete graficador;
	catanGameModel * temp = handFSM->getCatanGame();
	delete handFSM;
	bool iStart = temp->isPlayer1Playing();
	vector<EDAInputController *> playingFSMInpControllers;
	vector<EDAInputController *> playingFSMNetwControllers;
	playingFSMInpControllers.push_back(new )
	gameFSM = new playingFSM(iStart,temp,)
}

void bossFSM::closeConnection(genericEvent * ev)
{
	delete graficador;
}

void bossFSM::finishHandshaking(genericEvent * ev)
{
	fsmEvent = new outEv;
}

void bossFSM::closeHandshaking(genericEvent * ev)
{
	delete graficador;
}

void bossFSM::sendToNetwFSM(genericEvent * ev)
{
	//innerFSM->cycle(static_cast<networkingEv *>(ev)->getHeader()) //en realidad hay que mandarle todo el evento, capaz modificar el cycle de la fsm de handshaking para que haga getHeader en vez de getType
																//sino que el networking event tenga adentro otro evento con getType = getHeader;
}

void bossFSM::sendTimerEv(genericEvent * ev)
{
	//mandar al display de alguna forma si la fuente es allegro
	//mandar a fsm handshaking como evento invalido para que corte todo
}


void bossFSM::sendInputEv(genericEvent * ev)
{
	//ACA TIENE QUE ESTAR EL DISPATCHER PARA LA FSM DE PLAYING
	//innerFSM->cycle(static_cast<inputEv *>(ev)->additionalInfo);
	//quitController(static_cast<>); //mandar a quit controller si es mouse o Q, ver despues
}

void bossFSM::finishGame(genericEvent * ev)
{
	//avisar al juego que esta por salir?
}

void bossFSM::closeGame(genericEvent * ev)
{
	fsmEvent = new outEv;
}

void bossFSM::sendNetwEv(genericEvent * ev)
{
	//innerFSM->cycle(static_cast<networkingEv *>(ev)->additional);
}

void bossFSM::sendGameOver(genericEvent * ev)
{

}

void bossFSM::closeRematch(genericEvent * ev)
{
	fsmEvent = new outEv;
}

void bossFSM::(genericEvent * ev)
{

}