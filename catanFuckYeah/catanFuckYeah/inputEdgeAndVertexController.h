#pragma once
#include "EDAInputController.h"
#include "catanGameModel.h"

class inputEdgeAndVertexController : public EDAInputController
{
public:
	inputEdgeAndVertexController(catanGameModel * game);
	virtual void parseMouseEvent(mouseEvent * ev);
	virtual void parseKeyboardEvent(keyboardEvent * ev);
	inputControllerTypes getType() { return CTRL_EDGE_AND_VERTEX; }
	~inputEdgeAndVertexController();
private:
	catanGameModel gameModel;
};

