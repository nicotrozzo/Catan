#include "handShakingFSM.h"
#include "networkingEvents.h"

handShakingServerFSM::handShakingServerFSM(string playerName_,netwEmisor * emisor) : handShakingFSM(&fsmTable[0][0], 6, 2, WAIT_NAME_S)
{
	game = new catanGameSetter;
	game->setMyName(playerName_);
	communicator = emisor;
	expectedPackage = NAME_IS;	
}

void handShakingServerFSM::error(genericEvent * ev)
{
	fsmEvent = new outEv("Handshaking error");
	expectedPackage = NO_PCKG;
	//algo mas?
}

void handShakingServerFSM::saveName(genericEvent * ev)
{
	string opponentName = static_cast<nameIsPckg *>(ev)->getName();	
	game->setOppName(opponentName);
	communicator->sendPackage(ACK);
	expectedPackage = NAME;
}

void handShakingServerFSM::sendName(genericEvent * ev)
{
	communicator->sendPackage(NAME_IS, info2send);
	expectedPackage = ACK;
}

void handShakingServerFSM::sendMap(genericEvent * ev)
{
	info2send = game->getMap()->getMap();
	communicator->sendPackage(MAP_IS, info2send);
	expectedPackage = ACK;
}

void handShakingServerFSM::sendTokens(genericEvent * ev)
{
	info2send = game->getCircularTokens();
	communicator->sendPackage(CIRCULAR_TOKENS, info2send);
	expectedPackage = ACK;
}

void handShakingServerFSM::sendStart(genericEvent * ev) 
{
	networkingEventTypes package2send = (rand() % 2) ? I_START : YOU_START;
	communicator->sendPackage(package2send);
	unsigned char player = package2send == I_START ? 1 : 2;
	game->setInitialPlayer(player);
	if (package2send == I_START)
	{
		expectedPackage = ACK;
	}	
	else
	{
		expectedPackage = NO_PCKG;
		fsmEvent = new doneEv;	//OJO ACA QUE TERMINA UN ESTADO ANTES, LO AGARRARAN A TIEMPO AL EVENTO ANTES DE QUE LE MANDEN ALGO MAS?
	}
}

void handShakingServerFSM::endHandshaking(genericEvent * ev)
{
	fsmEvent = new doneEv;
}



/*Para el handshaking de client*/
handShakingClientFSM::handShakingClientFSM(string playerName_, netwEmisor * emisor) : handShakingFSM(&fsmTable[0][0], 6, 2, WAIT_NAME_REQUEST_C)
{
	info2send = playerName_;
	communicator = emisor;
	expectedPackage = NAME;
	alternatePackages.clear();
}

void handShakingClientFSM::error(genericEvent * ev)
{
	expectedPackage = NO_PCKG;
	fsmEvent = new outEv("Handshaking error");
}

void handShakingClientFSM::sendName(genericEvent * ev)
{
	game->setMyName(info2send);
	communicator->sendPackage(NAME_IS, info2send);
	expectedPackage = ACK;
}

void handShakingClientFSM::sendNameReq(genericEvent * ev)
{
	communicator->sendPackage(NAME);
	expectedPackage = NAME_IS;
}

void handShakingClientFSM::saveName(genericEvent * ev)
{
	string opponentName = static_cast<nameIsPckg *>(ev)->getName();	
	game->setOppName(opponentName);
	communicator->sendPackage(ACK);
	expectedPackage = MAP_IS;
}

void handShakingClientFSM::saveMap(genericEvent * ev)
{
	string map = static_cast<mapIsPckg *>(ev)->getMap();
	if (game->setMap(map))
	{
		communicator->sendPackage(ACK);
		expectedPackage = CIRCULAR_TOKENS;
	}
	else
	{
		fsmEvent = new outEv("Error de comunicacion");
		communicator->sendPackage(ERROR_PCKG);
	}
}

void handShakingClientFSM::saveTokens(genericEvent * ev)
{
	string tok = static_cast<circTokensPckg *>(ev)->getTokens();
	if (game->setCircularTokens(tok))
	{
		communicator->sendPackage(ACK);
		expectedPackage = I_START;
		alternatePackages = { YOU_START,PLAY_WITH_DEV };
	}
	else
	{
		fsmEvent = new outEv("Error de comunicacion");
		communicator->sendPackage(ERROR_PCKG);
	}
}

void handShakingClientFSM::endHandshaking(genericEvent * ev)
{
	if ( (static_cast<networkingEv *>(ev)->getHeader()) == PLAY_WITH_DEV )
	{
		communicator->sendPackage(NO);
		alternatePackages.remove(PLAY_WITH_DEV);	//no volvera a llegar un evento valido por este paquete
	}
	else
	{
		if ((static_cast<networkingEv *>(ev)->getHeader()) == YOU_START)
		{
			game->setInitialPlayer(1);	//el servidor me dijo que empiece, le aviso al juego
		}
		else
		{
			game->setInitialPlayer(2);	//arranca el servidor
			communicator->sendPackage(ACK);
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