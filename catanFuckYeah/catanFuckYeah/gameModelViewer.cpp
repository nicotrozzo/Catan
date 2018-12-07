#include "gameModelViewer.h"



gameModelViewer::gameModelViewer(catanGameModel *myGame)
{
	initOk = false;
	this->myGame = myGame;
	if ((diceValue1 = al_load_bitmap("graficoCatan\\dados\\1.png")) != NULL && (diceValue2 = al_load_bitmap("graficoCatan\\dados\\2.png")) != NULL(diceValue3 = al_load_bitmap("graficoCatan\\dados\\3.png")) != NULL(diceValue4 = al_load_bitmap("graficoCatan\\dados\\4.png")) != NULL(diceValue5 = al_load_bitmap("graficoCatan\\dados\\5.png")) != NULL(diceValue6 = al_load_bitmap("graficoCatan\\dados\\6.png")) != NULL)
	{
		initOk = true;
	}
}

void gameModelViewer::update()
{
	if (initOk)
	{

	}
	else
	{

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



gameModelViewer::~gameModelViewer()
{
}

