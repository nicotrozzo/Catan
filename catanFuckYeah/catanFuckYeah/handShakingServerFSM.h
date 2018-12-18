#pragma once
#include "handShakingFSM.h"

enum handShakingServStates : stateTypes { WAIT_NAME_S, WAIT_NAME_REQUEST_S, WAIT_NAME_ACK_S, MAP_ACK_S, CIRC_TOK_ACK_S, WAIT_START_ACK_S };

class handShakingServerFSM : public handShakingFSM
{


private:

#define TX(x) (static_cast<void (genericFSM::* )(genericEvent *)>(&handShakingServerFSM::x)) //casteo a funcion, por visual

	const fsmCell fsmTable[6][2] = {
		//			 NEXT							INVALID_EVENT			
	{ { WAIT_NAME_REQUEST_S,TX(saveName) },{ WAIT_NAME_S,TX(error) } },			//WAIT_NAME_S			
	{ { WAIT_NAME_ACK_S,TX(sendName) },{ WAIT_NAME_REQUEST_S,TX(error) } },	//WAIT_NAME_REQUEST_S	
	{ { MAP_ACK_S,TX(sendMap) },{ WAIT_NAME_ACK_S,TX(error) } },	//WAIT_NAME_ACK_S		
	{ { CIRC_TOK_ACK_S,TX(sendTokens) },{ MAP_ACK_S,TX(error) } },			//MAP_ACK_S				
	{ { WAIT_START_ACK_S,TX(sendStart) },{ CIRC_TOK_ACK_S,TX(error) } },		//CIRC_TOK_ACK_S			
	{ { WAIT_START_ACK_S,TX(endHandshaking) },{ WAIT_START_ACK_S,TX(error) } },		//WAIT_START_ACK_S				 
	};

	//The action routines for the FSM

	void error(genericEvent * ev);
	void saveName(genericEvent * ev);
	void sendName(genericEvent * ev);
	void sendMap(genericEvent * ev);
	void sendTokens(genericEvent * ev);
	void sendStart(genericEvent * ev);
	void endHandshaking(genericEvent * ev);

	netwEmisor * communicator;
public:
	handShakingServerFSM(string, netwEmisor *emisor);
	virtual catanGameModel * getCatanGame(void);
};

