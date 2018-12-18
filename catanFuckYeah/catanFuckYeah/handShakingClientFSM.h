#pragma once
#include "handShakingFSM.h"

enum handShakingClientStates : stateTypes { WAIT_NAME_REQUEST_C, WAIT_NAME_ACK_C, WAIT_NAME_C, WAIT_MAP_C, WAIT_CIRC_TOK_C, WAIT_START_C };

class handShakingClientFSM : public handShakingFSM
{


private:

#define TX(x) (static_cast<void (genericFSM::* )(genericEvent *)>(&handShakingClientFSM::x)) //casteo a funcion, por visual

	const fsmCell fsmTable[6][2] = {
		//			 NEXT							INVALID_EVENT											                 
	{ { WAIT_NAME_ACK_C,TX(sendName) },{ WAIT_NAME_REQUEST_C,TX(error) } },//WAIT_NAME_REQUEST_C	
	{ { WAIT_NAME_C,TX(sendNameReq) },{ WAIT_NAME_ACK_C,TX(error) } },	//WAIT_NAME_ACK_C			
	{ { WAIT_MAP_C,TX(saveName) },{ WAIT_NAME_C,TX(error) } },		//WAIT_NAME_C			
	{ { WAIT_CIRC_TOK_C,TX(saveMap) },{ WAIT_MAP_C,TX(error) } },			//WAIT_MAP_C			
	{ { WAIT_START_C,TX(saveTokens) },{ WAIT_CIRC_TOK_C,TX(error) } },	//WAIT_CIRC_TOK_C		
	{ { WAIT_START_C,TX(endHandshaking) },{ WAIT_START_C,TX(error) } },		//WAIT_START_C			
	};

	//The action routines for the FSM

	void error(genericEvent * ev);
	void sendName(genericEvent * ev);
	void sendNameReq(genericEvent * ev);
	void saveName(genericEvent * ev);
	void saveMap(genericEvent * ev);
	void saveTokens(genericEvent * ev);
	void endHandshaking(genericEvent * ev);

	list<networkingEventTypes> alternatePackages;
	netwEmisor * communicator;
public:
	handShakingClientFSM(string, netwEmisor * emisor);
	virtual catanGameModel * getCatanGame(void);
};


