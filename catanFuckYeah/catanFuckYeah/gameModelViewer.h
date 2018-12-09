#pragma once
#include "catanGameModel.h"
#include "allegroInit.h"
#include "observer.h"
#include "gameCoords.h"
#include <allegro5/allegro_color.h>


class gameModelViewer : public observer
{
public:
	gameModelViewer(catanGameModel *myGame);
	void update();
	~gameModelViewer();
private:
	catanGameModel * myGame;
	ALLEGRO_BITMAP * diceValue1;
	ALLEGRO_BITMAP * diceValue2;
	ALLEGRO_BITMAP * diceValue3;
	ALLEGRO_BITMAP * diceValue4;
	ALLEGRO_BITMAP * diceValue5;
	ALLEGRO_BITMAP * diceValue6;
	ALLEGRO_BITMAP * tradeMenuBitmap;
	ALLEGRO_BITMAP * robberDiscardMenuBitmap;
	ALLEGRO_BITMAP * tickBitmap;
	ALLEGRO_BITMAP * crossBitmap;
	ALLEGRO_BITMAP * passButtonBitmap;
	ALLEGRO_BITMAP * bankTradeButtonBitmap;
	ALLEGRO_BITMAP * playerTradeButtonBitmap;
	ALLEGRO_BITMAP * exitButtonBitmap;
	ALLEGRO_FONT * fontForAmountOfCards;
	ALLEGRO_FONT * fontForBankCosts;
	void viewDices();
	void viewTrade();
	void viewRobberDiscard();
	void viewSelectedCards();
	void viewTickAndCrossButtons();
	void viewActionButtons();			//viewer de bank trade, player trade y pass button
	void viewExitButton();
	bool initOk;
};

