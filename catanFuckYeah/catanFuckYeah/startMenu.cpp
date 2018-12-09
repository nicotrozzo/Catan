#include "startMenu.h"
using namespace std;

startMenu::startMenu()
{
	initOk = false;
	if ((menuBitmap = al_load_bitmap("graficoCatan\\menues\\mainmenu.png")) != NULL || (playBitmap = al_load_bitmap("graficoCatan\\buttons\\buttonplay1.png")) != NULL || (exitBitmap = al_load_bitmap("graficoCatan\\buttons\\buttonexit1.png")) != NULL)
	{
		initOk = true;
		al_draw_bitmap(menuBitmap, 0, 0, 0);
		al_draw_bitmap(playBitmap, al_get_display_width(allInit.getDisplay()) / 4, al_get_display_height(allInit.getDisplay()) / 2, 0);
		al_draw_bitmap(exitBitmap, 2 * al_get_display_width(allInit.getDisplay()) / 4, al_get_display_height(allInit.getDisplay()) / 2, 0);
	}
}


void startMenu::refresh()
{
		al_flip_display();
}

void startMenu::getInitOk()
{
	return initOK;
}

startMenu::~startMenu()
{
	al_destroy_bitmap(menuBitmap);
	al_destroy_bitmap(playBitmap);
	al_destroy_bitmap(exitBitmap);
}
