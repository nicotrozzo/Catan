#include "playingFSM.h"
#include "EDANetworkingController.h"
#include "EDAInputController.h"
#include "inputActionButtonController.h"
#include "inputCardsController.h"
#include "inputHexagonController.h"
#include "inputEdgeAndVertexController.h"
#include "inputTickAndXController.h"
#include "inputStateController.h"
#include "netwConstructionController.h"
#include "netwAckController.h"
#include "netwBankTradeController.h"
#include "gameModelViewer.h"
#include "mapViewer.h"
#include "player1Viewer.h"
#include "player2Viewer.h"

using namespace std;


playingFSM::playingFSM(bool iStart, catanGameModel * game, std::vector<EDAInputController *> inputControllers, std::vector<EDANetworkingController *> networkingControllers, netwEmisor * em, gameGraphicator * messageDisp_) : genericFSM(&fsmTable[0][0], 8, 5, iStart ? MY_TURN : OPP_TURN), allInputControllers(inputControllers) , allNetworkingControllers(networkingControllers)
{
	gameModel = game;
	emisor = em;
	messageDisp = messageDisp_;
	mapView = new mapViewer(game->getMap());
	gameModel->attach(mapView);
	gameViewer = new gameModelViewer(game);
	gameModel->attach(gameViewer);
	if (iStart)
	{
		currentInputControllers.push_back(getInputController(CTRL_EDGE_AND_VERTEX));

		currentInputControllers.push_back(getInputController(CTRL_ACTION_BUTTON)); //capaz este no vaya, solo el primero para los primeros roads y settlements

		p1view = new player1Viewer(gameModel->getCurrentPlayer());
		gameModel->attach(p1view);
		p2view = new player2Viewer(gameModel->getOtherPlayer());
		gameModel->attach(p2view);
	}
	else
	{
		currentNetworkingControllers.push_back(static_cast<netwConstructionController *>(getNetworkingController(CTRL_CONSTRUCTION)));
		EDANetworkingController * controllerToAdd = getNetworkingController(GENERIC_NETW_CONTROLLER);	//agrega un controller de networking que solo espera que le manden PASS
		controllerToAdd->setExpectedPackage(PASS);
		currentNetworkingControllers.push_back(controllerToAdd);
		p2view = new player2Viewer(gameModel->getCurrentPlayer());
		gameModel->attach(p2view);
		p1view = new player1Viewer(gameModel->getOtherPlayer());
		gameModel->attach(p1view);
	}
	if (!p1view->getInitOk() || !p2view->getInitOk() || !gameViewer->getInitOk() || !mapView->getInitOk())
	{
		fsmEvent = new outEv("Error en la inicializacion de los graficos del juego");
	}
	else
	{
		gameModel->notify();
	}
}

void playingFSM::sendToInputControllers(inputEv * input)
{
	bool read = false;
	for (auto x : currentInputControllers)
	{
		if (input->getInputEvType() == INP_MOUSE_EVENT)
		{
			read = x->parseMouseEvent(static_cast<mouseEvent *>(input));
		}
		else if (input->getInputEvType() == INP_KEYBOARD_EVENT)
		{
			read = x->parseKeyboardEvent(static_cast<keyboardEvent *>(input));
		}
		if (read)	//si a un controller le sirvio el evento, no le servira a ningun otro
		{
			break;
		}
	}
}

void playingFSM::sendToNetwControllers(networkingEv * netwPackage)
{
	bool read = false;
	for (auto x : currentNetworkingControllers)
	{
		read = x->parseNetworkingEvent(netwPackage);
		if (read)
		{
			break;
		}
	}
	if (netwPackage->getHeader() == QUIT)
	{
		emisor->sendPackage(ACK);
		fsmEvent = new outEv("Opponent left game");
	}
	else if (netwPackage->getHeader() == ERROR_PCKG)
	{
		fsmEvent = new outEv("Opponent left game after a communication error");
	}
	else if (!read)
	{
		string errMessage = "Unexpected network event. Header: ";
		errMessage += netwPackage->getHeader();
		fsmEvent = new outEv(errMessage);
		emisor->sendPackage(ERROR_PCKG);
	}
}

playingFSM::~playingFSM()
{
	for (auto x : allInputControllers)
	{
		delete x;
	}
	for (auto x : allNetworkingControllers)
	{
		delete x;
	}
	allInputControllers.clear();
	allNetworkingControllers.clear();
	gameModel->detach(gameViewer);
	gameModel->detach(mapView);
	gameModel->detach(p1view);
	gameModel->detach(p2view);
	delete gameViewer;
	delete mapView;
	delete p1view;
	delete p2view;
}

/*ACTION ROUTINES FOR FSM*/

void playingFSM::passControllers(genericEvent * ev)
{
	currentInputControllers.clear();
	currentNetworkingControllers.clear();
	if (gameModel->initState())
	{
		gameModel->dicesThrown(0, 0);
		inputStateController *controllerToAdd = static_cast<inputStateController *>(getInputController(CTRL_STATE));
		controllerToAdd->setEv(CHANGE_STATE);
		currentInputControllers.push_back(controllerToAdd);
	}
	else
	{
		currentNetworkingControllers.push_back(getNetworkingController(CTRL_DICES));
	}
}

void playingFSM::oppTurnControllers(genericEvent * ev)
{
	currentInputControllers.clear();
	currentNetworkingControllers.clear();
	currentNetworkingControllers.push_back(getNetworkingController(CTRL_CONSTRUCTION));
	if (!gameModel->initState())
	{
		EDANetworkingController * controllerToAdd = getNetworkingController(GENERIC_NETW_CONTROLLER);	//agrega un controller de networking que solo espera que le manden PASS
		controllerToAdd->setExpectedPackage(PASS);
		currentNetworkingControllers.push_back(controllerToAdd);
		currentNetworkingControllers.push_back(getNetworkingController(CTRL_BANKTRADE));
		currentNetworkingControllers.push_back(getNetworkingController(CTRL_OFFERTRADE));
		messageDisp->setMessage(static_cast<playingFSMEvent *>(ev)->getMessage());
	}
}

void playingFSM::tradeControllers(genericEvent * ev)
{
	currentInputControllers.clear();
	currentNetworkingControllers.clear();
	currentInputControllers.push_back(getInputController(CTRL_TICKANDX));

	inputTickAndXController * controllerToAdd = static_cast<inputTickAndXController*>(getInputController(CTRL_TICKANDX));	//agrega un controller de networking que solo espera que le manden SETTLEMENT
	inputCardsController * cardsControllerToAdd = static_cast<inputCardsController*>(getInputController(CTRL_CARDS));
	if (!static_cast<playingFSMCardsEv *>(ev)->isOfferTrade())
	{
		controllerToAdd->setActionToDo(TICK_BANK_TRADE);
		cardsControllerToAdd->setFunction(BANK_TRADE);
		messageDisp->setMessage("             Prepare your bank trade");
	}
	else
	{
		controllerToAdd->setActionToDo(TICK_OWN_TRADE);
		cardsControllerToAdd->setFunction(OFFER_TRADE);
		messageDisp->setMessage("             Prepare your trade offer");
	}
	currentInputControllers.push_back(controllerToAdd);
	currentInputControllers.push_back(cardsControllerToAdd);	//espera que el usuario seleccione las cartas

}

void playingFSM::buildControllers(genericEvent * ev)
{
	currentInputControllers.clear();
	currentNetworkingControllers.clear();
	inputTickAndXController * controllerToAdd = static_cast<inputTickAndXController *>(getInputController(CTRL_TICKANDX));
	controllerToAdd->setActionToDo(TICK_BUILD);
	currentInputControllers.push_back(controllerToAdd);
	currentInputControllers.push_back(getInputController(CTRL_EDGE_AND_VERTEX));
	messageDisp->setMessage(static_cast<playingFSMEvent *>(ev)->getMessage());
}

void playingFSM::myRobberControllers(genericEvent * ev)
{
	if (gameModel->getOtherPlayer()->getAmountOfCards() > 7)	//si el otro jugador tiene que mandar sus robberCards
	{
		currentNetworkingControllers.push_back(getNetworkingController(CTRL_ROBBERCARDS));
		messageDisp->setMessage("             Waiting opponent to discard");
	}
	else
	{
		netwAckController * controllerToAdd = static_cast<netwAckController *>(getNetworkingController(CTRL_ACK));
		controllerToAdd->setAction(DICES_CASE);
		currentNetworkingControllers.push_back(controllerToAdd);
	}
}

void playingFSM::robbCardsReady(genericEvent * ev)
{
	currentInputControllers.clear();
	currentNetworkingControllers.clear();
	netwAckController * controllerToAdd = static_cast<netwAckController *>(getNetworkingController(CTRL_ACK));
	controllerToAdd->setAction(ROBBER_CARDS_CASE);
	currentNetworkingControllers.push_back(controllerToAdd);
}

void playingFSM::myCardsSent(genericEvent * ev)
{
	if (gameModel->getCurrentPlayer()->getAmountOfCards() > 7)
	{
		currentNetworkingControllers.push_back(getNetworkingController(CTRL_ROBBERCARDS));
		messageDisp->setMessage("                Waiting opponent to discard");
	}
	else
	{
		currentNetworkingControllers.push_back(getNetworkingController(CTRL_ROBBERMOVE));
		messageDisp->setMessage("         Waiting opponent to move the robber");
	}
}

void playingFSM::prepareRobbMove(genericEvent * ev)
{
	currentInputControllers.clear();
	currentNetworkingControllers.clear();
	myRobberMove();
}

void playingFSM::waitRobbMove(genericEvent * ev)
{
	currentNetworkingControllers.push_back(getNetworkingController(CTRL_ROBBERMOVE));
	messageDisp->setMessage("             Waiting opponent to move the robber");
	emisor->sendPackage(ACK);
}

void playingFSM::error(genericEvent * ev)
{
	fsmEvent = new outEv(static_cast<playingFSMEvent *>(ev)->getMessage());
	//destruir todo lo que tenga que destruir
}

void playingFSM::myTurnControllers(genericEvent * ev)
{
	currentNetworkingControllers.clear();
	currentInputControllers.clear();
	currentInputControllers.push_back(getInputController(CTRL_EDGE_AND_VERTEX));
	if (!gameModel->initState())
	{
		currentInputControllers.push_back(getInputController(CTRL_ACTION_BUTTON));
	}
	messageDisp->setMessage(static_cast<playingFSMEvent *>(ev)->getMessage());
}

void playingFSM::finishedBuilding(genericEvent * ev)
{
	currentInputControllers.clear();
	currentNetworkingControllers.clear();
	if (gameModel->initState() && !gameModel->hasToConstruct())
	{
		inputStateController *controllerToAdd = static_cast<inputStateController *>(getInputController(CTRL_STATE));
		controllerToAdd->setEv(CHANGE_STATE);
		currentInputControllers.push_back(controllerToAdd);
	}
	else if (gameModel->mustThrowDices())	//si acaba de salir del estado inicial
	{
		unsigned int dice1 = rand() % 6 + 1;
		unsigned int dice2 = rand() % 6 + 1;
		string info2send;
		info2send += dice1 + '0';
		info2send += dice2 + '0';
		emisor->sendPackage(DICES_ARE, info2send);
		if (gameModel->dicesThrown(dice1, dice2))
		{
			myTurnControllers(ev);
		}
		else
		{
			inputStateController *controllerToAdd = static_cast<inputStateController *>(getInputController(CTRL_STATE));
			controllerToAdd->setEv(ROBBER_EV);
			currentInputControllers.push_back(controllerToAdd);
			myRobberControllers(ev);
		}
	}
	else if(!gameModel->gameOver())
	{
		myTurnControllers(ev);
	}
	else
	{
		fsmEvent = new doneEv(true);
	}
}

void playingFSM::netwYNControllers(genericEvent * ev)
{
	currentNetworkingControllers.clear();
	currentInputControllers.clear();
	currentNetworkingControllers.push_back(getNetworkingController(CTRL_YN));	
	messageDisp->setMessage("                 Waiting opponent's answer");
}

void playingFSM::ackController(genericEvent * ev)
{
	currentNetworkingControllers.clear();
	currentInputControllers.clear();
	messageDisp->setMessage("");
	if (!gameModel->gameOver())
	{
		netwAckController * controllerToAdd = static_cast<netwAckController *>(getNetworkingController(CTRL_ACK));
		controllerToAdd->setAction(OTHER_CASE);
		currentNetworkingControllers.push_back(controllerToAdd);
	}
	else
	{
		EDANetworkingController * controllerToAdd = getNetworkingController(GENERIC_NETW_CONTROLLER);	//agrega un controller de networking que solo espera que le manden PASS
		controllerToAdd->setExpectedPackage(YOU_WON);
		currentNetworkingControllers.push_back(controllerToAdd);
	}
}

void playingFSM::dicesController(genericEvent * ev)
{
	currentInputControllers.clear();
	currentNetworkingControllers.clear();
	currentNetworkingControllers.push_back(getNetworkingController(CTRL_DICES));
}



void playingFSM::oppCardsReady(genericEvent * ev)
{
	currentNetworkingControllers.clear();
	currentInputControllers.clear();
	if (gameModel->getCurrentPlayer()->getAmountOfCards() > 7)
	{
		myRobberCards();
	}
	else
	{
		myRobberMove();
	}
}

void playingFSM::myTurnPassControllers(genericEvent * ev)
{
	currentInputControllers.clear();
	currentNetworkingControllers.clear();	
	if(gameModel->initState())
	{
		myTurnControllers(ev);
		gameModel->dicesThrown(0, 0);	//cambia de turno
	}
	else if (gameModel->gameOver())
	{
		fsmEvent = new doneEv(false);
	}
	else
	{
		unsigned int dice1 = rand() % 6 + 1;
		unsigned int dice2 = rand() % 6 + 1;
		string info2send;
		info2send += dice1 + '0';
		info2send += dice2 + '0';
		emisor->sendPackage(DICES_ARE, info2send);
		if (gameModel->dicesThrown(dice1, dice2))
		{
			myTurnControllers(ev);
		}
		else
		{
			inputStateController *controllerToAdd = static_cast<inputStateController *>(getInputController(CTRL_STATE));
			controllerToAdd->setEv(ROBBER_EV);
			currentInputControllers.push_back(controllerToAdd);
			myRobberControllers(ev);
		}
	}
}

void playingFSM::oppRobberControllers(genericEvent * ev)
{
	currentInputControllers.clear();
	currentNetworkingControllers.clear();
	if (gameModel->getOtherPlayer()->getAmountOfCards() > 7)	//si el jugador propio (other player xq no es su turno) tiene mas de 7 cartas, se tiene que descartar
	{
		myRobberCards();
	}
	else if(gameModel->getCurrentPlayer()->getAmountOfCards() > 7)
	{
		currentNetworkingControllers.push_back(getNetworkingController(CTRL_ROBBERCARDS));
		messageDisp->setMessage("                 Waiting opponent to discard");
		emisor->sendPackage(ACK);
	}
	else
	{
		currentNetworkingControllers.push_back(getNetworkingController(CTRL_ROBBERMOVE));
		messageDisp->setMessage("        Waiting opponent to move the robber");
		emisor->sendPackage(ACK);
	}
}

void playingFSM::waitingControllers(genericEvent * ev)
{
	currentNetworkingControllers.clear();
	currentInputControllers.clear();
	inputTickAndXController * controllerToAdd = static_cast<inputTickAndXController *>(getInputController(CTRL_TICKANDX));
	if (!static_cast<playingFSMEvent *>(ev)->getError())
	{
		controllerToAdd->setActionToDo(TICK_OPP_TRADE);
	}
	else	//si llego un trade invalido porque el jugador propio no tenia los recursos
	{
		controllerToAdd->setActionToDo(TICK_INVALID_TRADE);
	}
	messageDisp->setMessage(static_cast<playingFSMEvent *>(ev)->getMessage());
	currentInputControllers.push_back(controllerToAdd);
}

/*Devuelve el controller pedido si esta presente en la lista de todos los controllers de input, sino nullptr*/
EDAInputController * playingFSM::getInputController(inputControllerTypes type)
{
	EDAInputController * ret = nullptr;
	for (auto temp : allInputControllers)
	{
		if(temp->getType() == type)
		{
			ret = temp;
			break;
		}
	}
	return ret;
}

/*Devuelve el controller pedido si esta presente en la lista de todos los controllers de networking, sino nullptr*/
EDANetworkingController * playingFSM::getNetworkingController(netwControllerTypes type)
{
	EDANetworkingController * ret = nullptr;
	for (auto temp : allNetworkingControllers)
	{
		if (temp->getType() == type)
		{
			ret = temp;
			break;
		}
	}
	return ret;
}

void playingFSM::myRobberCards()
{
	EDAInputController * controllerToAdd = getInputController(CTRL_CARDS);
	static_cast<inputCardsController *>(controllerToAdd)->setFunction(ROBBER_CARDS);	//le avisa al controller que espera cartas de robber
	currentInputControllers.push_back(controllerToAdd);	//espera cartas
	messageDisp->setMessage("                  Choose cards to discard");
	controllerToAdd = getInputController(CTRL_TICKANDX);
	static_cast<inputTickAndXController *>(controllerToAdd)->setActionToDo(TICK_ROBB_CARDS);
	currentInputControllers.push_back(controllerToAdd);
	gameModel->prepareRobberDiscard(DESSERT);	//empieza a seleccionar
}


void playingFSM::myRobberMove()
{
	netwAckController * controllerToAdd = static_cast<netwAckController *>(getNetworkingController(CTRL_ACK));
	controllerToAdd->setAction(OTHER_CASE);
	currentNetworkingControllers.push_back(controllerToAdd);
	currentInputControllers.push_back(getInputController(CTRL_HEXAGON));
	messageDisp->setMessage("                     Move the robber");
}


playingFSMEvent::playingFSMEvent(playingFSMEvTypes type_, string message_)
{ 
	type = type_; 
	error = false;
	message = message_;
}

playingFSMEvent::playingFSMEvent(playingFSMEvTypes type_, bool error_, string message_)
{
	type = type_; 
	error = error_;
	message = message_;
}

eventTypes playingFSMEvent::getType()
{
	return type;
}

string playingFSMEvent::getMessage()
{
	return message;
}

bool playingFSMEvent::getError()
{
	return error;
}
