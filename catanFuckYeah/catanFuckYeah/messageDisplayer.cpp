#include "messageDisplayer.h"
#include "gameDefines.h"
#include <allegro5/allegro_ttf.h>

using namespace std;

messageDisplayer::messageDisplayer()
{
	initOk = false;
	tickCountForRefresh = 0;
	angle = 0;
	if ((messageShowBitmap = al_load_bitmap("graficoCatan\\menues\\messageShow.png")) != NULL)
	{
		if ((fontForMessageShow = al_load_ttf_font("graficoCatan\\font\\scribish.ttf", 71 * PROP_X, 0)) != NULL)
		{
			if ((refreshBitmap = al_load_bitmap("graficoCatan\\refresh.png")) != NULL)
			{
				initOk = true;
			}
		}
	}

}

void messageDisplayer::refresh()
{
	if (initOk)
	{
		showMessage();
		al_flip_display();
	}
}

bool messageDisplayer::getInitOk()
{
	return initOk;
}

void messageDisplayer::setMessage(string message)
{
	this->message = message;
}

void messageDisplayer::showMessage()
{
	if (message == "Waiting to quit...")
	{
		al_draw_scaled_rotated_bitmap(messageShowBitmap, 0, 0, 323 * PROP_X, 330 * PROP_Y, PROP_X, PROP_Y, 0, 0);
		al_draw_text(fontForMessageShow, al_color_name("white"), 344 * PROP_X, 410 * PROP_Y, 0, message.c_str());
		showRefresh();
	}
	else if(message.length() > 0)	//si se hace un setMessage("") no muestra nada
	{
		//texto normal con fondo abajo de la pantalla
	}
}

void messageDisplayer::showRefresh()
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
	al_draw_scaled_rotated_bitmap(refreshBitmap, al_get_bitmap_width(refreshBitmap) / 2.0, al_get_bitmap_height(refreshBitmap) / 2.0, 800 * PROP_X, 528 * PROP_Y,PROP_X,PROP_Y, angle, 0);
}

messageDisplayer::~messageDisplayer()
{
	al_destroy_bitmap(messageShowBitmap);
	al_destroy_bitmap(refreshBitmap);
	al_destroy_font(fontForMessageShow);
}


