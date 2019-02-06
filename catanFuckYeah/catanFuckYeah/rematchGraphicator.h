#pragma once
#include "graphicator.h"
#include <allegro5/allegro_color.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
class rematchGraphicator :	public graphicator
{
public:
	rematchGraphicator(bool p1Won);
	void refresh();
	void toggleState();
	bool getInitOk();
	~rematchGraphicator();
private:
	bool p1Won;
	bool waitingInput;
	bool initOk;
	ALLEGRO_BITMAP * wallPaperBitmap;
	ALLEGRO_BITMAP * playAgainButton;
	ALLEGRO_BITMAP * rematchButton;
	ALLEGRO_BITMAP * scapeButton;
	ALLEGRO_BITMAP * refreshBitmap;
	ALLEGRO_FONT * fontForWinnerLooser;
	ALLEGRO_FONT * fontForWaiting;
	void writeMessage();
	void viewWallPaper();
	void buttonViewer();
	void waitingOpponent();
	int tickCountForRefresh;
	int i;
	float angle;
};

