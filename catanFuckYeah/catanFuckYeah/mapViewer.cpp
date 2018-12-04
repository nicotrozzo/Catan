#include "mapViewer.h"


mapViewer::mapViewer(catanMapModel * myMap)
{
	oceanHex = { {'N',seaN},{'L',seaL},{'M',seaM},{'O',seaO},{'P',seaP},{'T',seaT} };
	resourcesHex = { {'N',desierto},{'L',colinas},{'M',bosques },{'O',pasto},{'P',montañas},{'T',campos} };
	initOk = false;
	this->myMap = myMap;
	if ((robberBitmap = al_load_bitmap("graficoCatan\\ladron.png")) != NULL)
	{
		if ((settlement1Bitmap = al_load_bitmap("graficoCatan\\piezas\\settlement1.png")) != NULL && (settlement2Bitmap = al_load_bitmap("graficoCatan\\piezas\\settlement2.png")) != NULL)
		{
			if ((road1Bitmap = al_load_bitmap("graficoCatan\\piezas\\road1.png")) != NULL && (road2Bitmap = al_load_bitmap("graficoCatan\\piezas\\road2.png")) != NULL)
			{
				if ((city1Bitmap = al_load_bitmap("graficoCatan\\piezas\\city1.png")) != NULL && (city2Bitmap = al_load_bitmap("graficoCatan\\piezas\\city2.png")) != NULL)
				{
					if ((montañas = al_load_bitmap("graficoCatan\\hexagonos\\montañas.png")) != NULL && (colinas = al_load_bitmap("graficoCatan\\hexagonos\\colinas.png")) != NULL && (pasto = al_load_bitmap("graficoCatan\\hexagonos\\pasto.png")) != NULL && (campos = al_load_bitmap("graficoCatan\\hexagonos\\campos.png")) != NULL && (bosques = al_load_bitmap("graficoCatan\\hexagonos\\bosques.png")) != NULL && (desierto = al_load_bitmap("graficoCatan\\hexagonos\\desierto.png")))
					{
						if((seaN = al_load_bitmap("graficoCatan\\hexagonos\\sea\\sea0.png")) != NULL && (seaL = al_load_bitmap("graficoCatan\\hexagonos\\sea\\sea1.png")) != NULL && (seaM = al_load_bitmap("graficoCatan\\hexagonos\\sea\\sea2.png")) != NULL && (seaO = al_load_bitmap("graficoCatan\\hexagonos\\sea\\sea3.png")) != NULL && (seaP = al_load_bitmap("graficoCatan\\hexagonos\\sea\\sea4.png")) != NULL && (seaT = al_load_bitmap("graficoCatan\\hexagonos\\sea\\sea5.png")))
						{
							if ((wallpaperBitmap = al_load_bitmap("graficoCatan\\menues\\playingMenu.png")) != NULL)
							{
								initOk = true;
							}
						}
					}
				}
			}
		}
	}
}

void mapViewer::update()
{
	viewWallpaper();
	viewHex();
	viewRobber();
	viewTokens();
	viewBankTrade();
}

void mapViewer::viewWallpaper()
{
	al_draw_bitmap(wallpaperBitmap,0,0,0);
}

void mapViewer::viewHex()
{
	string pieces = myMap->getMap();
	for (unsigned char i = 0; i < NUMBER_OF_OCEAN_PIECES; i++)
	{
		al_draw_rotated_bitmap(oceanHex[pieces[i]], al_get_bitmap_width(oceanHex[pieces[i]]) / 2, al_get_bitmap_height(oceanHex[pieces[i]]) / 2, myHexagonCoords[i].xCoord - al_get_bitmap_width(oceanHex[pieces[i]]) / 2, myHexagonCoords[i].yCoord - al_get_bitmap_height(oceanHex[pieces[i]]) / 2, myHexagonCoords[i].angle, 0);
	}
	for (unsigned char i = 0; i < HEX_COUNT; i++)
	{
		al_draw_bitmap(resourcesHex[pieces[i+NUMBER_OF_OCEAN_PIECES]], myHexagonCoords[pieces[i + NUMBER_OF_OCEAN_PIECES]].xCoord - al_get_bitmap_width(oceanHex[pieces[i +NUMBER_OF_OCEAN_PIECES]]) / 2, myHexagonCoords[pieces[i + NUMBER_OF_OCEAN_PIECES]].yCoord - al_get_bitmap_height(oceanHex[pieces[i + NUMBER_OF_OCEAN_PIECES]]) / 2,0);
	}
}

void mapViewer::viewTokens()
{

}

void mapViewer::viewBuildings()
{
	list<string> p1Settlements = myMap->getP1BuiltVertexes();
	list<string> p2Settlements = myMap->getP2BuiltVertexes();
	list<string> p1Cities = myMap->getP1Cities();
	list<string> p2Cities = myMap->getP2Cities();
	list<string> p1Roads = myMap->getP1Roads();
	list<string> p2Roads = myMap->getP2Roads();
	list<string>::iterator it;
	for (it = p1Settlements.begin(); it != p1Settlements.end(); it++)
	{
		al_draw_bitmap(settlement1Bitmap, myVertexCoords[*it].xCoord - (al_get_bitmap_width(settlement1Bitmap)/2), myVertexCoords[*it].yCoord - (al_get_bitmap_height(settlement1Bitmap)/2), 0);		//pongo corrimientos para que me dibuje la imagen centrada
	}
	for (it = p2Settlements.begin(); it != p2Settlements.end(); it++)
	{
		al_draw_bitmap(settlement2Bitmap, myVertexCoords[*it].xCoord - (al_get_bitmap_width(settlement2Bitmap) / 2), myVertexCoords[*it].yCoord - (al_get_bitmap_height(settlement2Bitmap) / 2), 0);
	}
	for (it = p1Cities.begin(); it != p1Cities.end(); it++)
	{
		al_draw_bitmap(city1Bitmap, myVertexCoords[*it].xCoord - (al_get_bitmap_width(city1Bitmap) / 2), myVertexCoords[*it].yCoord - (al_get_bitmap_height(city1Bitmap) / 2), 0);
	}
	for (it = p2Cities.begin(); it != p2Cities.end(); it++)
	{
		al_draw_bitmap(city2Bitmap, myVertexCoords[*it].xCoord - (al_get_bitmap_width(city2Bitmap) / 2), myVertexCoords[*it].yCoord - (al_get_bitmap_height(city2Bitmap) / 2), 0);
	}
	for (it = p1Roads.begin(); it != p1Roads.end(); it++)
	{
		al_draw_rotated_bitmap(road1Bitmap, al_get_bitmap_width(road1Bitmap) / 2, al_get_bitmap_height(road1Bitmap) / 2, myEdgesCoords[*it].xCoord - al_get_bitmap_width(road1Bitmap) / 2, myEdgesCoords[*it].yCoord - al_get_bitmap_height(road1Bitmap) / 2, myEdgesCoords[*it].angle, 0);		//roto desde el centro
	}
	for (it = p2Roads.begin(); it != p2Roads.end(); it++)
	{
		al_draw_rotated_bitmap(road2Bitmap, al_get_bitmap_width(road2Bitmap) / 2, al_get_bitmap_height(road2Bitmap) / 2, myEdgesCoords[*it].xCoord - al_get_bitmap_width(road2Bitmap) / 2, myEdgesCoords[*it].yCoord - al_get_bitmap_height(road2Bitmap) / 2, myEdgesCoords[*it].angle, 0);
	}
}

void mapViewer::viewRobber()
{
	unsigned char robberPos = myMap->getRobberPos();
	al_draw_bitmap(robberBitmap, myHexagonCoords[robberPos].xCoord, myHexagonCoords[robberPos].yCoord, 0);
}

mapViewer::~mapViewer()
{
}