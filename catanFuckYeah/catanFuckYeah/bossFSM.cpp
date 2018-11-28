#include "bossFSM.h"
#include "bossFSMEvents.h"
#include "connectionEstablisher.h"
#include "handShakingFSM.h"

bossFSM::bossFSM() : genericFSM(&fsmTable[0][0], 6, 7, START_MENU) 
{
	//innerFSM = new startMenuFSM();	//esta fsm debe crear en su constructor el display
	//	
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
}

void bossFSM::stMnError(genericEvent * ev)
{
	//capaz informar el error
	endStMn(ev);
}

void bossFSM::endStMn(genericEvent * ev)
{
	//delete innerFSM
	fsmEvent = new outEv;
}

void bossFSM::refreshStMn(genericEvent * ev)
{
	//innerFSM->cycle(static_cast<timerEv *>(ev));	
}

void bossFSM::sendToInnerFSM(genericEvent * ev)
{
	//innerFSM->cycle(static_cast<inputEv *>(ev)->aditionalInfo()));
}

void bossFSM::newHandshaking(genericEvent * ev)
{
	//hacer cosas de cambio de estado
	//delete innerFSM;
	//innerFSM = new handShakingFSM();
}

void bossFSM:: (genericEvent * ev)
{

}

void bossFSM:: (genericEvent * ev)
{

}

void bossFSM:: (genericEvent * ev)
{

}

void bossFSM:: (genericEvent * ev)
{

}

void bossFSM:: (genericEvent * ev)
{

}