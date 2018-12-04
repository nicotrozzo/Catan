#include "player2Viewer.h"


player2Viewer::player2Viewer(catanPlayerModel * player2)
{
	initOk = false;
	player = player2;
	if ((fontForVictoryPoints = al_load_ttf_font("font\\scribish", 55, 0)) != NULL)
	{
		if ((fontForName = al_load_ttf_font("font\\scribish", 59, 0)) != NULL)
		{
			if ((fontForAmountOfCards = al_load_ttf_font("font\\scribish", 59, 0)) != NULL)
			{
				initOk = true;
			}
		}
	}
}

void player2Viewer::update()
{
	viewAmountOfCards();
	viewLongestRoad();
	viewNameIs();
	viewVictoryPoints();
	al_flip_display();
}

void player2Viewer::viewNameIs()
{
	string name = player->getName();
	al_draw_text(fontForName, al_color_name("black"), 16, 20, 0, name.c_str());
}

void player2Viewer::viewLongestRoad()		//faltaaaaaaaaaaaaaaaaaaaaaaaaaa
{
}

void player2Viewer::viewAmountOfCards()
{
	unsigned char amountOfCards = player->getAmountOfCards();
	al_draw_text(fontForAmountOfCards, al_color_name("black"), 16, 20, 0, to_string(amountOfCards).c_str());
}

void player2Viewer::viewVictoryPoints()
{
	unsigned char victoryPoints = player->getVictoryPoints();
	string points = to_string(victoryPoints);
	al_draw_text(fontForVictoryPoints, al_color_name("black"), 129, 547, 0, points.c_str());
}

player2Viewer::~player2Viewer()
{
}

