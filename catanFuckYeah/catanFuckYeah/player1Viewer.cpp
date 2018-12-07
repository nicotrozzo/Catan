#include "player1Viewer.h"



player1Viewer::player1Viewer(catanPlayerModel * player1)
{
	initOk = false;
	player = player1;
	if ((fontForVictoryPoints = al_load_ttf_font("graficoCatan\\font\\scribish.ttf", 55, 0)) != NULL)
	{
		if ((fontForName = al_load_ttf_font("graficoCatan\\font\\scribish.ttf", 59, 0)) != NULL)
		{
			if ((fontForResources = al_load_ttf_font("graficoCatan\\font\\scribish.ttf", 31, 0)) != NULL)
			{
				if ((fontForAmountOfCards = al_load_ttf_font("graficoCatan\\font\\scribish.ttf", 59, 0)) != NULL)
				{
					initOk = true;
				}
			}
		}
	}
}

void player1Viewer::update()
{
	if (initOk)
	{
		viewAmountOfCards();
		viewLongestRoads();
		viewNameIs();
		viewResources();
		viewVictoryPoints();
	}
	else
	{
		cout << "error en player1" << endl;
	}
}


void player1Viewer::viewVictoryPoints()
{
	unsigned char victoryPoints = player->getVictoryPoints();
	string points = to_string(victoryPoints);
	al_draw_text(fontForVictoryPoints, al_color_name("black"), 148, 573, 0, points.c_str());
}

void player1Viewer::viewNameIs()
{
	string name = player->getName();
	al_draw_text(fontForName, al_color_name("black"), 27, 25, 0, name.c_str());
}

void player1Viewer::viewResources()
{
	unsigned char ore = (player->getCards()).ore;
	unsigned char brick = (player->getCards()).brick;
	unsigned char wool = (player->getCards()).wool;
	unsigned char wheat = (player->getCards()).wheat;
	unsigned char wood = (player->getCards()).wood;
	al_draw_text(fontForResources, al_color_name("black"), 12, 148, 0, to_string(ore).c_str());
	al_draw_text(fontForResources, al_color_name("black"), 112, 148, 0, to_string(wheat).c_str());
	al_draw_text(fontForResources, al_color_name("black"), 212, 148, 0, to_string(brick).c_str());
	al_draw_text(fontForResources, al_color_name("black"), 53, 272, 0, to_string(wood).c_str());
	al_draw_text(fontForResources, al_color_name("black"), 156, 272, 0, to_string(wool).c_str());
}

void player1Viewer::viewLongestRoads()		//faltaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
{
}

void player1Viewer::viewAmountOfCards()
{
	unsigned char amountOfCards = player->getAmountOfCards();
	al_draw_text(fontForAmountOfCards, al_color_name("black"), 250, 450, 0, to_string(amountOfCards).c_str());
}


player1Viewer::~player1Viewer()
{
}