#include "handShakingFSM.h"
#include "networkingEvents.h"

handShakingServerFSM::handShakingServerFSM(string playerName_,netwEmisor * emisor) : genericFSM(&fsmTable[0][0], 6, 2, WAIT_NAME_S), handShakingFSM(playerName_)
{
	game = new catanGameSetter;
	communicator = emisor;
	expectedPackage = NAME_IS;	
}

void handShakingServerFSM::error(genericEvent * ev)
{
	fsmEvent = new outEv("Handshaking error");
	expectedPackage = static_cast<networkingEventTypes>(0);
	//algo mas?
}

void handShakingServerFSM::saveName(genericEvent * ev)
{
	string opponentName = static_cast<nameIsPckg *>(ev)->getName();	//capaz static_cast<name_is *>
	catanGameSetter->setOppName(opponentName);
	communicator->send(ACK);
	expectedPackage = NAME;
}

void handShakingServerFSM::sendName(genericEvent * ev)
{
	//communicator->send(NAME_IS, info2send);
	expectedPackage = ACK;
}

void handShakingServerFSM::sendMap(genericEvent * ev)
{
	//info2send = catanGameSetter->getMap();
	//communicator->send(MAP_IS, info2send);
	expectedPackage = ACK;
}

void handShakingServerFSM::sendTokens(genericEvent * ev)
{
	//info2send = catanGameSetter->getCircTok();
	//communicator->send(CIRCULAR_TOKENS, info2send);
	expectedPackage = ACK;
}

void handShakingServerFSM::sendStart(genericEvent * ev) 
{
	//HACER EN ALGUN LADO SRAND(TIME(NULL));
	networkingEventTypes package2send = (rand() % 2) ? I_START : YOU_START;
	//communicator->send(package2send);
	//catanGameSetter->setInitialPlayer(package2send);
	if (package2send == I_START)
	{
		expectedPackage = ACK;
	}	
	else
	{
		expectedPackage = static_cast<networkingEventTypes>(0);
		fsmEvent = new doneEv;	//OJO ACA QUE TERMINA UN ESTADO ANTES, LO AGARRARAN A TIEMPO AL EVENTO ANTES DE QUE LE MANDEN ALGO MAS?
	}
}

void handShakingServerFSM::endHandshaking(genericEvent * ev)
{
	fsmEvent = new doneEv;
}



/*Para el handshaking de client*/
handShakingClientFSM::handShakingClientFSM(string playerName_, netwEmisor * emisor) : genericFSM(&fsmTable[0][0], 6, 2, WAIT_NAME_REQUEST_C), handShakingFSM(playerName_)
{
	communicator = emisor;
	expectedPackage = NAME;
	alternatePackages.clear();
}
void handShakingClientFSM::error(genericEvent * ev)
{
	expectedPackage = static_cast<networkingEventTypes>(0);
	fsmEvent = new outEv("Handshaking error");
}

void handShakingClientFSM::sendName(genericEvent * ev)
{
	//communicator->send(NAME_IS, info2send);
	expectedPackage = ACK;
}

void handShakingClientFSM::sendNameReq(genericEvent * ev)
{
	//communicator->send(NAME);
	expectedPackage = NAME_IS;
}

void handShakingClientFSM::saveName(genericEvent * ev)
{
	//string opponentName = static_cast<networkingEv *>(ev)->extraInfo;	//capaz static_cast<name_is *>
	//catanGameSetter->setOppName(opponentName);
	//communicator->send(ACK);
	expectedPackage = MAP_IS;
}

void handShakingClientFSM::saveMap(genericEvent * ev)
{
	string map = static_cast<map_is *>(ev)->getMap();
	catanGameSetter->setMap(map);
	expectedPackage = CIRCULAR_TOKENS;
}

void handShakingClientFSM::saveTokens(genericEvent * ev)
{
	string map = static_cast<map_is *>(ev)->getMap();
	catanGameSetter->setMap(map);
	expectedPackage = I_START;
	alternatePackages = { YOU_START,PLAY_WITH_DEV };
}

void handShakingClientFSM::endHandshaking(genericEvent * ev)
{
	if ( (static_cast<networkingEv *>(ev)->getHeader()) == PLAY_WITH_DEV )
	{
		//communicator->send(NO);
		alternatePackages.remove(PLAY_WITH_DEV);	//no volvera a llegar un evento valido por este paquete
	}
	else
	{
		if ((static_cast<networkingEv *>(ev)->getHeader()) == YOU_START)
		{
			//catanGameSetter->setInitialPlayer(I_START);	//el servidor me dijo que empiece, le aviso al juego
		}
		else
		{
			//catanGameSetter->setInitialPlayer(YOU_START);	//arranca el servidor
			communicator->send(ACK);
		}
		fsmEvent = new doneEv;
	}
}

catanGameModel * handShakingServerFSM::getCatanGame(void)
{
	catanGameModel * ret = nullptr;
	if (fsmEvent != nullptr)
	{
		ret = static_cast<catanGameModel *>(game);
	}
	return ret;
}

catanGameModel * handShakingClientFSM::getCatanGame(void)
{
	catanGameModel * ret = nullptr;
	if (fsmEvent != nullptr)
	{
		ret = static_cast<catanGameModel *>(game);
	}
	return ret;
}