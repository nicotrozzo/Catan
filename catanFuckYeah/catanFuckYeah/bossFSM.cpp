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

#include "netwBankTradeController.h"
#include "netwAckController.h"
#include "netwConstructionController.h"
#include "netwDicesController.h"
#include "netwOfferTradeController.h"
#include "netwRobberCardsController.h"
#include "netwRobberMoveController.h"
#include "netwYNController.h"

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
	graficador = new gameGraphicator;
	catanGameModel * temp = handFSM->getCatanGame();
	delete handFSM;
	bool iStart = temp->isPlayer1Playing();
	vector<EDAInputController *> playingFSMInpControllers;
	EDAInputController * controllerToAdd;
	for (int i = 0; i < 6; i++)
	{
		switch (i)
		{
		case 0:
			controllerToAdd = new inputActionButtonController(temp);	//ALGUNOS VAN A NECESITAR EL EMISOR
			break;
		case 1:
			controllerToAdd = new inputCardsController(temp);
			break;
		case 2:
			controllerToAdd = new inputEdgeAndVertexController(temp);
			break;
		case 3:
			controllerToAdd = new inputHexagonController(temp);
			break;
		case 4:
			controllerToAdd = new inputStateController;
			break;
		case 5:
			controllerToAdd = new inputTickAndXController(temp);
			break;
		}
		playingFSMEvGen.attach(controllerToAdd);
		playingFSMInpControllers[i] = controllerToAdd;
	}
	EDANetworkingController * netwControllerToAdd;
	vector<EDANetworkingController *> playingFSMNetwControllers;
	for (int i = 0; i < 6; i++)
	{
		switch (i)
		{
		case 0:
			netwControllerToAdd = new netwBankTradeController(temp);
			break;
		case 1:
			netwControllerToAdd = new netwConstructionController(temp);
			break;
		case 2:
			netwControllerToAdd = new netwDicesController(temp);
			break;
		case 3:
			netwControllerToAdd = new netwOfferTradeController(temp);
			break;
		case 4:
			netwControllerToAdd = new netwRobberCardsController(temp);
			break;
		case 5:
			netwControllerToAdd = new netwYNController(temp);
			break;
		case 6:
			netwControllerToAdd = new netwAckController(temp);
			break;
		}
		playingFSMEvGen.attach(netwControllerToAdd);
		playingFSMNetwControllers[i] = netwControllerToAdd;
	}
	gameFSM = new playingFSM(iStart, temp, playingFSMInpControllers, playingFSMNetwControllers, emisor);
	evGen.attach(gameFSM);
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

void bossFSM::sendToHandFSM(genericEvent * ev)
{
	handShakingEv * evento = new handShakingEv(static_cast<networkingEv *>(ev)->getHeader() == handFSM->getExpectedPackage());
	handFSM->cycle(evento);
	delete evento;
}

void bossFSM::sendTimerEv(genericEvent * ev)
{
	if (static_cast<timerEv *>(ev)->refreshEvent())
	{
		graficador->refresh();
	}
	else	//si no es un evento de refresh de pantalla, es un error, emite un invalid event
	{
		handShakingEv * evento = new handShakingEv(false);
		handFSM->cycle(evento);
		delete evento;
	}
}


void bossFSM::sendInputEv(genericEvent * ev)
{
	gameFSM->sendToInputControllers(static_cast<inputEv *>(ev));
	if(static_cast<inputEv *>(ev)->getInputEvType() == INP_MOUSE_EVENT)
	{
		quitController->parseMouseEvent(static_cast<mouseEvent *>(ev));
	}
	else if (static_cast<inputEv *>(ev)->getInputEvType() == INP_KEYBOARD_EVENT)
	{
		quitController->parseKeyboardEvent(static_cast<keyboardEvent *>(ev));
	}
	playingFSMEvent * evento = static_cast<playingFSMEvent *>(playingFSMEvGen.getNextEvent());
	if (evento != nullptr)
	{
		gameFSM->cycle(evento);
		delete evento;
	}
}

void bossFSM::finishGame(genericEvent * ev)
{

	graficador = new messageDisplayer;
	static_cast<messageDisplayer *>(graficador)->setMessage("Esperando para salir...");
}

void bossFSM::closeGame(genericEvent * ev)
{
	fsmEvent = new outEv;
}

void bossFSM::destroyAll(genericEvent * ev)
{
	if (gameFSM != nullptr)
	{
		delete gameFSM;
	}
	if (emisor != nullptr)
	{
		delete emisor;
	}
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