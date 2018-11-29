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

void playingFSM::prepareRobber(genericEvent * ev)		//VER DE QUE ACA PIDA ELEGIR LAS CARTAS A DESCARTAR ¿Y DONDE COLOCAR EL ROBBER?
{
	expectedPackages.clear();
	expectedPackages = {ROBBER_CARDS, ROBBER_MOVE};
	/*if(catanGame->myplayer->cardsCount() > 7)
	{
		robberfsm = new myRobberFSM(WAIT_OPPCARDS);
	}
	else if(catanGame->otherplayer->cardsCount() > 7)
	{
		robberfsm = new robberFSM(WAIT_ROBBCARDS);
	}
	else
	{
		robberfsm = new robberFSM(WAIT_ROBBMOVE);
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

void oppRobberFSM::sendCards(genericEvent * ev)
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
