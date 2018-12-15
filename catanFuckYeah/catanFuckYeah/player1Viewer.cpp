#include "player1Viewer.h"
#include <allegro5/allegro_ttf.h>


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
				if ((fontForAmountOfCards = al_load_ttf_font("graficoCatan\\font\\scribish.ttf", 40, 0)) != NULL)
				{
					if ((fontForLongestRoad = al_load_ttf_font("graficoCatan\\font\\scribish.ttf", 30, 0)) != NULL)
					{
						initOk = true;
					}
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

bool player1Viewer::getInitOk()
{
	return initOk;
}


void player1Viewer::viewVictoryPoints()
{
	unsigned char victoryPoints = player->getVictoryPoints();
	string points = to_string(victoryPoints);
	al_draw_text(fontForVictoryPoints, al_color_name("black"), 148, 575, 0, points.c_str());
}

void player1Viewer::viewNameIs()
{
	string name = player->getName();
	if (name.size() == 0)
	{
		al_draw_text(fontForName, al_color_name("black"), 27, 28, 0, "Player1");
	}
	else
	{
		al_draw_text(fontForName, al_color_name("black"), 27, 28, 0, (name.substr(0,6)).c_str());
	}
}

void player1Viewer::viewResources()
{
	unsigned char ore = (player->getCards()).ore;
	unsigned char brick = (player->getCards()).brick;
	unsigned char wool = (player->getCards()).wool;
	unsigned char wheat = (player->getCards()).wheat;
	unsigned char wood = (player->getCards()).wood;
	al_draw_text(fontForResources, al_color_name("black"), 15, 150, 0, to_string(ore).c_str());
	al_draw_text(fontForResources, al_color_name("black"), 115, 150, 0, to_string(wheat).c_str());
	al_draw_text(fontForResources, al_color_name("black"), 215, 150, 0, to_string(brick).c_str());
	al_draw_text(fontForResources, al_color_name("black"), 56, 275, 0, to_string(wood).c_str());
	al_draw_text(fontForResources, al_color_name("black"), 159, 275, 0, to_string(wool).c_str());
}

void player1Viewer::viewLongestRoads()
{
	al_draw_text(fontForLongestRoad, al_color_name("black"), 74, 469, 0, to_string(player->getLongestRoad()).c_str());
}

void player1Viewer::viewAmountOfCards()
{
	unsigned char amountOfCards = player->getAmountOfCards();
	if (amountOfCards > 9)
	{
		al_draw_text(fontForAmountOfCards, al_color_name("black"), 248, 461, 0, to_string(amountOfCards).c_str());
	}
	else
	{

		al_draw_text(fontForVictoryPoints, al_color_name("black"), 252, 461, 0, to_string(amountOfCards).c_str());
	}
}


player1Viewer::~player1Viewer()
{
	al_destroy_font(fontForVictoryPoints);
	al_destroy_font(fontForName);
	al_destroy_font(fontForAmountOfCards);
	al_destroy_font(fontForLongestRoad);
	al_destroy_font(fontForResources);
}
