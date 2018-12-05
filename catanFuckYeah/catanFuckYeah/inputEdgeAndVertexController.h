#pragma once
#include "EDAInputController.h"
#include "catanGameModel.h"

class inputEdgeAndVertexController : public EDAInputController
{
public:
	
	inputEdgeAndVertexController(catanGameModel * game);
	/*
	Si el click cae en:
	Vertice:  ret = gameModel->validConstruction(SETTLEMENT/CITY,coords);, las coordenadas estan hardcodeadas
	Road: ret = gameModel->validConstruction(ROAD,coords); coordenadas hardcodeadas
	Siempre que caiga en un lugar valido y la construccion sea valida, controllerEvent = new buildEv(SETTLEMENT/ROAD/CITY);
	*/
	virtual void parseMouseEvent(mouseEvent * ev);
	virtual void parseKeyboardEvent(keyboardEvent * ev);
	inputControllerTypes getType() { return CTRL_EDGE_AND_VERTEX; }
	~inputEdgeAndVertexController();
private:
	catanGameModel * gameModel;
};

