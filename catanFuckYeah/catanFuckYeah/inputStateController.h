#pragma once
#include "EDAInputController.h"
#include "playingFSM.h"
class inputStateController : public EDAInputController
{
public:
	inputStateController();
	void setEv(playingFSMEvTypes ev);
	inputControllerTypes getType() { return CTRL_STATE; }
	bool parseMouseEvent(mouseEvent * ev) {}
	bool parseKeyboardEvent(keyboardEvent * ev) {}
	~inputStateController();
};

