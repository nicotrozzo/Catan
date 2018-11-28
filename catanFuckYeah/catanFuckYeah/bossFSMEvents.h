#pragma once

#include "eventHandling.h"

#include <iostream>

using namespace std;

enum implEvent : eventTypes { INPUT_EVENT, DONE, OUT, QUIT, CLOSE_DISPLAY , NETWORKING_EVENT , TIMER_EVENT};

//enunm Forward Declaration
//it is feasible as long as the type is defined in the code.
using inputEventTypes = unsigned int;

enum networkingEventTypes {
	ACK = 0x01, NAME = 0x10, NAME_IS, MAP_IS, CIRCULAR_TOKENS,
	PLAY_WITH_DEV = 0x15, DEV_CARDS, YOU_START, I_START,
	DICES_ARE = 0x20, ROBBER_CARDS, CARD_IS, ROBBER_MOVE, SETTLEMENT, ROAD, CITY, BANK_TRADE, OFFER_TRADE, PASS,
	DEV_CARD = 0x30, MONOPOLY, YEARS_OF_PLENTY, ROAD_BUILDING, KNIGHT,
	YES = 0x40, NO,
	I_WON = 0x50, PLAY_AGAIN, GAME_OVER,
	ERROR = 0xFE, QUIT
};

class inputEv : public genericEvent
{
public:
	eventTypes getType(void) { return INPUT_EVENT; }
	virtual inputEventTypes getInputEvType() = 0;
};

class doneEv : public genericEvent
{
public:
	eventTypes getType(void) { return DONE; }
};

class outEv : public genericEvent
{
public:
	outEv() {}
	outEv(string detail_) : detail(detail_) {}
	eventTypes getType(void) { return OUT; }
	string getDetail() { return detail; } 
private:
	const string detail;
};

class quitEv : public genericEvent
{
public:
	eventTypes getType(void) { return QUIT; }
};

class closeDisplayEv : public genericEvent
{
public:
	eventTypes getType(void) { return CLOSE_DISPLAY; }
};

class networkingEv : public genericEvent
{
public:
	networkingEv(networkingEventTypes header_);
	eventTypes getType(void) { return NETWORKING_EVENT; }
	networkingEventTypes getHeader();
	bool getError();
private:
	networkingEventTypes header;
	bool error;
	bool validHeader(char);
};

class timerEv : public genericEvent
{
public:
	eventTypes getType(void) { return TIMER_EVENT; }
};

