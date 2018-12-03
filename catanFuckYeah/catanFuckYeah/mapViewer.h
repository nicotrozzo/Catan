#pragma once
#include "catanMapModel.h"
#include "allegroInit.h"
#include "observer.h"
#include <allegro5/allegro_color.h>
#include <string>


class mapViewer : public observer
{
public:
	mapViewer();
	void update();
	~mapViewer();
public:
	void viewHex();
	void viewTokens();
	void viewBuildings();
	void viewRobber();
	void viewBankTrade();			//no se donde hacer tema trades
};

