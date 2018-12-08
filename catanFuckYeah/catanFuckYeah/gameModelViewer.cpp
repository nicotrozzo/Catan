#include "gameModelViewer.h"


gameModelViewer::gameModelViewer(catanGameModel *myGame)
{
	initOk = false;
	this->myGame = myGame;
	if ((diceValue1 = al_load_bitmap("graficoCatan\\dados\\1.png")) != NULL && (diceValue2 = al_load_bitmap("graficoCatan\\dados\\2.png")) != NULL(diceValue3 = al_load_bitmap("graficoCatan\\dados\\3.png")) != NULL(diceValue4 = al_load_bitmap("graficoCatan\\dados\\4.png")) != NULL(diceValue5 = al_load_bitmap("graficoCatan\\dados\\5.png")) != NULL(diceValue6 = al_load_bitmap("graficoCatan\\dados\\6.png")) != NULL)
	{
		if ((tradeMenuBitmap = al_load_bitmap("graficoCatan\\menues\\menuDeTrueque.png")) != NULL)
		{
			if ((robberDiscardMenuBitmap = al_load_bitmap("graficoCatan\\menues\\menuDeLadron.png")) != NULL)
			{
				if ((fontForAmountOfCards = al_load_ttf_font("graficoCatan\\font\\scribish.ttf", 43, 0)) != NULL)
				{
					if ((fontForBankCosts = al_load_ttf_font("graficoCatan\\font\\scribish.ttf", 45, 0)) != NULL)
					{
						initOk = true;
					}
				}
			}
		}
	}
}

void gameModelViewer::update()
{
	if (initOk)
	{
		viewDices();
		if ((myGame->isSelecting() == BANK_TRADE) || (myGame->isSelecting() == OFFER_TRADE))
		{
			viewTrade();
			viewSelectedCards();
		}
		else if (myGame->isSelecting() == ROBBER_CARDS)
		{
			viewRobberDiscard();
			viewSelectedCards();
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

void gameModelViewer::viewRobberDiscard()
{
	al_draw_bitmap(robberDiscardMenuBitmap,241,66,0);
	al_draw_text(fontForBankCosts, al_color_name("black"), 489, 118, 0, to_string((myGame->getBankTradeCosts())[ORE] + '0') +"x1");
	al_draw_text(fontForBankCosts, al_color_name("black"), 489, 118, 0, to_string((myGame->getBankTradeCosts())[WHEAT] + '0') + "x1");
	al_draw_text(fontForBankCosts, al_color_name("black"), 489, 118, 0, to_string((myGame->getBankTradeCosts())[WOOL] + '0') + "x1");
	al_draw_text(fontForBankCosts, al_color_name("black"), 489, 118, 0, to_string((myGame->getBankTradeCosts())[WOOD] + '0') + "x1");
	al_draw_text(fontForBankCosts, al_color_name("black"), 489, 118, 0, to_string((myGame->getBankTradeCosts())[BRICK] + '0') + "x1");
}

void gameModelViewer::viewSelectedCards()
{
	if (myGame->isSelecting() == BANK_TRADE)
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
	else if (myGame->isSelecting() == OFFER_TRADE)
	{
		cards player1Cards = myGame->getP1SelectedCardsForTrade();
		string ore = "ORE";
		string brick = "BRICK";
		string wool = "WOOL";
		string wood = "WOOD";
		string wheat = "WHEAT";
		al_draw_text(fontForAmountOfCards, al_color_name("black"), gameCoords::cardsCoords[ore + '1'].xCoord, gameCoords::cardsCoords[ore].yCoord, 0, to_string(player1Cards.ore).c_str());
		al_draw_text(fontForAmountOfCards, al_color_name("black"), gameCoords::cardsCoords[brick + '1'].xCoord, gameCoords::cardsCoords[brick].yCoord, 0, to_string(player1Cards.brick).c_str());
		al_draw_text(fontForAmountOfCards, al_color_name("black"), gameCoords::cardsCoords[wool + '1'].xCoord, gameCoords::cardsCoords[wool].yCoord, 0, to_string(player1Cards.wool).c_str());
		al_draw_text(fontForAmountOfCards, al_color_name("black"), gameCoords::cardsCoords[wood + '1'].xCoord, gameCoords::cardsCoords[wood].yCoord, 0, to_string(player1Cards.wood).c_str());
		al_draw_text(fontForAmountOfCards, al_color_name("black"), gameCoords::cardsCoords[wheat + '1'].xCoord, gameCoords::cardsCoords[wheat].yCoord, 0, to_string(player1Cards.wheat).c_str());
		al_draw_text(fontForAmountOfCards, al_color_name("black"), gameCoords::cardsCoords[ore + '2'].xCoord, gameCoords::cardsCoords[ore].yCoord, 0, to_string(player1Cards.ore).c_str());
		al_draw_text(fontForAmountOfCards, al_color_name("black"), gameCoords::cardsCoords[brick + '2'].xCoord, gameCoords::cardsCoords[brick].yCoord, 0, to_string(player1Cards.brick).c_str());
		al_draw_text(fontForAmountOfCards, al_color_name("black"), gameCoords::cardsCoords[wool + '2'].xCoord, gameCoords::cardsCoords[wool].yCoord, 0, to_string(player1Cards.wool).c_str());
		al_draw_text(fontForAmountOfCards, al_color_name("black"), gameCoords::cardsCoords[wood + '2'].xCoord, gameCoords::cardsCoords[wood].yCoord, 0, to_string(player1Cards.wood).c_str());
		al_draw_text(fontForAmountOfCards, al_color_name("black"), gameCoords::cardsCoords[wheat + '2'].xCoord, gameCoords::cardsCoords[wheat].yCoord, 0, to_string(player1Cards.wheat).c_str());
	}
	else if (myGame->isSelecting() == ROBBER_CARDS)
	{
		cards player1DiscardCards = myGame->getP1DiscardRobberCards();
		string ore = "ORE";
		string brick = "BRICK";
		string wool = "WOOL";
		string wood = "WOOD";
		string wheat = "WHEAT";
		al_draw_text(fontForAmountOfCards, al_color_name("black"), gameCoords::cardsCoords[ore + '1'].xCoord, gameCoords::cardsCoords[ore].yCoord, 0, to_string(player1DiscardCards.ore).c_str());
		al_draw_text(fontForAmountOfCards, al_color_name("black"), gameCoords::cardsCoords[brick + '1'].xCoord, gameCoords::cardsCoords[brick].yCoord, 0, to_string(player1DiscardCards.brick).c_str());
		al_draw_text(fontForAmountOfCards, al_color_name("black"), gameCoords::cardsCoords[wool + '1'].xCoord, gameCoords::cardsCoords[wool].yCoord, 0, to_string(player1DiscardCards.wool).c_str());
		al_draw_text(fontForAmountOfCards, al_color_name("black"), gameCoords::cardsCoords[wood + '1'].xCoord, gameCoords::cardsCoords[wood].yCoord, 0, to_string(player1DiscardCards.wood).c_str());
		al_draw_text(fontForAmountOfCards, al_color_name("black"), gameCoords::cardsCoords[wheat + '1'].xCoord, gameCoords::cardsCoords[wheat].yCoord, 0, to_string(player1DiscardCards.wheat).c_str());
	}
}

gameModelViewer::~gameModelViewer()
{
}

