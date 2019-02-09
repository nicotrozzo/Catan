#include "gameGraphicator.h"
#include <allegro5/allegro_ttf.h>
#include "gameDefines.h"
#include "gameCoords.h"

using namespace std;

gameGraphicator::gameGraphicator()
{
	message = "";
	initOk = false;
	if ((backgroundBitmap = al_load_bitmap("graficoCatan\\menues\\messageBackground.png")) != NULL)
	{
		if ((fontForMessages = al_load_ttf_font("graficoCatan\\font\\PrinceValiant.ttf", 31 * PROP_Y, 0)) != NULL)
		{
			initOk = true;
		}
	}
}

void gameGraphicator::refresh()
{
	if(initOk)
	{
		if (message.length() > 0)
		{
			al_draw_scaled_rotated_bitmap(backgroundBitmap, 0, 0, 456 * PROP_X, 0, PROP_X, PROP_Y, 0, 0);
			writeMessage();
		}
		al_flip_display();
	}
	else
	{
		std::cout << "error en gameGraphicator" << endl;
	}
}

void gameGraphicator::writeMessage()
{
	if (message.length() < 15)
	{
		message.insert(0, "		a	");
		al_draw_text(fontForMessages, al_color_name("black"), 476 * PROP_X, 5 * PROP_Y, 0, message.c_str());
	}
	else if(message.length() < 23)
	{
		message.insert(0, "		");
		al_draw_text(fontForMessages, al_color_name("black"), 476 * PROP_X, 5 * PROP_Y, 0, message.c_str());
	}
	else
	{
		message.insert(0, "	");
		al_draw_text(fontForMessages, al_color_name("black"), 476 * PROP_X, 5 * PROP_Y, 0, message.c_str());
	}
}

void gameGraphicator::setMessage(string message_)
{
	message = message_;
}

gameGraphicator::~gameGraphicator()
{
	al_destroy_bitmap(backgroundBitmap);
	al_destroy_font(fontForMessages);
}


