#include "rematchGraphicator.h"
#include "gameDefines.h"
#include "gameCoords.h"
#include <allegro5/allegro_ttf.h>

rematchGraphicator::rematchGraphicator(bool p1Won)
{
	i = 0;
	angle = 0;
	tickCountForRefresh = 0;
	this->p1Won = p1Won;
	waitingInput = p1Won; //si gano p1 arranca esperando input
	initOk = false;
	if ((wallPaperBitmap = al_load_bitmap("graficoCatan\\menues\\rematchMenu.png")) != NULL)
	{
		if((fontForWinnerLooser = al_load_ttf_font("graficoCatan\\font\\scribish.ttf", 69 * PROP_Y, 0)) != NULL)
		{
			if ((rematchButton = al_load_bitmap("graficoCatan\\buttons\\rematchButton.png")) != NULL)
			{
				if ((playAgainButton = al_load_bitmap("graficoCatan\\menues\\playAgainButton.png")) != NULL)
				{
					if ((scapeButton = al_load_bitmap("graficoCatan\\menues\\finalExitButton.png")) != NULL)
					{
						if ((refreshBitmap = al_load_bitmap("graficoCatan\\refresh.png")) != NULL)
						{
							if ((fontForWaiting = al_load_ttf_font("graficoCatan\\font\\scribish.ttf", 91 * PROP_Y, 0)) != NULL)
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

void rematchGraphicator::refresh()
{
	if (initOk)
	{
		viewWallPaper();
		writeMessage();
		if (waitingInput)
		{
			buttonViewer();
		}
		else
		{
			waitingOpponent();
		}
	}
	else
	{
		cout << "Error en rematchGraphicator" << endl;
	}
}

void rematchGraphicator::toggleState()
{
	waitingInput = !waitingInput;
}

bool rematchGraphicator::getInitOk()
{
	return initOk;
}

void rematchGraphicator::writeMessage()
{
	if (p1Won)
	{
		al_draw_text(fontForWinnerLooser, al_color_name("red"), 74 * PROP_X,120 * PROP_Y, 0, "You won this match, congratulations!\n\t\t Do you dare to try again? ");
	}
	else
	{
		al_draw_text(fontForWinnerLooser, al_color_name("red"), 74 * PROP_X, 120 * PROP_Y, 0, "You have been defeated, what a pity!\n\t\t Do you want rematch? ");
	}
}

void rematchGraphicator::viewWallPaper()
{
	al_draw_scaled_rotated_bitmap(wallPaperBitmap, 0, 0, 0, 0, PROP_X, PROP_Y, 0, 0);
}

void rematchGraphicator::buttonViewer()
{
	if (p1Won)
	{
		al_draw_scaled_rotated_bitmap(playAgainButton, 0, 0, gameCoords::buttonCoords["REMATCH/PLAY_AGAIN"].xCoord , gameCoords::buttonCoords["REMATCH/PLAY_AGAIN"].yCoord, PROP_X, PROP_Y, 0, 0);
	}
	else
	{
		al_draw_scaled_rotated_bitmap(rematchButton, 0, 0, gameCoords::buttonCoords["REMATCH/PLAY_AGAIN"].xCoord, gameCoords::buttonCoords["REMATCH/PLAY_AGAIN"].yCoord, PROP_X, PROP_Y, 0, 0);
	}
	al_draw_scaled_rotated_bitmap(scapeButton, 0, 0, gameCoords::buttonCoords["SCAPE"].xCoord, gameCoords::buttonCoords["SCAPE"].yCoord, PROP_X, PROP_Y, 0, 0);
}

void rematchGraphicator::waitingOpponent()
{
	tickCountForRefresh++;
	if (tickCountForRefresh == 1)
	{
		tickCountForRefresh = 0;
		angle += 3 * PI / 180.0;
		if (angle > 2 * PI)
		{
			angle = 0;
		}
	}
	al_draw_text(fontForWaiting, al_color_name("red"), 20 * PROP_X, 888 * PROP_Y, 0, "Waiting opponent...");
	al_draw_rotated_bitmap(refreshBitmap, al_get_bitmap_width(refreshBitmap) / 2.0, al_get_bitmap_height(refreshBitmap) / 2.0, 1575 * PROP_X, 935 * PROP_Y, angle, 0);
}

rematchGraphicator::~rematchGraphicator()
{
	al_destroy_bitmap(playAgainButton);
	al_destroy_bitmap(rematchButton);
	al_destroy_bitmap(scapeButton);
	al_destroy_bitmap(wallPaperBitmap);
	al_destroy_bitmap(refreshBitmap);
	al_destroy_font(fontForWinnerLooser);
	al_destroy_font(fontForWaiting);
}
