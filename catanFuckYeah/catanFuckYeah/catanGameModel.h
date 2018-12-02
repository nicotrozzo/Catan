#pragma once
#include "EDASubject.h"
#include "bossFSMEvents.h"
#include "catanMapModel.h"
#include "catanPlayerModel.h"
#include "gameDefines.h"

class catanGameModel : public EDASubject
{
public:
	catanGameModel();
	bool dicesThrown(unsigned int diceValue);	//modifica informacion del juego, cambia de turno
	bool construction(networkingEventTypes type, string coords);				//devuelve false si la construccion no es valida, PUEDE MODIFICAR GAME OVER
	bool playersTrade(string currentPlayerCards, string otherPlayerCards);		//devuelve false con trueque invalido
	bool validSelectedCards(string currentPlayerCards, string otherPlayerCards);		//checkea que la transaccion solicitada sea valida, en cuyo case devuelve true
	bool bankTrade(string player, unsigned char  bankResource);		//devuelve false si la transaccion es invalida (ver lo de 2x1 y 3x1)
	bool robberMoved(unsigned char hex);	//devuelve false si el lugar no es valido 
	bool discardCurrentPlayer(string cards);	//devuelve false si era una cantidad invalida de cartas, o no tenia esas cartas
	bool discardOtherPlayer(string cards);		//devuelve false si era una cantidad invalida de cartas, o no tenia esas cartas

	//bool waitingAccept();
	//bool waitingCards();
	catanPlayerModel getCurrentPlayer();
	catanPlayerModel getOtherPlayer();
	bool gameOver();	//true si termino el juego, llamar despues de construccion!!!!!!!!(pregunta a cada jugador cuantos puntos tiene)
	~catanGameModel();
protected:
	//bool waitingCards;
	//bool waitingToAccept;
	bool player1Playing;	//true si es el turno del jugador 1, false si es el turno del jugador 2
	catanPlayerModel player1;
	catanPlayerModel player2;
	catanMapModel map;
};


/*SOLO LO TIENE FSM DE HANSHAKING*/
class catanGameModelSetup : public catanGameModel
{
public:
	setMyName(string name) { player1.setName(name); }
	setOppName(string name) { player2.setName(name); }
	void setMap(string map_) { map.setMap(map_); };
	string getMap() { return map.getMap(); }
	string getCircularTokens() { return map.getCircularTokens(); };
	setStartingPlayer(char player);
};



