#include "gameModelViewer.h"
#include <allegro5/allegro_ttf.h>

gameModelViewer::gameModelViewer(catanGameModel *myGame)
{
	initOk = false;
	this->myGame = myGame;
	if ((diceValue1 = al_load_bitmap("graficoCatan\\dados\\1.png")) != NULL && (diceValue2 = al_load_bitmap("graficoCatan\\dados\\2.png")) != NULL && (diceValue3 = al_load_bitmap("graficoCatan\\dados\\3.png")) != NULL && (diceValue4 = al_load_bitmap("graficoCatan\\dados\\4.png")) != NULL && (diceValue5 = al_load_bitmap("graficoCatan\\dados\\5.png")) != NULL && (diceValue6 = al_load_bitmap("graficoCatan\\dados\\6.png")) != NULL)
	{
		if ((tradeMenuBitmap = al_load_bitmap("graficoCatan\\menues\\menuDeTrueque.png")) != NULL)
		{
			if ((robberDiscardMenuBitmap = al_load_bitmap("graficoCatan\\menues\\menuDeLadron.png")) != NULL)
			{
				if ((fontForAmountOfCards = al_load_ttf_font("graficoCatan\\font\\scribish.ttf", 37 * PROP_Y, 0)) != NULL)
				{
					if ((fontForBankCosts = al_load_ttf_font("graficoCatan\\font\\scribish.ttf", 42 * PROP_Y, 0)) != NULL)
					{
						if ((tickBitmap = al_load_bitmap("graficoCatan\\buttons\\yes.png")) != NULL && (crossBitmap = al_load_bitmap("graficoCatan\\buttons\\no.png")) != NULL)
						{
							if ((passButtonBitmap = al_load_bitmap("graficoCatan\\buttons\\passButton.png")) != NULL && (bankTradeButtonBitmap = al_load_bitmap("graficoCatan\\buttons\\bankTrade.png")) != NULL && (playerTradeButtonBitmap = al_load_bitmap("graficoCatan\\buttons\\playerTrade.png")) != NULL)
							{
								if ((exitButtonBitmap = al_load_bitmap("graficoCatan\\buttons\\gameExitButton.png")) != NULL)
								{

									initOk = true;
								}
							}
						}
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
		viewTurn();
		viewExitButton();
		if (!myGame->initState())
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
			if (myGame->isPlayer1Playing())
			{
				if ((myGame->isConstructing()) || (myGame->isSelecting()))
				{
					viewTickAndCrossButtons();
				}
				else
				{
					viewActionButtons();
				}
			}
			else if (myGame->isSelecting())
			{
				viewTickAndCrossButtons();
			}
		}
		else if (myGame->isPlayer1Playing() && ((myGame->isConstructing()) || (myGame->isSelecting())))
		{
			viewTickAndCrossButtons();
		}
	}
	else
	{
		cout << "Error en gameModelViewer" << endl;
	}
}

bool gameModelViewer::getInitOk()
{
	return initOk;
}

void gameModelViewer::viewDices()
{
	unsigned char dice1 = myGame->getDice1();
	unsigned char dice2 = myGame->getDice2();
	switch (dice1)
	{
	case 1:
		al_draw_scaled_rotated_bitmap(diceValue1,0,0, 1384 * PROP_X, 416 * PROP_Y,PROP_X,PROP_Y,0, 0);
		break;
	case 2:
		al_draw_scaled_rotated_bitmap(diceValue2,0,0, 1384 * PROP_X, 416 * PROP_Y,PROP_X, PROP_Y,0, 0);
		break;
	case 3:
		al_draw_scaled_rotated_bitmap(diceValue3, 0, 0, 1384 * PROP_X, 416 * PROP_Y, PROP_X, PROP_Y, 0, 0);
		break;
	case 4:
		al_draw_scaled_rotated_bitmap(diceValue4, 0, 0, 1384 * PROP_X, 416 * PROP_Y, PROP_X, PROP_Y, 0, 0);
		break;
	case 5:
		al_draw_scaled_rotated_bitmap(diceValue5, 0, 0, 1384 * PROP_X, 416 * PROP_Y, PROP_X, PROP_Y, 0, 0);
		break;
	case 6:
		al_draw_scaled_rotated_bitmap(diceValue6, 0, 0, 1384 * PROP_X, 416 * PROP_Y, PROP_X, PROP_Y, 0, 0);
		break;
	}
	switch (dice2)
	{
	case 1:
		al_draw_scaled_rotated_bitmap(diceValue1, 0, 0, 1510 * PROP_X, 485 * PROP_Y, PROP_X, PROP_Y, 0, 0);
		break;
	case 2:
		al_draw_scaled_rotated_bitmap(diceValue2, 0, 0, 1510 * PROP_X, 485 * PROP_Y, PROP_X, PROP_Y, 0, 0);
		break;
	case 3:
		al_draw_scaled_rotated_bitmap(diceValue3, 0, 0, 1510 * PROP_X, 485 * PROP_Y, PROP_X, PROP_Y, 0, 0);
		break;
	case 4:
		al_draw_scaled_rotated_bitmap(diceValue4, 0, 0, 1510 * PROP_X, 485 * PROP_Y, PROP_X, PROP_Y, 0, 0);
		break;
	case 5:
		al_draw_scaled_rotated_bitmap(diceValue5, 0, 0, 1510 * PROP_X, 485 * PROP_Y, PROP_X, PROP_Y, 0, 0);
		break;
	case 6:
		al_draw_scaled_rotated_bitmap(diceValue6, 0, 0, 1510 * PROP_X, 485 * PROP_Y, PROP_X, PROP_Y, 0, 0);
		break;
	}
}

void gameModelViewer::viewTrade()
{
	al_draw_scaled_rotated_bitmap(tradeMenuBitmap,0,0,0,0,PROP_X,PROP_Y,0,0);
	if (myGame->isSelecting() == BANK_TRADE)
	{
		map<resourceType, unsigned char> costs = myGame->getBankTradeCosts();
		al_draw_text(fontForBankCosts, al_color_name("black"), 489 * PROP_X, 118 * PROP_Y, 0, (to_string(costs[ORE] ) + "x1").c_str());
		al_draw_text(fontForBankCosts, al_color_name("black"), 668 * PROP_X, 118 * PROP_Y, 0, (to_string(costs[WHEAT] ) + "x1").c_str());
		al_draw_text(fontForBankCosts, al_color_name("black"), 853 * PROP_X, 118 * PROP_Y, 0, (to_string(costs[WOOL] ) + "x1").c_str());
		al_draw_text(fontForBankCosts, al_color_name("black"), 1019 * PROP_X, 118 * PROP_Y, 0, (to_string(costs[WOOD] ) + "x1").c_str());
		al_draw_text(fontForBankCosts, al_color_name("black"), 1199 * PROP_X, 118 * PROP_Y, 0, (to_string(costs[BRICK] ) + "x1").c_str());
	}
}

void gameModelViewer::viewRobberDiscard()
{
	al_draw_scaled_rotated_bitmap(robberDiscardMenuBitmap,0,0,0,0,PROP_X,PROP_Y,0,0);
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
		if (playerAccess.length() > 0)
		{
			playerAccess += '1';
			bankAccess += '2';
			coords playerCardCoords = { gameCoords::cardsCoords[playerAccess].xCoord, gameCoords::cardsCoords[playerAccess].yCoord , MAP_NONE };
			coords bankCardCoords = { gameCoords::cardsCoords[bankAccess].xCoord, gameCoords::cardsCoords[bankAccess].yCoord , MAP_NONE };
			al_draw_text(fontForAmountOfCards, al_color_name("black"), playerCardCoords.xCoord - 2, playerCardCoords.yCoord, 0, to_string(playerCards.resCount).c_str());
			al_draw_text(fontForAmountOfCards, al_color_name("black"), bankCardCoords.xCoord - 2, bankCardCoords.yCoord, 0, "1");
		}
	}
	else if (myGame->isSelecting() == OFFER_TRADE)
	{
		cards player1Cards = myGame->getP1SelectedCardsForTrade();
		cards player2Cards = myGame->getP2SelectedCardsForTrade();
		string ore = "ORE";
		string brick = "BRICK";
		string wool = "WOOL";
		string wood = "WOOD";
		string wheat = "WHEAT";
		al_draw_text(fontForAmountOfCards, al_color_name("black"), gameCoords::cardsCoords[ore + '1'].xCoord, gameCoords::cardsCoords[ore + '1'].yCoord, 0, to_string(player1Cards.ore).c_str());
		al_draw_text(fontForAmountOfCards, al_color_name("black"), gameCoords::cardsCoords[brick + '1'].xCoord, gameCoords::cardsCoords[brick + '1'].yCoord, 0, to_string(player1Cards.brick).c_str());
		al_draw_text(fontForAmountOfCards, al_color_name("black"), gameCoords::cardsCoords[wool + '1'].xCoord, gameCoords::cardsCoords[wool + '1'].yCoord, 0, to_string(player1Cards.wool).c_str());
		al_draw_text(fontForAmountOfCards, al_color_name("black"), gameCoords::cardsCoords[wood + '1'].xCoord, gameCoords::cardsCoords[wood + '1'].yCoord, 0, to_string(player1Cards.wood).c_str());
		al_draw_text(fontForAmountOfCards, al_color_name("black"), gameCoords::cardsCoords[wheat + '1'].xCoord, gameCoords::cardsCoords[wheat + '1'].yCoord, 0, to_string(player1Cards.wheat).c_str());
		al_draw_text(fontForAmountOfCards, al_color_name("black"), gameCoords::cardsCoords[ore + '2'].xCoord, gameCoords::cardsCoords[ore + '2'].yCoord, 0, to_string(player2Cards.ore).c_str());
		al_draw_text(fontForAmountOfCards, al_color_name("black"), gameCoords::cardsCoords[brick + '2'].xCoord, gameCoords::cardsCoords[brick + '2'].yCoord, 0, to_string(player2Cards.brick).c_str());
		al_draw_text(fontForAmountOfCards, al_color_name("black"), gameCoords::cardsCoords[wool + '2'].xCoord, gameCoords::cardsCoords[wool + '2'].yCoord, 0, to_string(player2Cards.wool).c_str());
		al_draw_text(fontForAmountOfCards, al_color_name("black"), gameCoords::cardsCoords[wood + '2'].xCoord, gameCoords::cardsCoords[wood + '2'].yCoord, 0, to_string(player2Cards.wood).c_str());
		al_draw_text(fontForAmountOfCards, al_color_name("black"), gameCoords::cardsCoords[wheat + '2'].xCoord, gameCoords::cardsCoords[wheat + '2'].yCoord, 0, to_string(player2Cards.wheat).c_str());
	}
	else if (myGame->isSelecting() == ROBBER_CARDS)
	{
		cards player1DiscardCards = myGame->getP1DiscardRobberCards();
		string ore = "ORE";
		string brick = "BRICK";
		string wool = "WOOL";
		string wood = "WOOD";
		string wheat = "WHEAT";
		al_draw_text(fontForAmountOfCards, al_color_name("black"), gameCoords::cardsCoords[ore + '1'].xCoord - 2, gameCoords::cardsCoords[ore + '1'].yCoord + 2, 0, to_string(player1DiscardCards.ore).c_str());
		al_draw_text(fontForAmountOfCards, al_color_name("black"), gameCoords::cardsCoords[brick + '1'].xCoord - 2, gameCoords::cardsCoords[brick + '1'].yCoord + 2, 0, to_string(player1DiscardCards.brick).c_str());
		al_draw_text(fontForAmountOfCards, al_color_name("black"), gameCoords::cardsCoords[wool + '1'].xCoord - 2, gameCoords::cardsCoords[wool + '1'].yCoord + 2, 0, to_string(player1DiscardCards.wool).c_str());
		al_draw_text(fontForAmountOfCards, al_color_name("black"), gameCoords::cardsCoords[wood + '1'].xCoord - 2, gameCoords::cardsCoords[wood + '1'].yCoord + 5, 0, to_string(player1DiscardCards.wood).c_str());
		al_draw_text(fontForAmountOfCards, al_color_name("black"), gameCoords::cardsCoords[wheat + '1'].xCoord - 2, gameCoords::cardsCoords[wheat + '1'].yCoord + 2, 0, to_string(player1DiscardCards.wheat).c_str());
	}
}

void gameModelViewer::viewTickAndCrossButtons()
{
	al_draw_scaled_rotated_bitmap(tickBitmap,0,0, gameCoords::buttonCoords["YES"].xCoord, gameCoords::buttonCoords["YES"].yCoord, PROP_X,PROP_Y,0,0);
	al_draw_scaled_rotated_bitmap(crossBitmap, 0, 0, gameCoords::buttonCoords["NO"].xCoord, gameCoords::buttonCoords["NO"].yCoord, PROP_X, PROP_Y, 0, 0);
}

void gameModelViewer::viewActionButtons()
{
	al_draw_scaled_rotated_bitmap(passButtonBitmap, 0,0,gameCoords::buttonCoords["END_TURN"].xCoord, gameCoords::buttonCoords["END_TURN"].yCoord,PROP_X,PROP_Y,0, 0);
	al_draw_scaled_rotated_bitmap(playerTradeButtonBitmap,0,0, gameCoords::buttonCoords["PLAYER_TRADE"].xCoord, gameCoords::buttonCoords["PLAYER_TRADE"].yCoord, PROP_X,PROP_Y,0,0);
	al_draw_scaled_rotated_bitmap(bankTradeButtonBitmap, 0,0,gameCoords::buttonCoords["BANK_TRADE"].xCoord, gameCoords::buttonCoords["BANK_TRADE"].yCoord,PROP_X,PROP_Y,0, 0);
}

void gameModelViewer::viewExitButton()
{
	al_draw_scaled_rotated_bitmap(exitButtonBitmap,0,0, gameCoords::buttonCoords["EXIT"].xCoord, gameCoords::buttonCoords["EXIT"].yCoord,PROP_X,PROP_Y,0, 0);
}

void gameModelViewer::viewTurn()
{
	string text = myGame->getCurrentPlayer()->getName() + "'s turn";
	al_draw_text(fontForAmountOfCards, al_color_name("black"), 660*PROP_X, 3, 0, text.c_str());
}

gameModelViewer::~gameModelViewer()
{
	al_destroy_bitmap(diceValue1);
	al_destroy_bitmap(diceValue2);
	al_destroy_bitmap(diceValue3);
	al_destroy_bitmap(diceValue4);
	al_destroy_bitmap(diceValue5);
	al_destroy_bitmap(diceValue6);
	al_destroy_bitmap(tradeMenuBitmap);
	al_destroy_bitmap(robberDiscardMenuBitmap);
	al_destroy_bitmap(tickBitmap);
	al_destroy_bitmap(crossBitmap);
	al_destroy_bitmap(passButtonBitmap);
	al_destroy_bitmap(bankTradeButtonBitmap);
	al_destroy_bitmap(playerTradeButtonBitmap);
	al_destroy_bitmap(exitButtonBitmap);
	al_destroy_font(fontForAmountOfCards);
	al_destroy_font(fontForBankCosts);
}

