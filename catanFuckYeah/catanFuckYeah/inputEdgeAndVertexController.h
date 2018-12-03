#pragma once
#include "EDAInputController.h"

class inputEdgeAndVertexController : public EDAInputController
{
public:
	inputEdgeAndVertexController();
	virtual void parseMouseEvent(mouseEvent * ev);
	virtual void parseKeyboardEvent(keyboardEvent * ev);
	~inputEdgeAndVertexController();
};

