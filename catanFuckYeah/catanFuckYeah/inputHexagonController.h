#pragma once
#include "EDAInputController.h"
#include "catanGameModel.h"

class inputHexagonController : public EDAInputController
{
public:
	inputHexagonController(catanGameModel * game);
	/*
		Si el click cae en un hexagono:
		gameModel->robberMoved(hexagonoClickeado) si devuelve true, controllerEvent = algo del robber
		si devuelve false, no hay que emitir evento y quedar esperando un nuevo click
	*/
	virtual void parseMouseEvent(mouseEvent * ev);
	virtual void parseKeyboardEvent(keyboardEvent * ev);
	inputControllerTypes getType() { return CTRL_HEXAGON; }
	~inputHexagonController();
private:
	catanGameModel * game;
};

