#include "player2Viewer.h"


player2Viewer::player2Viewer(catanPlayerModel * player2)
{
	initOk = false;
	player = player2;
	if ((fontForVictoryPoints = al_load_ttf_font("graficoCatan\\font\\scribish.ttf", 55, 0)) != NULL)
	{
		if ((fontForName = al_load_ttf_font("graficoCatan\\font\\scribish.ttf", 59, 0)) != NULL)
		{
			if ((fontForAmountOfCards = al_load_ttf_font("graficoCatan\\font\\scribish.ttf", 59, 0)) != NULL)
			{
				if ((fontForLongestRoad = al_load_ttf_font("graficoCatan\\font\\scribish.ttf", 30, 0)) != NULL)
				{
					initOk = true;
				}
			}
		}
	}
}

void player2Viewer::update()
{
	if (initOk)
	{
		viewAmountOfCards();
		viewLongestRoad();
		viewNameIs();
		viewVictoryPoints();
	}
	else
	{
		cout << "error player2" << endl;
	}

}
void player2Viewer::viewNameIs()
{
	string name = player->getName();
	al_draw_text(fontForName, al_color_name("black"), 27, 686, 0, name.c_str());
}

void player2Viewer::viewLongestRoad()
{
	al_draw_text(fontForLongestRoad, al_color_name("black"), 74, 794, 0, to_string(player->getLongestRoad()).c_str());
}

void player2Viewer::viewAmountOfCards()
{
	unsigned char amountOfCards = player->getAmountOfCards();
	al_draw_text(fontForAmountOfCards, al_color_name("black"), 250, 780, 0, to_string(amountOfCards).c_str());
}

void player2Viewer::viewVictoryPoints()
{
	unsigned char victoryPoints = player->getVictoryPoints();
	string points = to_string(victoryPoints);
	al_draw_text(fontForVictoryPoints, al_color_name("black"), 148, 900, 0, points.c_str());
}

player2Viewer::~player2Viewer()
{
}

