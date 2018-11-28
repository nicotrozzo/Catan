#include "bossFSM.h"
#include "bossFSMEvents.h"
#include "connectionEstablisher.h"
#include "handShakingFSM.h"

bossFSM::bossFSM() : genericFSM(&fsmTable[0][0], 6, 7, START_MENU) 
{
	//innerFSM = new startMenuFSM();	//esta fsm debe crear en su constructor el display		
}

/*Action routines*/
void bossFSM::sendToStartMenu(genericEvent * ev)
{
	//innerFSM->cycle(ev);	
}

void bossFSM::newEstablisher(genericEvent * ev)
{
	//startMenuFSM->getDisplay()
	//delete innerFSM;
	//innerFSM = new connectionEstablisher;
	//poner a alguien a mirar el boton de quit (fsm?)
}

void bossFSM::stMnError(genericEvent * ev)
{
	//capaz informar el error
	closeStMn(ev);
}

void bossFSM::closeStMn(genericEvent * ev)
{
	//delete innerFSM
	fsmEvent = new outEv;
}

void bossFSM::refreshStMn(genericEvent * ev)
{
	//innerFSM->cycle(static_cast<timerEv *>(ev));	
}

void bossFSM::sendQuitController(genericEvent * ev)
{
	//quitController->event(static_cast<inputEv *>(ev)->aditionalInfo()));
}

void bossFSM::newHandshaking(genericEvent * ev)
{
	//hacer cosas de cambio de estado
	//crear/attachear/arrancar generador de eventos de timer de 2,5 minutos
	//delete innerFSM;
	//innerFSM = new handShakingFSM();
}

void bossFSM::newStMn(genericEvent * ev)
{
	//innerFSM = new startMenuFSM;
}

void bossFSM::closeWaiting(genericEvent * ev)
{
	//destruir mas cosas si hace falta
	delete innerFSM;
}

void bossFSM::refreshWait(genericEvent * ev)
{
	//update display, falta ver como
}

void bossFSM::newGame(genericEvent * ev)
{
	//delete innerFSM;
	//innerFSM = new playingFSM;
	//quitController->updatePosition(PLAYING);

}

void bossFSM::closeConnection(genericEvent * ev)
{

}

void bossFSM::finishHandshaking(genericEvent * ev)
{
	fsmEvent = new outEv;
}

void bossFSM::closeHandshaking(genericEvent * ev)
{

}

void bossFSM::sendToNetwFSM(genericEvent * ev)
{
	//innerFSM->cycle(static_cast<networkingEv *>(ev)->getHeader()) //en realidad hay que mandarle todo el evento, capaz modificar el cycle de la fsm de handshaking para que haga getHeader en vez de getType
																	//sino que el networking event tenga adentro otro evento con getType = getHeader;
}

void bossFSM::sendTimerEv(genericEvent * ev)
{
	//mandar al display de alguna forma si la fuente es allegro
	//mandar a fsm handshaking como evento invalido para que corte todo
}


void bossFSM::sendInputEv(genericEvent * ev)
{
	//ACA TIENE QUE ESTAR EL DISPATCHER PARA LA FSM DE PLAYING
	//innerFSM->cycle(static_cast<inputEv *>(ev)->additionalInfo);
	//quitController(static_cast<>); //mandar a quit controller si es mouse o Q, ver despues
}

void bossFSM::finishGame(genericEvent * ev)
{
	//avisar al juego que esta por salir?
}

void bossFSM::closeGame(genericEvent * ev)
{
	fsmEvent = new outEv;
}

void bossFSM::sendNetwEv(genericEvent * ev)
{
	//innerFSM->cycle(static_cast<networkingEv *>(ev)->additional);
}

void bossFSM::sendGameOver(genericEvent * ev)
{

}

void bossFSM::closeRematch(genericEvent * ev)
{
	fsmEvent = new outEv;
}



void bossFSM::(genericEvent * ev)
{

}