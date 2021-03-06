#include "bossFSM.h"
#include "bossFSMEvents.h"
#include "connectionEstablisher.h"
#include "handShakingServerFSM.h"
#include "handShakingClientFSM.h"
#include "waitingGame.h"
#include "gameGraphicator.h"
#include "messageDisplayer.h"
#include "rematchGraphicator.h"

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

bossFSM::bossFSM(quitButtonController * qControl, connectionEstablisher * establish, mainEventGenerator * eventGen, netwEventGenerator * netw,string name, timerEventGenerator * timeout) : evGen(*eventGen),genericFSM(&fsmTable[0][0], 6, 7, START_MENU)
{
	answerTimer = timeout;
	graficador = new startMenu;
	quitController = qControl;
	establisher = establish;
	netwReceiver = netw;
	this->name = name;
	if (!static_cast<startMenu *>(graficador)->getInitOk())
	{
		delete graficador;
		graficador = nullptr;
		fsmEvent = new closeDisplayEv;
	}
	fsmRematch = nullptr;
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
	evGen.attach(establisher);
	establisher->startConnecting();
	delete graficador;
	graficador = new waitingGame;
	if (static_cast<waitingGame *>(graficador)->getInitOk())
	{
		static_cast<waitingGame *>(graficador)->setMessage("Searching opponent...");
	}
	else
	{
		delete graficador;
		fsmEvent = new closeDisplayEv;
		graficador = nullptr;
	}
	quitController->toggleState();
}

void bossFSM::stMnError(genericEvent * ev)
{
	closeStMn(ev);
	/*if (ev->getType() == OUT_EV)
	{
		cout << "Error: " << static_cast<outEv *>(ev)->getDetail() << endl;
	}*/
}

void bossFSM::closeStMn(genericEvent * ev)
{
	delete graficador;
	graficador = nullptr;
	fsmEvent = new outEv;
}

void bossFSM::refreshStMn(genericEvent * ev)
{
	if (graficador != nullptr)
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
		handFSM = new handShakingServerFSM(name,emisor,answerTimer);
	}
	else
	{
		handFSM = new handShakingClientFSM(name,emisor,answerTimer);
	}
	evGen.detach(establisher);
	evGen.attach(handFSM);
	static_cast<waitingGame *>(graficador)->setMessage("Opponent found!\nPreparing game...");

	//crear/attachear/arrancar generador de eventos de timer de 2,5 minutos
}

void bossFSM::newStMn1(genericEvent * ev)
{
	delete graficador;
	graficador = new startMenu;		
	quitController->toggleState();
	if (handFSM != nullptr)
	{
		evGen.detach(handFSM);
		delete handFSM;
		handFSM = nullptr;
	}
	if (gameFSM != nullptr)
	{
		evGen.detach(gameFSM);
		delete gameFSM;
		gameFSM = nullptr;
	}
	if (!static_cast<startMenu *>(graficador)->getInitOk())
	{
		delete graficador;
		graficador = nullptr;
		fsmEvent = new closeDisplayEv;
	}
	establisher->stopConnection();
	answerTimer->stopTimer();
	if (emisor != nullptr)
	{
		delete emisor;
		emisor = nullptr;
	}
	/*if (ev->getType() == OUT_EV)
	{
		cout << "Error: " << static_cast<outEv *>(ev)->getDetail() << endl;
	}*/
}
void bossFSM::newStMn2(genericEvent * ev)
{
	newStMn1(ev);
	netwReceiver->setConnector(nullptr);
}

void bossFSM::closeWaiting(genericEvent * ev)
{
	delete graficador;
	graficador = nullptr;
	fsmEvent = new closeDisplayEv;
}


/*Crea la fsm de playing*/
void bossFSM::newGame(genericEvent * ev)
{
	delete graficador;
	graficador = new gameGraphicator;
	graficador->refresh();
	catanGameModel * temp = handFSM->getCatanGame();
	evGen.detach(handFSM);
	delete handFSM;
	handFSM = nullptr;
	bool iStart = temp->isPlayer1Playing();
	vector<EDAInputController *> playingFSMInpControllers;
	EDAInputController * controllerToAdd = nullptr;
	innerFSMEvGen.clear();
	for (int i = 0; i < 6; i++)
	{
		switch (i)
		{
		case 0:
			controllerToAdd = new inputActionButtonController(temp,emisor,answerTimer);	
			break;
		case 1:
			controllerToAdd = new inputCardsController(temp);
			break;
		case 2:
			controllerToAdd = new inputEdgeAndVertexController(temp);
			break;
		case 3:
			controllerToAdd = new inputHexagonController(temp,emisor, answerTimer);
			break;
		case 4:
			controllerToAdd = new inputStateController;
			break;
		case 5:
			controllerToAdd = new inputTickAndXController(temp,emisor, answerTimer);
			break;
		}
		innerFSMEvGen.attach(controllerToAdd);
		playingFSMInpControllers.push_back(controllerToAdd);
	}
	EDANetworkingController * netwControllerToAdd = nullptr;
	vector<EDANetworkingController *> playingFSMNetwControllers;
	for (int i = 0; i < 9; i++)
	{
		switch (i)
		{
		case 0:
			netwControllerToAdd = new netwBankTradeController(temp,emisor);
			break;
		case 1:
			netwControllerToAdd = new netwConstructionController(temp,emisor);
			break;
		case 2:
			netwControllerToAdd = new netwDicesController(temp);
			break;
		case 3:
			netwControllerToAdd = new netwOfferTradeController(temp);
			break;
		case 4:
			netwControllerToAdd = new netwRobberCardsController(temp,emisor);
			break;
		case 5:
			netwControllerToAdd = new netwYNController(temp);
			break;
		case 6:
			netwControllerToAdd = new netwAckController(temp);
			break;
		case 7:
			netwControllerToAdd = new EDANetworkingController;
			break;
		case 8:
			netwControllerToAdd = new netwRobberMoveController(temp, emisor);
			break;
		}
		innerFSMEvGen.attach(netwControllerToAdd);
		playingFSMNetwControllers.push_back(netwControllerToAdd);
	}
	gameFSM = new playingFSM(iStart, temp, playingFSMInpControllers, playingFSMNetwControllers, emisor, static_cast<gameGraphicator *>(graficador));
	evGen.attach(gameFSM);
}

void bossFSM::rematch(genericEvent * ev)
{
	evGen.detach(gameFSM);
	delete gameFSM;
	gameFSM = nullptr;
	delete graficador;
	graficador = new rematchGraphicator(static_cast<doneEv *>(ev)->iwon());
	innerFSMEvGen.clear();
	netwRematchController * netwControllerToAdd = new netwRematchController(emisor);
	inputRematchController * inpControllerToAdd = new inputRematchController(emisor);
	innerFSMEvGen.attach(netwControllerToAdd);
	innerFSMEvGen.attach(inpControllerToAdd);
	fsmRematch = new rematchFSM(static_cast<doneEv *>(ev)->iwon(),netwControllerToAdd , inpControllerToAdd, emisor, static_cast<rematchGraphicator *>(graficador));
	evGen.attach(fsmRematch);
}

void bossFSM::playAgain(genericEvent * ev)
{
	delete graficador;
	graficador = new waitingGame;
	if (fsmRematch->iWon())
	{
		handFSM = new handShakingServerFSM(name, emisor, answerTimer);
	}
	else
	{
		handFSM = new handShakingClientFSM(name, emisor, answerTimer);
	}
	evGen.detach(fsmRematch);
	delete fsmRematch;
	fsmRematch = nullptr;
	evGen.attach(handFSM);
	static_cast<waitingGame *>(graficador)->setMessage("Preparing game...");
}

void bossFSM::dontPlayAgain(genericEvent * ev)
{
	delete graficador;
	graficador = new startMenu;
	quitController->toggleState();
	evGen.detach(fsmRematch);
	delete fsmRematch;
	fsmRematch = nullptr;
	answerTimer->stopTimer();
	establisher->stopConnection();
	netwReceiver->setConnector(nullptr);
	emisor->setConnector(nullptr);
}

void bossFSM::sendRematchInput(genericEvent * ev)
{
	fsmRematch->sendToInputController(static_cast<inputEv *>(ev));
	if (static_cast<inputEv *>(ev)->getInputEvType() == INP_MOUSE_EVENT)
	{
		quitController->parseMouseEvent(static_cast<mouseEvent *>(ev));
	}
	else if (static_cast<inputEv *>(ev)->getInputEvType() == INP_KEYBOARD_EVENT)
	{
		quitController->parseKeyboardEvent(static_cast<keyboardEvent *>(ev));
	}
	rematchEv * evento = static_cast<rematchEv *>(innerFSMEvGen.getNextEvent());
	if (evento != nullptr)
	{
		fsmRematch->cycle(evento);
		delete evento;
	}
}

void bossFSM::sendRematchNetw(genericEvent * ev)
{
	fsmRematch->sendToNetwController(static_cast<networkingEv *>(ev));
	answerTimer->stopTimer();
	rematchEv * evento = static_cast<rematchEv *>(innerFSMEvGen.getNextEvent());
	if (evento != nullptr)
	{
		fsmRematch->cycle(evento);
		delete evento;
	}
}

void bossFSM::closeConnection(genericEvent * ev)
{
	delete graficador;
	graficador = nullptr;
	if (handFSM != nullptr)
	{
		evGen.detach(handFSM);
		delete handFSM;
		handFSM = nullptr;
	}
	if (gameFSM != nullptr)
	{
		evGen.detach(gameFSM);
		delete gameFSM;
		gameFSM = nullptr;
	}
	/*if (ev->getType() == OUT_EV)
	{
		cout << "Error: " << static_cast<outEv *>(ev)->getDetail() << endl;
	}*/
}

void bossFSM::finishHandshaking(genericEvent * ev)
{
	emisor->sendPackage(QUIT);
}

void bossFSM::closeHandshaking(genericEvent * ev)
{
	delete graficador;
	graficador = nullptr;
	fsmEvent = new outEv;
}

void bossFSM::sendToHandFSM(genericEvent * ev)
{
	string info2send = "";
	handShakingEv * evento = nullptr;
	if (static_cast<networkingEv *>(ev)->getHeader() == handFSM->getExpectedPackage())
	{
		switch (static_cast<networkingEv *>(ev)->getHeader())
		{
		case NAME_IS:
			info2send = static_cast<nameIsPckg *>(ev)->getName();
			break;
		case MAP_IS:
			info2send = static_cast<mapIsPckg *>(ev)->getMap();
			break;
		case CIRCULAR_TOKENS:
			info2send = static_cast<circTokensPckg *>(ev)->getTokens();
			break; 
		default:
			info2send += static_cast<networkingEv *>(ev)->getHeader();	//por las dudas, le manda el evento del que provenia
		}
		evento = new handShakingEv(true,info2send);
	}
	else if (handFSM->clientFSM())
	{
		list<networkingEventTypes> altPack = static_cast<handShakingClientFSM *>(handFSM)->getListOfAlternatePackages();
		for (auto x : altPack)
		{
			if (x == static_cast<networkingEv *>(ev)->getHeader())
			{
				info2send += static_cast<networkingEv *>(ev)->getHeader();
				evento = new handShakingEv(true, info2send);
				break;
			}
		}
		if (evento == nullptr)
		{
			evento = new handShakingEv(false);
		}
	}
	else
	{
		evento = new handShakingEv(false);
	}
	handFSM->cycle(evento);
	delete evento;
}

void bossFSM::sendTimerEv(genericEvent * ev)
{
	if (graficador != nullptr)
	{
		graficador->refresh();
	}
	
}

void bossFSM::sendTimerEvent(genericEvent * ev)
{
	playingFSMEvent * evento = static_cast<playingFSMEvent *>(innerFSMEvGen.getNextEvent());
	if (evento != nullptr)
	{
		gameFSM->cycle(evento);
		delete evento;
	}
	if (graficador != nullptr)
	{
		graficador->refresh();
	}
}


void bossFSM::sendInputEv(genericEvent * ev)
{
	if (gameFSM != nullptr)
	{
		gameFSM->sendToInputControllers(static_cast<inputEv *>(ev));
	}
	if(static_cast<inputEv *>(ev)->getInputEvType() == INP_MOUSE_EVENT)
	{
		quitController->parseMouseEvent(static_cast<mouseEvent *>(ev));
	}
	else if (static_cast<inputEv *>(ev)->getInputEvType() == INP_KEYBOARD_EVENT)
	{
		quitController->parseKeyboardEvent(static_cast<keyboardEvent *>(ev));
	}
	playingFSMEvent * evento = static_cast<playingFSMEvent *>(innerFSMEvGen.getNextEvent());
	if (evento != nullptr)
	{
		gameFSM->cycle(evento);
		delete evento;
	}
}

void bossFSM::finishGame(genericEvent * ev)
{
	emisor->sendPackage(QUIT);
	if (graficador != nullptr)
	{
		delete graficador;
	}
	graficador = new messageDisplayer;
	static_cast<messageDisplayer *>(graficador)->setMessage("Waiting to quit...");
}

void bossFSM::closeGame(genericEvent * ev)
{
	if (gameFSM != nullptr)
	{
		evGen.detach(gameFSM);
		delete gameFSM;
		gameFSM = nullptr;
		emisor->sendPackage(ERROR_PCKG);		//manda error para no tener que esperar el ACK y avisarle al oponente que se fue
	}

	fsmEvent = new outEv;
}

void bossFSM::closeWaitingAck(genericEvent * ev)
{
	destroyAll(ev);
	fsmEvent = new outEv;
}

void bossFSM::destroyAll(genericEvent * ev)
{
	if (gameFSM != nullptr)
	{
		evGen.detach(gameFSM);
		delete gameFSM;
		gameFSM = nullptr;
	}
	if (emisor != nullptr)
	{
		delete emisor;
		emisor = nullptr;
	}
	delete graficador;
	graficador = new startMenu;
	quitController->toggleState();
	answerTimer->stopTimer();
	establisher->stopConnection();
	netwReceiver->setConnector(nullptr);
}

void bossFSM::sendNetwEv(genericEvent * ev)
{
	gameFSM->sendToNetwControllers(static_cast<networkingEv *>(ev));
	answerTimer->stopTimer();
	playingFSMEvent * evento = static_cast<playingFSMEvent *>(innerFSMEvGen.getNextEvent());
	if (evento != nullptr)
	{
		gameFSM->cycle(evento);
		delete evento;
	}
}

void bossFSM::parseNetwEv(genericEvent * ev)
{
/*	switch(static_cast<networkingEv *>(ev)->getHeader())
	{
	case:
		break;
	case:
		break;
	case:
		break;
	}*/
}

void bossFSM::sendQuit(genericEvent * ev)
{
	evGen.detach(fsmRematch);
	delete fsmRematch;
	fsmRematch = nullptr;
	answerTimer->startTimer();
	emisor->sendPackage(QUIT);
}

void bossFSM::closeRematch(genericEvent * ev)
{
	delete graficador;
	evGen.detach(fsmRematch);
	delete fsmRematch;
	fsmRematch = nullptr;
	answerTimer->stopTimer();
	establisher->stopConnection();
	netwReceiver->setConnector(nullptr);
	delete emisor;
	emisor = nullptr;
	fsmEvent = new outEv;
}