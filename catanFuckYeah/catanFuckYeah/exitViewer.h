#pragma once
#include "observer.h"
#include "allegroInit.h"
#include "gameCoords.h"

class exitViewer : public observer
{
public:
	exitViewer();
	void update();
	void setIsInMenu(bool inMenu) { isInMenu = inMenu; }
	~exitViewer();
private:
	ALLEGRO_BITMAP *exitButtonForGameBitmap;
	ALLEGRO_BITMAP *exitButtonForMainMenuBitmap;
	void viewExitButton();
	bool initOk;
	bool isInMenu;
};

