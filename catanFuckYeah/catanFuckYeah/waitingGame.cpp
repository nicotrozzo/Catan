#include "waitingGame.h"

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
				initOk = true;
			}
		}
	}
}

void waitingGame::refresh()
{
	showWallpapers();
	showRefresh();
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

void waitingGame::showWallpapers()
{
	tickCountForWallpaper++;
	if (tickCountForWallpaper == 100)
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
	if (tickCountForWallpaper == 5)
	{
		tickCountForWallpaper = 0;
		angle += 3 * PI / 180.0;
		if (angle > 2 * PI)
		{
			angle = 0;
		}
	}
	al_draw_rotated_bitmap(refreshBitmap, al_get_bitmap_width(refreshBitmap) / 2.0, al_get_bitmap_height(refreshBitmap) / 2.0, 1575, 935, angle, 0);
}

waitingGame::~waitingGame()
{
	al_destroy_bitmap(refreshBitmap);
	for (int i = 0; i < 3; i++)
	{
		al_destroy_bitmap(bitmapArray[i]);
	}
	al_destroy_font(fontForMessage);
}
