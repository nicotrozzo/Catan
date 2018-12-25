#include "handShakingClientFSM.h"
#include "networkingEvents.h"


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
	string opponentName = static_cast<handShakingEv *>(ev)->getInfo();
	game->setOppName(opponentName);
	communicator->sendPackage(ACK);
	expectedPackage = MAP_IS;
}

void handShakingClientFSM::saveMap(genericEvent * ev)
{
	string map = static_cast<handShakingEv *>(ev)->getInfo();
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
	string tok = static_cast<handShakingEv *>(ev)->getInfo();
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
	if ((static_cast<handShakingEv *>(ev)->getInfo())[0] == PLAY_WITH_DEV)
	{
		communicator->sendPackage(NO);
		alternatePackages.remove(PLAY_WITH_DEV);	//no volvera a llegar un evento valido por este paquete
	}
	else
	{
		if ((static_cast<handShakingEv *>(ev)->getInfo())[0] == YOU_START)
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

catanGameModel * handShakingClientFSM::getCatanGame(void)
{
	catanGameModel * ret = nullptr;
	if (fsmEvent != nullptr)
	{
		ret = static_cast<catanGameModel *>(game);
	}
	return ret;
}