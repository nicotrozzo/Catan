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
	bool dicesThrown(unsigned char dice1, unsigned char dice2);	//modifica informacion del juego, cambia de turno
	
	
	bool validConstruction(networkingEventTypes type, string coords);	//devuelve true si la construccion solicitada es valida, y la almacena internamente hasta que le den la orden de construir
	bool construct();		//construye la ultima construccion que se haya validado, devuelve false si la construccion no es valida, PUEDE MODIFICAR GAME OVER
	void cancelConstruction();
	bool isConstructing();

	bool bankTrade(string playerResource, resourceType  bankResource);		//devuelve false si la transaccion es invalida (ver lo de 2x1 y 3x1)
	bool robberMoved(unsigned char hex);	//devuelve false y no cambia nada si el lugar no es valido 
	
	map<resourceType,unsigned char> getBankTradeCosts();	

	bool prepareRobberDiscard(resourceType resource); //Devuelve true si se podia seleccionar uno mas de dicho recurso
	bool robberCardsReady();
	void clearRobberCards();
	bool discardCurrentPlayer();				//devuelve false si era una cantidad invalida de cartas, o no tenia esas cartas
	bool discardPlayer2(string cards);		//devuelve false si era una cantidad invalida de cartas, o no tenia esas cartas
	

	networkingEventTypes isSelecting();	//devuelve 0 si no esta preparando un intercambio, OFFER_TRADE si esta preparando intercambio entre jugadores o BANK_TRADE si esta preparando intercambio con el banco
	void clearTrades();	//borra la informacion sobre intercambios pendientes que tenga el modelo MODIFICA EL MODELO
	
	/*preparePlayerTrade:
	*Recibe:
	-Primer parametro: recurso a incrementar
	-Segundo parametro: jugador cuyo recurso se quiere incrementar (1 o 2)
	*Funcionamiento: si se puede, incrementa el recurso pedido en 1 en los recursos seleccionados por el jugador solicitado para el intercambio
	Siempre incrementa el recurso del jugador 2 para que el usuario no pueda saber cuantos recursos tiene el jugador 2
	*Devuelve: false si se trato de incrementar un recurso DEL JUGADOR ACTUAL que no tenia.
	Si devuelve true, MODIFICA EL MODELO
	*/
	bool preparePlayerTrade(resourceType resource, unsigned char player);	//MODIFICA EL MODELO
	bool playerTradeReady();	//devuelve true si el intercambio con el jugador preparado esta listo
	bool playerTrade();
	
	bool playersTrade(string cardsPlayer1, string cardsPlayer2);		//Para el trade del contrario. devuelve false con trueque invalido


	/*prepareBankTrade:
	*Recibe:
	-Primer parametro: recurso a seleccionar
	-Segundo parametro: indica si se selecciona un recurso del banco o del jugador. True si es del jugador, false si es del banco
	*Funcionamiento: intenta seleccionar el recurso solicitado para el jugador o el banco. Si se selecciona un recurso del jugador y habia uno seleccionado del banco, este ultimo se borra
	Si se selecciona un recurso del jugador y ya habia un recurso seleccionado del jugador, pisa el anterior, lo mismo con recursos del banco.
	Si el jugador no dispone de los recursos suficientes, no hace nada.
	Si el jugador dispone de los recursos, selecciona la cantidad necesaria, segun los costos del jugador para el bank trade
	*Devuelve: true si selecciona el recurso, false si no*/
	bool prepareBankTrade(resourceType resource, bool player);	//MODIFICA EL MODELO	
	bool bankTradeReady();	//devuelve true si el intercambio con el banco preparado esta listo
	bool bankTrade();	//ejecuta el trade preparado, 
	
	cards getP1SelectedCardsForTrade() { return p1SelectedCardsForTrade; }
	cards getP2SelectedCardsForTrade() { return p2SelectedCardsForTrade; }
	cards getP1DiscardRobberCards() { return p1DiscardRobberCards; }
	resource_t getPlayerSelectedResource() { return playerSelectedResource; }
	resourceType getBankSelectedResource() { return bankSelectedResource; }

	bool isPlayer1Playing();	//devuelve true si es el turno del jugador 1
	catanPlayerModel *getCurrentPlayer();
	catanPlayerModel *getOtherPlayer();
	catanMapModel *getMap();
	unsigned char getDice1() { return dice1; }
	unsigned char getDice2() { return dice2; }
	bool gameOver();	//true si termino el juego, llamar despues de construccion!!!!!!!!(pregunta a cada jugador cuantos puntos tiene)
	void notify();
	~catanGameModel();
protected:
	bool player1Playing;	//true si es el turno del jugador 1, false si es el turno del jugador 2
	bool player1Started;	//true si empezo jugando el jugador 1
	catanPlayerModel player1;
	catanPlayerModel player2;
	cards p1SelectedCardsForTrade;
	cards p2SelectedCardsForTrade;
	cards p1DiscardRobberCards;
	resource_t playerSelectedResource; //para el bankTrade
	resourceType bankSelectedResource;
	bool constructing;
	unsigned char dice1;
	unsigned char dice2;
	catanMapModel map;
	bool selectedResource(resourceType res, unsigned char player);
	networkingEventTypes selecting;
	void updatePlayersVictoryPoints();
	unsigned char longestRoadPlayer;
	bool validResourceForConstruct(networkingEventTypes type);
	bool validSelectedCards(string cardsPlayer1, string cardsPlayer2);		//checkea que la transaccion solicitada sea valida, en cuyo case devuelve true
	bool p2HasSelectedCards(); //devuelve true si el jugador 2 tiene las selected cards
	bool initConstructionOk(unsigned char player);
};


