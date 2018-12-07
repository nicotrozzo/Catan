#include "gameModelViewer.h"



gameModelViewer::gameModelViewer(catanGameModel *myGame)
{
	initOk = false;
	this->myGame = myGame;
	if ((dice1 = al_load_bitmap("graficoCatan\\dados\\1.png")) != NULL && (dice2 = al_load_bitmap("graficoCatan\\dados\\2.png")) != NULL(dice3 = al_load_bitmap("graficoCatan\\dados\\3.png")) != NULL(dice4 = al_load_bitmap("graficoCatan\\dados\\4.png")) != NULL(dice5 = al_load_bitmap("graficoCatan\\dados\\5.png")) != NULL(dice6 = al_load_bitmap("graficoCatan\\dados\\6.png")) != NULL)
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

}



gameModelViewer::~gameModelViewer()
{
}

