#include "bossFSM.h"
#include "bossFSMEvents.h"
#include "connectionEstablisher.h"
#include "handShakingFSM.h"
#include "waitingGame.h"
bossFSM::bossFSM(quitButtonController * qControl, connectionEstablisher * establish) : genericFSM(&fsmTable[0][0], 6, 7, START_MENU)
{
	graficador = new startMenu;
	quitController = qControl;
	establisher = establish;
	if (!static_cast<startMenu *>(graficador)->getInitOk())
	{
		delete graficador;
		fsmEvent = new closeDisplayEv;
	}
		//evGen.attach(quitController);
	//innerFSM = new startMenuFSM();	//esta fsm debe crear en su constructor el display		
}

/*Action routines*/
void bossFSM::sendToStMnControllers(genericEvent * ev)
{
	if (static_cast<inputEv *>(ev)->getInputEvType() == INP_MOUSE_EVENT)
	{
		quitController->parseMouseEvent(static_cast<mouseEvent *>(ev));
	}
	else if (static_cast<inputEv *>(ev)->getInputEvType() == INP_KEYBOARD_EVENT)
	{
		quitController->parseKeyboardEvent(static_cast<keyboardEvent *>(ev));
	}
}

void bossFSM::newEstablisher(genericEvent * ev)
{	
	graphicator * temp = new waitingGame(static_cast<startMenu*>(graficador)->getDisplay());
	delete graficador;
	graficador = temp;
	establisher->startConnecting();
	static_cast<waitingGame *>(graficador)->setMessage("Buscando oponente...");
	quitController->toggleState();
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
	if (static_cast<timerEv *>(ev)->refreshEvent())
	{
		graficador->refresh();
	}
}

void bossFSM::sendQuitController(genericEvent * ev)
{
	if (ev->getType() == INPUT_EVENT)
	{
		inputEv inEvent = static_cast<ip>();
	}
	quitController->event(static_cast<inputEv *>(ev)->aditionalInfo()));
}

void bossFSM::newHandshaking(genericEvent * ev)
{

	//innerFSM = establisher->getConnector()
	//hacer cosas de cambio de estado
	//crear/attachear/arrancar generador de eventos de timer de 2,5 minutos
	//evGen.detach(innerFSM);
	//delete innerFSM;
	//innerFSM = new handShakingFSM();
	//evGen.attach(innerFSM);
}

void bossFSM::newStMn(genericEvent * ev)
{
	//innerFSM = new startMenuFSM;
	//evGen.attach(innerFSM);
}

void bossFSM::closeWaiting(genericEvent * ev)
{
	//destruir mas cosas si hace falta
	evGen.detach(innerFSM);
	delete innerFSM;
}

void bossFSM::refreshWait(genericEvent * ev)
{
	//update display, falta ver como
}

void bossFSM::newGame(genericEvent * ev)
{
	//catanGame game = static_cast<handShakingFSM>(innerFSM)->getCatanGame();
	evGen.detach(innerFSM);
	//delete innerFSM;
	//innerFSM = new playingFSM(game);
	//quitController->updatePosition(PLAYING);
	evGen.attach(innerFSM);
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