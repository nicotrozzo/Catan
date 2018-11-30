#pragma once
#include "bossFSMEvents.h"

class  nameIsPckg : public networkingEv
{
public:
	nameIsPckg(string pckg);
	string getName();
private:
	string name;
};


class mapIsPckg : public networkingEv
{
public:
	mapIsPckg(string pckg);
	string getMap();
private:
	string map;
};

class circTokensPckg : public networkingEv
{
public:
	circTokensPckg(string pckg);
	string getTokens();
private:
	string circTokens;
};

class offerTradePckg : public networkingEv
{
public:
	offerTradePckg(string pckg);
	string getOwnResources();
	string getOppResources();

private:
	string ownRes;
	string oppRes;
};

class bankTradePckg : public networkingEv
{
public:
	bankTradePckg(string offer);
	string getOwnResources();
	unsigned char getBankResource();
private:
	string ownRes;
	unsigned char bankRes;
};

class dicesArePckg : public networkingEv
{
public:
	dicesArePckg(string dices);
	unsigned char getDicesSum();
private:
	unsigned char dice1;
	unsigned char dice2;
};

class robberCardsPckg : public networkingEv
{
public:
	robberCardsPckg(string robbCards);
	string getCards();
private:
	unsigned char cardCount;
	string cards;
};


class robberMovePckg : public networkingEv
{
public:
	robberMovePckg(string move);
	unsigned char getNewRobberPos();
private:
	unsigned char newPos;		//es unsigned har ya que va en un hexagono
};

class buildPckg : public networkingEv
{
public:
	buildPckg(string pckg);	//para settlement, road y city
	string getCoords();
private:
	string coords;
};

/*
class devCardsPckg : public networkingEv
{
public:

private:

};
*/