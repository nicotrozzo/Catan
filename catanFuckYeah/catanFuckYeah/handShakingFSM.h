#pragma once

#include <iostream>
#include "genericFSM.h"
#include "bossFSMEvents.h"

enum handShakingImplStates : stateTypes { WAIT_NAME , WAIT_NAME_REQUEST, WAIT_NAME_ACK, MAP , CIRC_TOK, WAIT_START_ACK };

class handShakingFSM : public genericFSM
{


private:

#define TX(x) (static_cast<void (genericFSM::* )(genericEvent *)>(&bossFSM::x)) //casteo a funcion, por visual

	const fsmCell fsmTable[6][2] = {
	//			 NEXT									INVALID_EVENT					SKIP                  
	{ { WAIT_NAME_REQUEST,TX(guardarYMandarAck) },	{ WAIT_NAME,TX(error) },		{ WAIT_NAME,TX(error) } },			//WAIT_NAME		
	{ { WAIT_NAME_ACK,TX(mandarNombre) },			{ WAIT_NAME_REQUEST,TX(error) },{ WAIT_NAME_REQUEST,TX(error) } },	//WAIT_NAME_REQUEST
	{ { MAP,TX(mandarMapa) },						{ WAIT_NAME_ACK,TX(error) },	{ WAIT_NAME_ACK,TX(error) } } },	//WAIT_NAME_ACK
	{ { CIRC_TOK,TX(mandarTokens) },				{ MAP,TX(error) },				{ MAP,TX(error) } },				//MAP
	{ { WAIT_START_ACK,TX(avisarQuienEmpieza) },	{ CIRC_TOK,TX(error) },			{ CIRC_TOK,TX(error) } },			//CIRC_TOK
	{ { WAIT_START_ACK,TX(emitirDONE) },			{ WAIT_START_ACK,TX(error) },	{ CIRC_TOK,TX(error) } }			//WAIT_START_ACK 
	};
	
	//The action routines for the FSM
	
	void prueba1(genericEvent * ev)
	{
	
	}

	list<networkingEventTypes> expectedPackages;
	bool server;
public:
	handShakingFSM(bool server_) : genericFSM(&fsmTable[0][0], 6, 2, WAIT_NAME) { server = server_; }	//crear fsm chica, display (en fsm chica), atachear fsm chica como fuente de eventos
};