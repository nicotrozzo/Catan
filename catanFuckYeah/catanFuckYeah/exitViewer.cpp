#include "exitViewer.h"
using namespace std;


exitViewer::exitViewer()
{
	initOk = false;
	if ((exitButtonForMainMenuBitmap = al_load_bitmap("graficoCatan\\buttons\\gameExitButton.png")) != NULL)
	{
		if((exitButtonForGameBitmap = al_load_bitmap("graficoCatan\\buttons\\buttonexit1.png")))
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
}

