#pragma once

#include <iostream>
#include "genericFSM.h"
#include "bossFSMEvents.h"
#include "netwEmisor.h"
#include "catanGameSetter.h"
#include "timerEventGenerator.h"

enum handShakingEvTypes : eventTypes {NEXT,INVALID_EVENT};

class handShakingEv : public genericEvent
{
public:
	handShakingEv(bool next,string info_ = "") : next(next), info(info_) {}
	eventTypes getType() { return (next ? NEXT : INVALID_EVENT); }
	string getInfo() { return info; }
private:
	bool next;
	string info;
};

class handShakingFSM : public genericFSM
{
public:
	handShakingFSM(const fsmCell * const table, const unsigned int rows, const unsigned int columns, stateTypes initState, timerEventGenerator * ansTimer) : genericFSM(table, rows, columns, initState), answerTimer(ansTimer) { game = new catanGameSetter; }
	virtual catanGameModel * getCatanGame(void) = 0; 
	networkingEventTypes getExpectedPackage() { return expectedPackage; }
	virtual bool clientFSM() = 0;
protected:
	catanGameSetter * game;	//catanGameSetter es herencia de catanGame (que tiene las variables protected), con setters
	timerEventGenerator * answerTimer;
	networkingEventTypes expectedPackage;
	string info2send;
};

