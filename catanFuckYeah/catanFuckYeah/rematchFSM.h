#pragma once
#include "genericFSM.h"

enum rematchStates : stateTypes { WAIT_NAME_S, WAIT_NAME_REQUEST_S, WAIT_NAME_ACK_S, MAP_ACK_S, CIRC_TOK_ACK_S, WAIT_START_ACK_S };

enum rematchEvTypes : eventTypes { NEXT, INVALID_EVENT };

class rematchEv : public genericEvent
{
public:
	rematchEv(rematchEvTypes type_) : type(type_) {}
	eventTypes getType() { return type; }
private:
	rematchEvTypes type;
};

class rematchFSM :	public genericFSM
{


private:

#define TX(x) (static_cast<void (genericFSM::* )(genericEvent *)>(&rematchFSM::x)) //casteo a funcion, por visual

	const fsmCell fsmTable[][] = {
	//				CHANGE						 	
	{ { WAIT_NAME_REQUEST_S,TX(saveName) },{ WAIT_NAME_S,TX(error) } },			//WAIT_NAME_S			
	{ { WAIT_NAME_ACK_S,TX(sendName) },{ WAIT_NAME_REQUEST_S,TX(error) } },	//WAIT_NAME_REQUEST_S	
	};

	//The action routines for the FSM


public:
	rematchFSM(, const unsigned int rows, const unsigned int columns, stateTypes initState);
	~rematchFSM();
};

