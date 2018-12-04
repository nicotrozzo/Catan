#include "mapViewer.h"


mapViewer::mapViewer(catanMapModel myMap)
{
	initError = false;
	this->myMap = myMap;
	if ((robberBitmap = al_load_bitmap("graficoCatan\\ladron.png")) != NULL)
	{

	}
}

void mapViewer::update()
{

}

void mapViewer::viewHex()
{

}

void mapViewer::viewTokens()
{
}

void mapViewer::viewBuildings()
{
}

void mapViewer::viewRobber()
{
	unsigned char robberPos = myMap.getRobberPos();
	al_draw_bitmap(robberBitmap, myHexagonCoords[robberPos].xCoords, myHexagonCoords[robberPos].yCoords, 0);
}

mapViewer::~mapViewer()
{
}