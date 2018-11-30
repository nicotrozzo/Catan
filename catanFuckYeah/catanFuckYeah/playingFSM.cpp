#include "playingFSM.h"


playingFSM::playingFSM(stateTypes initState) : genericFSM(&fsmTable[0][0], 8, 6, initState)
{
	expectedPackages = { DICES_ARE };
	robberfsm = nullptr;
}

/*ACTION ROUTINES FOR FSM*/

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

void playingFSM::prepareMyRobber(genericEvent * ev)
{
	expectedPackages.clear();
	robberfsm = new myRobberFSM(WAIT_OPPONENT_ANSWER);
	/*if(catanGame->otherPlayer->cardsCount() > 7)
	{
		expectedPackages = {ROBBER_CARDS, ACK};
	}
	else
	{
		expectedPackages = {ACK};
	}
	*/
}

void playingFSM::prepareOppRobber(genericEvent * ev)		
{
	expectedPackages.clear();
	/*if(catanGame->myPlayer->cardsCount() > 7)
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
	*/
}

void playingFSM::error(genericEvent * ev)
{
	if (robberfsm != nullptr)
	{
		delete robberfsm;
	}
	fsmEvent = new outEv("Unexpected networking event");
	expectedPackages.clear();
	//destruir todo lo que tenga que destruir
}

void playingFSM::sendToRobberFSM(genericEvent * ev)
{
	/*
	robberfsm->cycle(static_cast<stay_ev *>(ev)->additionalEvent)
	*/
}

void playingFSM::sendTradeOffer(genericEvent * ev)
{
	expectedPackages.clear();
	//catanGame->tradeOffered(tradeOffer)
	
}

void playingFSM::sendAnswer(genericEvent * ev)
{

}

void playingFSM::changeTurn(genericEvent * ev)
{
	//avisar que cambio el turno
	//
}

void playingFSM::validate(genericEvent * ev)
{

}

list<networkingEv> playingFSM::getExpectedPackages()
{
	return expectedPackages;
}


oppRobberFSM::oppRobberFSM(stateTypes initState) : genericFSM(&fsmTable[0][0], 3, 2, initState)
{

}

void oppRobberFSM::error(genericEvent * ev)
{
	fsmEvent = new unexpectedNetwEvent("Unexpected event during Robber state");
	//borrar lo que haya que borrar
}

void oppRobberFSM::saveCards(genericEvent * ev)
{
	//mandar robber cards del oponente al modelo
}

void oppRobberFSM::sendCardsToOpponent(genericEvent * ev)
{
	//mandar robber cards propias al oponente
}

void oppRobberFSM::moveRobber(genericEvent * ev)
{
	//mandar robber move al modelo
}



void myRobberFSM::savePackage(genericEvent * ev)		//manda al modelo ack o cantidad de cartas seleccionadas
{
	if (ev->getDescription() == ACK)
	{
		catanGame->otherPlayer->cardsSelected(0);
	}
	else if (ev->getDescription() == ROBBER_CARDS)
	{
		catanGame->otherPlayer->cardsSelected(ver como devuelve el unwrapper la cantidad de cartas seleccionadas);
	}
}

void myRobberFSM::checkMyMove(genericEvent * ev)
{
	//el modelo se va a encargar de habilitar o deshabilitar los controllers para seleccionar las cartas o el robber
	if (ev->getDescription() == ROBBER_SELECTED)
	{
		catanGame->myPlayer->changeRobberPosition(ev->additionalInfo);
		packageToSend = ROBBER_MOVE;
	}
	else if (ev->getDescription() == CARD_SELECTED)
	{
		catanGame->myPlayer->selectCard(ev->additionalInfo);
		packageToSend = ROBBER_CARDS;
	}
}

void myRobberFSM::sendMyMove(genericEvent * ev)
{
	//mandar al empaquetador de paquetes el packageToSend presente y que este como tiene acceso al modelo vea la cantidad de cartas seleccionadas para poder armar el paquete
	if (packageToSend == ROBBER_MOVE)
	{
		//crear evento de "done" para salir de robberFSM
	}
}