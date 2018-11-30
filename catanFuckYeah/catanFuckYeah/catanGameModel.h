#pragma once
#include "EDASubject.h"
#include "bossFSMEvents.h"

class catanGameModel : public EDASubject
{
public:
	catanGameModel();
	~catanGameModel();
	bool dicesThrown(unsigned int diceValue);	//modifica informacion del juego, cambia de turno
	bool construction(networkingEventTypes type, string coords);				//devuelve false si la construccion no es valida, PUEDE MODIFICAR GAME OVER
	bool playersTrade(string currentPlayerCards, string otherPlayerCards);		//devuelve false con trueque invalido
	bool bankTrade(string player, unsigned char  bankResource);		//devuelve false si la transaccion es invalida (ver lo de 2x1 y 3x1)
	bool robberMoved(unsigned char hex);	//devuelve false si el lugar no es valido 
	bool discardCurrentPlayer(string cards);	//devuelve false si era una cantidad invalida de cartas, o no tenia esas cartas
	bool discardOtherPlayer(string cards);		//devuelve false si era una cantidad invalida de cartas, o no tenia esas cartas

	//bool waitingAccept();
	//bool waitingCards();
	//catanPlayer getCurrentPlayer();
	//catanPlayer getOtherPlayer();
	bool gameOver();	//true si termino el juego, llamar despues de construccion!!!!!!!!
protected:
	//bool waitingCards;
	//bool waitingToAccept;
	catanPlayer player1;
	catanPlayer player2;
	catanMapModel map;
};

class catanGameModelSetter : public catanGameModel
{
public:
	setMyName(string name) {}
	setOppName(string name) { player2->setName(name); }
	
};