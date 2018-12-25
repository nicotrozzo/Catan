#include "handShakingServerFSM.h"
#include "networkingEvents.h"

handShakingServerFSM::handShakingServerFSM(string playerName_, netwEmisor * emisor) : handShakingFSM(&fsmTable[0][0], 6, 2, WAIT_NAME_S)
{
	game = new catanGameSetter;
	game->setMyName(playerName_);
	communicator = emisor;
	communicator->sendPackage(NAME);
	expectedPackage = NAME_IS;
	info2send = playerName_;
}

void handShakingServerFSM::error(genericEvent * ev)
{
	fsmEvent = new outEv("Handshaking error");
	expectedPackage = NO_PCKG;
	//algo mas?
}

void handShakingServerFSM::saveName(genericEvent * ev)
{
	string opponentName = static_cast<handShakingEv *>(ev)->getInfo();
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

catanGameModel * handShakingServerFSM::getCatanGame(void)
{
	catanGameModel * ret = nullptr;
	if (fsmEvent != nullptr)
	{
		ret = static_cast<catanGameModel *>(game);
	}
	return ret;
}

void handShakingServerFSM::endHandshaking(genericEvent * ev)
{
	fsmEvent = new doneEv;
}


