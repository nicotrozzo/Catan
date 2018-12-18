#pragma once
#include "EDAInputController.h"
#include "catanGameModel.h"
#include "netwEmisor.h"

class inputHexagonController : public EDAInputController
{
public:
	inputHexagonController(catanGameModel * game, netwEmisor* emisor);
	/*
		Si el click cae en un hexagono:
		gameModel->robberMoved(hexagonoClickeado) si devuelve true, controllerEvent = algo del robber
		si devuelve false, no hay que emitir evento y quedar esperando un nuevo click
	*/
	virtual bool parseMouseEvent(mouseEvent * ev);
	virtual bool parseKeyboardEvent(keyboardEvent * ev) { return false; }			//El usuario no tiene por que saber como llamamos a cada hexagono A,B,C...
	inputControllerTypes getType();
	~inputHexagonController();
private:
	catanGameModel * gameModel;
	netwEmisor * netEmisor;
};

