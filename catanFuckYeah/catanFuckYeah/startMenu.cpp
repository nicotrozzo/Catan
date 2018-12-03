#include "startMenu.h"
using namespace std;

dibujator::dibujator()
{
}


bool dibujator::menuImageLoad()
{
	if ((menuBitmap = al_load_bitmap("graficoCatan\\menues\\mainmenu.png")) == NULL || (playBitmap = al_load_bitmap("graficoCatan\\buttons\\buttonplay1.png")) == NULL || (exitBitmap = al_load_bitmap("graficoCatan\\buttons\\buttonexit1.png")) == NULL)
	{
		return false;
	}
	else
	{
		al_draw_bitmap(menuBitmap, 0, 0, 0);
		al_draw_bitmap(playBitmap, al_get_display_width(allInit.getDisplay()) / 4, al_get_display_height(allInit.getDisplay()) / 2, 0);
		al_draw_bitmap(exitBitmap, 2 * al_get_display_width(allInit.getDisplay()) / 4, al_get_display_height(allInit.getDisplay()) / 2, 0);
		al_flip_display();
	}
	//else if((al))
	return true;
}


dibujator::~dibujator()
{
}
