#pragma once
#include "EDASubject.h"
#include "bossFSMEvents.h"

class catanGameModel : public EDASubject
{
public:
	catanGameModel();
	~catanGameModel();
	bool dicesThrown(unsigned int diceValue);	//modifica informacion del juego
	bool construction(networkingEventTypes type, string coords);		//devuelve false si la construccion no es valida, PUEDE MODIFICAR GAME OVER
	bool playersTrade();
	bool bankTrade();
	bool gameOver();	//true si termino el juego, llamar despues de construccion!!!!!!!!
private:
	
};

