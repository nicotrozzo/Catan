#pragma once

#include <iostream>
#include "genericFSM.h"
#include "bossFSMEvents.h"
#include "netwEmisor.h"
#include "catanGameSetter.h"
#include ""
class handShakingFSM : public genericFSM
{
public:
	//handShakingFSM(string playerName) { game = new catanGameSetter; game->setMyPlayerName(playerName); info2send = playerName; //la primera informacion que tendra que mandar fuera de un header sera el nombre del jugador propio }
	virtual catanGame * getCatanGame(void) = 0; 
	networkingEventTypes getExpectedPackage() { return expectedPackage; }

protected:
	catanGameSetter * game;	//catanGameSetter es herencia de catanGame (que tiene las variables protected), con setters
	networkingEventTypes expectedPackage;
	string info2send;
};

enum handShakingServStates : stateTypes { WAIT_NAME_S, WAIT_NAME_REQUEST_S, WAIT_NAME_ACK_S, MAP_ACK_S, CIRC_TOK_ACK_S, WAIT_START_ACK_S };

class handShakingServerFSM : public handShakingFSM
{


private:

#define TX(x) (static_cast<void (genericFSM::* )(genericEvent *)>(&bossFSM::x)) //casteo a funcion, por visual

	const fsmCell fsmTable[6][2] = {
	//			 NEXT							INVALID_EVENT			
	{ { WAIT_NAME_REQUEST_S,TX(saveName) },	{ WAIT_NAME_S,TX(error) }	},			//WAIT_NAME_S			
	{ { WAIT_NAME_ACK_S,TX(sendName) },		{ WAIT_NAME_REQUEST_S,TX(error) } },	//WAIT_NAME_REQUEST_S	
	{ { MAP_ACK_S,TX(sendMap) },				{ WAIT_NAME_ACK_S,TX(error) } },	//WAIT_NAME_ACK_S		
	{ { CIRC_TOK_ACK_S,TX(sendTokens) },		{ MAP_ACK_S,TX(error) } },			//MAP_ACK_S				
	{ { WAIT_START_ACK_S,TX(sendStart) },		{ CIRC_TOK_ACK_S,TX(error) } },		//CIRC_TOK_ACK_S			
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
};

enum handShakingServStates : stateTypes { WAIT_NAME_REQUEST_C, WAIT_NAME_ACK_C, WAIT_NAME_C, WAIT_MAP_C, WAIT_CIRC_TOK_C, WAIT_START_C };

class handShakingClientFSM : public handShakingFSM
{


private:

#define TX(x) (static_cast<void (genericFSM::* )(genericEvent *)>(&bossFSM::x)) //casteo a funcion, por visual

	const fsmCell fsmTable[6][2] = {
	//			 NEXT							INVALID_EVENT											                 
	{ { WAIT_NAME_ACK_C,TX(sendName) },		{ WAIT_NAME_REQUEST_C,TX(error) } },//WAIT_NAME_REQUEST_C	
	{ { WAIT_NAME_C,TX(sendNameReq) },		{ WAIT_NAME_ACK_C,TX(error) } },	//WAIT_NAME_ACK_C			
	{ { WAIT_MAP_C,TX(saveName) },			{ WAIT_NAME_C,TX(error) } },		//WAIT_NAME_C			
	{ { WAIT_CIRC_TOK_C,TX(saveMap) },		{ WAIT_MAP_C,TX(error) } },			//WAIT_MAP_C			
	{ { WAIT_START_C,TX(saveTokens) },		{ WAIT_CIRC_TOK_C,TX(error) } },	//WAIT_CIRC_TOK_C		
	{ { WAIT_START_C,TX(endHandshaking) },	{ WAIT_START_C,TX(error) } },		//WAIT_START_C			
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
	handShakingClientFSM(string,netwEmisor * emisor);
};

