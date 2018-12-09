#include "exitViewer.h"
using namespace std;


exitViewer::exitViewer()
{
	initOk = false;
	if ((exitButton = al_load_bitmap("graficoCatan\\buttons\\gameExitButton.png")) != NULL)
	{
	
		initOk = true;
	}
}

void exitViewer::update()
{
	if (initOk)
	{
		viewExitButton();
	}
	else
	{
		cout << "error de exitButton" << endl;
	}
}

void exitViewer::viewExitButton()
{
	if (isInMenu)
	{
		al_draw_bitmap(exitButtonBitmap, )
	}
}

exitViewer::~exitViewer()
{
	al_destroy_bitmap(exitButtonForMainMenuBitmap);
	al_destroy_bitmap(exitButtonForGameBitmap);
}

