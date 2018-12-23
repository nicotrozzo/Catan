#include "waitingGame.h"
#include "gameDefines.h"

using namespace std;


waitingGame::waitingGame()
{
	initOk = false;
	i = 0;
	angle = 0;
	tickCountForWallpaper = 0;
	tickCountForRefresh = 0;
	if ((bitmapArray[0] = al_load_bitmap("graficoCatan\\menues\\loadingMenu1.png")) != NULL && (bitmapArray[1] = al_load_bitmap("graficoCatan\\menues\\loadingMenu2.png")) != NULL && (bitmapArray[2] = al_load_bitmap("graficoCatan\\menues\\loadingMenu3.png")) != NULL && (bitmapArray[3] = al_load_bitmap("graficoCatan\\menues\\loadingMenu4.png")) != NULL)
	{
		if ((refreshBitmap = al_load_bitmap("graficoCatan\\refresh.png")) != NULL)
		{
			if ((fontForMessage = al_load_ttf_font("graficoCatan\\font\\TravelingTypewriter.ttf", 30,0))!=NULL)
			{
				if ((exitButtonBitmap = al_load_bitmap("graficoCatan\\buttons\\gameExitButton.png")) != NULL)
				{

					initOk = true;
				}
			}
		}
	}
}

void waitingGame::refresh()
{
	showWallpapers();
	showRefresh();
	showExitButton();
	showMessage();
	al_flip_display();
}

void waitingGame::showMessage()
{
	al_draw_text(fontForMessage, al_color_name("white"), 7, 7, 0,message.c_str());
}

void waitingGame::setMessage(string message)
{
	this->message = message;
}

bool waitingGame::getInitOk()
{
	return initOk;
}

void waitingGame::showExitButton()
{
	al_draw_scaled_rotated_bitmap(exitButtonBitmap, 0, 0, gameCoords::buttonCoords["EXIT"].xCoord, gameCoords::buttonCoords["EXIT"].yCoord, PROP_X, PROP_Y, 0, 0);
}

void waitingGame::showWallpapers()
{
	tickCountForWallpaper++;
	if (tickCountForWallpaper == 150)
	{
		tickCountForWallpaper = 0;
		i++;
		if (i == 4)
		{
			i = 0;
		}
	}
	al_draw_bitmap(bitmapArray[i], 0, 0, 0);
}

void waitingGame::showRefresh()
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
	al_draw_rotated_bitmap(refreshBitmap, al_get_bitmap_width(refreshBitmap) / 2.0, al_get_bitmap_height(refreshBitmap) / 2.0, 1575*PROP_X, 935*PROP_Y, angle, 0);
}

waitingGame::~waitingGame()
{
	al_destroy_bitmap(refreshBitmap);
	for (int i = 0; i < 3; i++)
	{
		al_destroy_bitmap(bitmapArray[i]);
	}
	al_destroy_font(fontForMessage);
	al_destroy_bitmap(exitButtonBitmap);
}
