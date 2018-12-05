#include "playingFSM.h"
#include "EDANetworkingController.h"
#include "EDAInputController.h"
#include "inputActionButtonController.h"
#include "inputCardsController.h"
#include "inputHexagonController.h"
#include "inputEdgeAndVertexController.h"
#include "inputTickAndXController.h"
#include "netwConstructionController.h"

using namespace std;

playingFSM::playingFSM(bool iStart, catanGameModel * game, std::vector<EDAInputController *> inputControllers, std::vector<EDANetworkingController *> networkingControllers) : genericFSM(&fsmTable[0][0], 8, 6, iStart ? MY_TURN : OPP_TURN), allInputControllers(inputControllers) , allNetworkingControllers(networkingControllers)
{
	robberfsm = nullptr;
	if (iStart)
	{
		currentInputControllers.push_back(getInputController(CTRL_EDGE_AND_VERTEX));

		currentInputControllers.push_back(getInputController(CTRL_ACTION_BUTTON)); //capaz este no vaya, solo el primero para los primeros roads y settlements

		//inputControllerList.push_back(new );
	}
	else
	{
		netwConstructionController * controllerToAdd = static_cast<netwConstructionController *>(getNetworkingController(CTRL_CONSTRUCTION));	//agrega un controller de networking que solo espera que le manden SETTLEMENT
		controllerToAdd->setExpectedPackage(SETTLEMENT);
		currentNetworkingControllers.push_back(controllerToAdd);
	}
}

/*ACTION ROUTINES FOR FSM*/

/*
void playingFSM::sendDices(genericEvent * ev)
{
	//mandarle dados al modelo, el modelo debe cambiar los recursos de cada jugador
	//if (!catanGame->dicesThrown(dices))	//si no gano
	//{
		expectedPackages.clear();
		expectedPackages = { SETTLEMENT, ROAD, CITY, BANK_TRADE, OFFER_TRADE , PASS};
	//}
	//else								//si con esos dados gano el otro
	//{
	//	fsmEvent = new doneEv; 
	//	mandar YOU_WON
	//	expectedeEvents = { PLAY_AGAIN, GAME_OVER };
	//}
}
*/

/*
void playingFSM::prepareMyRobber(genericEvent * ev)
{
	expectedPackages.clear();
	robberfsm = new myRobberFSM(WAIT_OPPONENT_ANSWER);
	if(catanGame->otherPlayer->cardsCount() > 7)
	{
		expectedPackages = {ROBBER_CARDS, ACK};
	}
	else
	{
		expectedPackages = {ACK};
	}
	
}
*/

/*
void playingFSM::prepareOppRobber(genericEvent * ev)		
{
	expectedPackages.clear();
	if(catanGame->myPlayer->cardsCount() > 7)
	{
		robberfsm = new oppRobberFSM(WAIT_MY_USER);
		expectedPackages = {ROBBER_CARDS, ROBBER_MOVE};
	}
	else if(catanGame->otherPlayer->cardsCount() > 7)
	{
		robberfsm = new oppRobberFSM(WAIT_OPPONENT);
		expectedPackages = {ROBBER_CARDS, ROBBER_MOVE};
	}
	else
	{
		robberfsm = new oppRobberFSM(WAIT_OPPONENT);
		expectedPackages = {ROBBER_MOVE};
	}	
	
}
*/


void playingFSM::passControllers(genericEvent * ev)
{
	currentInputControllers.clear();
	currentNetworkingControllers.clear();
	currentNetworkingControllers.push_back(getNetworkingController(CTRL_DICES));
}

void playingFSM::oppTurnControllers(genericEvent * ev)
{
	currentInputControllers.clear();
	currentNetworkingControllers.clear();
	EDANetworkingController * controllerToAdd = getNetworkingController(GENERIC_NETW_CONTROLLER);	//agrega un controller de networking que solo espera que le manden SETTLEMENT
	controllerToAdd->setExpectedPackage(PASS);
	currentNetworkingControllers.push_back(controllerToAdd);
	currentNetworkingControllers.push_back(getNetworkingController(CTRL_CONSTRUCTION));
	currentNetworkingControllers.push_back(getNetworkingController(CTRL_BANKTRADE));
	currentNetworkingControllers.push_back(getNetworkingController(CTRL_OFFERTRADE));
}

void playingFSM::tradeControllers(genericEvent * ev)
{
	currentInputControllers.clear();
	currentNetworkingControllers.clear();
	currentInputControllers.push_back(getInputController(CTRL_TICKANDX));

	inputTickAndXController * controllerToAdd = getInputController(CTRL_TICKANDX);	//agrega un controller de networking que solo espera que le manden SETTLEMENT
	controllerToAdd->set
	currentNetworkingControllers.push_back(controllerToAdd);


	currentInputControllers.push_back(getInputController(CTRL_CARDS));	//espera que el usuario seleccione las cartas

}

void playingFSM::buildControllers(genericEvent * ev)
{
}

void playingFSM::myRobberControllers(genericEvent * ev)
{
}

void playingFSM::error(genericEvent * ev)
{
	//ver si sigue igual lo de robber fsm
	/*if (robberfsm != nullptr)	
	{
		delete robberfsm;
	}*/
	fsmEvent = new outEv(static_cast<playingFSMEvent *>(ev)->getInfo());
	//destruir controllers
	//destruir todo lo que tenga que destruir
}

void playingFSM::myTurnControllers(genericEvent * ev)
{
}

void playingFSM::netwYNControllers(genericEvent * ev)
{
}

void playingFSM::oppRobberControllers(genericEvent * ev)
{
}

void playingFSM::waitingControllers(genericEvent * ev)
{
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

/*void playingFSM::sendToRobberFSM(genericEvent * ev)
{
	
	//robberfsm->cycle(static_cast<stay_ev *>(ev)->additionalEvent)
	
}*/

/*void playingFSM::sendTradeOffer(genericEvent * ev)
{
	expectedPackages.clear();
	//catanGame->tradeOffered(tradeOffer)
	
}*/

/*void playingFSM::sendAnswer(genericEvent * ev)
{

}*/

/*void playingFSM::changeTurn(genericEvent * ev)
{
	//avisar que cambio el turno
	//
}*/

/*void playingFSM::validate(genericEvent * ev)
{

}*/



oppRobberFSM::oppRobberFSM(stateTypes initState) : genericFSM(&fsmTable[0][0], 3, 2, initState)
{
	//expectedPackage = ? ; porque a priori no sabria si tengo que espara input por la seleccion de cartas o solo mandar ack y espera respuesta del otro
	//deberia arrancar en wait_user y que ahi me fij si tengo que descartar cartas o no
}

void oppRobberFSM::error(genericEvent * ev)
{
	fsmEvent = new unexpectedNetwEvent("Unexpected event during Robber state");
	//borrar lo que haya que borrar
}

void oppRobberFSM::savePackage(genericEvent * ev)	//manda robber cards o robber move del oponente al modelo
{
	if (ev->getHeader() == ROBBER_CARDS)
	{
		catanGameModel->discardOtherPlayer(static_cast<robberCardsPckg *>(ev)->getCards());
	}
	else if (ev->getHeader() == ROBBER_MOVE)
	{
		catanGame->robberMoved(static_cast<robberMovePckg *>(ev)->getNewRobberPos());
	}
}

void oppRobberFSM::sendMyCards(genericEvent * ev)
{
	//mandar robber cards propias al oponente
	new 
}




void myRobberFSM::savePackage(genericEvent * ev)		//manda al modelo ack o cantidad de cartas seleccionadas
{
	if (ev->getHeader() == ACK)
	{
		catanGameModel->otherPlayer->discardOtherPlayer("");
	}
	else if (ev->getHeader() == ROBBER_CARDS)
	{
		catanGameModel->otherPlayer->discardOtherPlayer(static_cast<robberCardsPckg *>(ev)->getCards());
	}
}

void myRobberFSM::checkMyMove(genericEvent * ev)
{
	//el modelo se va a encargar de habilitar o deshabilitar los controllers para seleccionar las cartas o el robber
	if (ev->getDescription() == ROBBER_SELECTED)	//esperar eventos de input
	{
		catanGame->myPlayer->robberMoved(ev->additionalInfo);
		packageToSend = ev;
	}
	else if (ev->getDescription() == CARD_SELECTED)
	{
		catanGame->myPlayer->selectCard(ev->additionalInfo);
		packageToSend = ev;
	}
}

void myRobberFSM::sendMyMove(genericEvent * ev)
{
	//podria checkear que el evento sea el tick y no ack....
	//mandar al empaquetador de paquetes el packageToSend presente y que este como tiene acceso al modelo vea la cantidad de cartas seleccionadas para poder armar el paquete
	if (packageToSend->getDescription() == ROBBER_MOVE)
	{
		//crear evento de "ok" para salir de robberFSM
		new robberMovePckg(packageToSend->additionalInfo);		//mando el paquete a la otra maquina
	}
	else if (packageToSend->getDescription() == ROBBER_CARDS)
	{
		new robberCardsPckg(packageToSend->additionalInfo);		//mando el paquete a la otra maquina
	}
}