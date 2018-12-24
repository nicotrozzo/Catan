#pragma once

#include <iostream>
#include "genericFSM.h"
#include "bossFSMEvents.h"
#include "netwEmisor.h"
#include "catanGameSetter.h"

enum handShakingEvTypes : eventTypes {NEXT,INVALID_EVENT};

class handShakingEv : public genericEvent
{
public:
	handShakingEv(bool next) : next(next) {}
	eventTypes getType() { return (next ? NEXT : INVALID_EVENT); }
private:
	bool next;
};

class handShakingFSM : public genericFSM
{
public:
	handShakingFSM(const fsmCell * const table, const unsigned int rows, const unsigned int columns, stateTypes initState) : genericFSM(table, rows, columns, initState) { game = new catanGameSetter; }
	virtual catanGameModel * getCatanGame(void) = 0; 
	networkingEventTypes getExpectedPackage() { return expectedPackage; }

protected:
	catanGameSetter * game;	//catanGameSetter es herencia de catanGame (que tiene las variables protected), con setters
	networkingEventTypes expectedPackage;
	string info2send;
};

