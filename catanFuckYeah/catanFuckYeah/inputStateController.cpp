#include "inputStateController.h"



inputStateController::inputStateController()
{
}

void inputStateController::setEv(playingFSMEvTypes ev)
{
	controllerEvent = new playingFSMEvent(ev);
}

inputStateController::~inputStateController()
{
}
