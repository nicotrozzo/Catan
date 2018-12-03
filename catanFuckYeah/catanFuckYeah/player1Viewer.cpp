#include "player1Viewer.h"



player1Viewer::player1Viewer(catanPlayerModel * player1)
{
	player = player1;
}

void player1Viewer::update()
{
	
}

bool player1Viewer::viewVictoryPoints()
{
	bool ret = true;
	unsigned char victoryPoints = player->getVictoryPoints();
	string points = to_string(victoryPoints);
	if ((fontForVictoryPoints = al_load_ttf_font("font\\scribish", 11, 0)) != NULL)
	{
		al_draw_text(fontForVictoryPoints, al_color_name("black"), 125, 545, 0, points.c_str());
	}
	else
	{
		cout << "No se pudo crear font" << endl;
		ret = false;
	}
	al_shutdown_ttf_addon();
	return ret;
}

bool player1Viewer::viewNameIs()
{
	return false;
}

bool player1Viewer::viewResources()
{
	return false;
}

bool player1Viewer::viewLongestRoads()
{
	return false;
}

bool player1Viewer::viewAmountOfCards()
{
	return false;
}



player1Viewer::~player1Viewer()
{
}
