#include "gameModelViewer.h"



gameModelViewer::gameModelViewer(catanGameModel *myGame)
{
	initOk = false;
	this->myGame = myGame;
	if ((diceValue1 = al_load_bitmap("graficoCatan\\dados\\1.png")) != NULL && (diceValue2 = al_load_bitmap("graficoCatan\\dados\\2.png")) != NULL(diceValue3 = al_load_bitmap("graficoCatan\\dados\\3.png")) != NULL(diceValue4 = al_load_bitmap("graficoCatan\\dados\\4.png")) != NULL(diceValue5 = al_load_bitmap("graficoCatan\\dados\\5.png")) != NULL(diceValue6 = al_load_bitmap("graficoCatan\\dados\\6.png")) != NULL)
	{
		if ((tradeMenuBitmap = al_load_bitmap("graficoCatan\\menues\\menuDeTrueque.png")) != NULL)
		{
			if ((fontForAmountOfCards = al_load_ttf_font("graficoCatan\\font\\scribish.ttf", 43, 0)) != NULL)
			{
				initOk = true;
			}
		}
	}
}

void gameModelViewer::update()
{
	if (initOk)
	{
		viewDices();
		if ((myGame->isTrading() == BANK_TRADE) || (myGame->isTrading() == OFFER_TRADE))
		{
			viewTrade();
		}
	}
	else
	{
		cout << "mal en gameModelViewer" << endl;
	}
}

void gameModelViewer::viewDices()
{
	unsigned char dice1 = myGame->getDice1();
	unsigned char dice2 = myGame->getDice2();
	switch (dice1)
	{
	case 1:
		al_draw_bitmap(diceValue1, 1384, 416, 0);
		break;
	case 2:
		al_draw_bitmap(diceValue2, 1384, 416, 0);
		break;
	case 3:
		al_draw_bitmap(diceValue3, 1384, 416, 0);
		break;
	case 4:
		al_draw_bitmap(diceValue4, 1384, 416, 0);
		break;
	case 5:
		al_draw_bitmap(diceValue5, 1384, 416, 0);
		break;
	case 6:
		al_draw_bitmap(diceValue6, 1384, 416, 0);
		break;
	}
	switch (dice2)
	{
	case 1:
		al_draw_bitmap(diceValue1, 1510, 485, 0);
		break;
	case 2:
		al_draw_bitmap(diceValue2, 1510, 485, 0);
		break;
	case 3:
		al_draw_bitmap(diceValue3, 1510, 485, 0);
		break;
	case 4:
		al_draw_bitmap(diceValue4, 1510, 485, 0);
		break;
	case 5:
		al_draw_bitmap(diceValue5, 1510, 485, 0);
		break;
	case 6:
		al_draw_bitmap(diceValue6, 1510, 485, 0);
		break;
	}
}

void gameModelViewer::viewTrade()
{
	al_draw_bitmap(tradeMenuBitmap,241,66,0);
}

void gameModelViewer::viewSelecteCards()
{
	if (myGame->isTrading() == BANK_TRADE)
	{
		resource_t playerCards = myGame->getPlayerSelectedResource();
		resourceType bankCards = myGame->getBankSelectedResource();
		string bankAccess;
		string playerAccess;
		switch (playerCards.res)
		{
		case ORE:
			playerAccess += "ORE";
			break;
		case BRICK:
			playerAccess += "BRICK";
			break;
		case WOOL:
			playerAccess += "WOOL";
			break;
		case WOOD:
			playerAccess += "WOOD";
			break;
		case WHEAT:
			playerAccess += "WHEAT";
			break;
		}	
		switch (bankCards)
		{
		case ORE:
			bankAccess += "ORE";
			break;
		case BRICK:
			bankAccess += "BRICK";
			break;
		case WOOL:
			bankAccess += "WOOL";
			break;
		case WOOD:
			bankAccess += "WOOD";
			break;
		case WHEAT:
			bankAccess += "WHEAT";
			break;
		}
		playerAccess += '1';
		bankAccess += '2';
		coords playerCardCoords = { gameCoords::cardsCoords[playerAccess].xCoord, gameCoords::cardsCoords[playerAccess].yCoord };
		coords bankCardCoords = { gameCoords::cardsCoords[bankAccess].xCoord, gameCoords::cardsCoords[bankAccess].yCoord };
		al_draw_text(fontForAmountOfCards, al_color_name("black"), playerCardCoords.xCoord, playerCardCoords.yCoord, 0, to_string(playerCards.resCount + '0').c_str());
		al_draw_text(fontForAmountOfCards, al_color_name("black"), bankCardCoords.xCoord, bankCardCoords.yCoord, 0, "1");
	}
	else if (myGame->isTrading() == OFFER_TRADE)
	{
		cards player1Cards = myGame->getP1SelectedCardsForTrade();
		string ore = "ORE1";
		al_draw_text(fontForAmountOfCards, al_color_name("black"), gameCoords::cardsCoords[ore].xCoord, gameCoords::cardsCoords[ore].yCoord, 0, player1Cards.ore);
	}
}



gameModelViewer::~gameModelViewer()
{
}

