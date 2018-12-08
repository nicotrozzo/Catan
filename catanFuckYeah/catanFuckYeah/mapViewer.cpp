#include "mapViewer.h"
#include "gameCoords.h"



mapViewer::mapViewer(catanMapModel * myMap)
{
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
					if ((montañas = al_load_bitmap("graficoCatan\\hexagonos\\montanas.png")) != NULL && (colinas = al_load_bitmap("graficoCatan\\hexagonos\\colinas.png")) != NULL && (pasto = al_load_bitmap("graficoCatan\\hexagonos\\pasto.png")) != NULL && (campos = al_load_bitmap("graficoCatan\\hexagonos\\campos.png")) != NULL && (bosques = al_load_bitmap("graficoCatan\\hexagonos\\bosques.png")) != NULL && (desierto = al_load_bitmap("graficoCatan\\hexagonos\\desierto.png")) != NULL)
					{
						if ((seaN = al_load_bitmap("graficoCatan\\hexagonos\\sea\\sea0.png")) != NULL && (seaL = al_load_bitmap("graficoCatan\\hexagonos\\sea\\sea1.png")) != NULL && (seaM = al_load_bitmap("graficoCatan\\hexagonos\\sea\\sea2.png")) != NULL && (seaO = al_load_bitmap("graficoCatan\\hexagonos\\sea\\sea3.png")) != NULL && (seaP = al_load_bitmap("graficoCatan\\hexagonos\\sea\\sea4.png")) != NULL && (seaT = al_load_bitmap("graficoCatan\\hexagonos\\sea\\sea5.png")) != NULL)
						{
							if ((wallpaperBitmap = al_load_bitmap("graficoCatan\\menues\\playingMenu.png")) != NULL)
							{
								if ((tokens[0] = al_load_bitmap("graficoCatan\\numeros\\2.png")) != NULL && (tokens[1] = al_load_bitmap("graficoCatan\\numeros\\3.png")) != NULL && (tokens[2] = al_load_bitmap("graficoCatan\\numeros\\4.png")) != NULL && (tokens[3] = al_load_bitmap("graficoCatan\\numeros\\5.png")) != NULL && (tokens[4] = al_load_bitmap("graficoCatan\\numeros\\6.png")) != NULL && (tokens[5] = al_load_bitmap("graficoCatan\\numeros\\8.png")) != NULL && (tokens[6] = al_load_bitmap("graficoCatan\\numeros\\9.png")) != NULL && (tokens[7] = al_load_bitmap("graficoCatan\\numeros\\10.png")) != NULL && (tokens[8] = al_load_bitmap("graficoCatan\\numeros\\11.png")) != NULL && (tokens[9] = al_load_bitmap("graficoCatan\\numeros\\12.png")) != NULL)
								{
									initOk = true;
									oceanHex = { { 'N',seaN },{ 'L',seaL },{ 'M',seaM },{ 'O',seaO },{ 'P',seaP },{ 'T',seaT } };
									resourcesHex = { { 'N',desierto },{ 'L',colinas },{ 'M',bosques },{ 'O',pasto },{ 'P',montañas },{ 'T',campos } };
								}
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
	if (initOk)
	{
		viewWallpaper();
		viewHex();
		viewTokens();
		viewRobber();
		viewPendingConstruction();
		viewBuildings();
		//viewBankTrade();
	}
	else
	{
		cout << "mal en mapviewer" << endl;
	}
}

void mapViewer::viewWallpaper()
{
	al_draw_bitmap(wallpaperBitmap, 0, 0, 0);
}

void mapViewer::viewHex()
{
	string pieces = myMap->getMap();
	ALLEGRO_BITMAP * bitmapToDraw;
	for (unsigned char i = 0; i < NUMBER_OF_OCEAN_PIECES; i++)
	{
		bitmapToDraw = oceanHex[static_cast<unsigned char>(pieces[i])];
		float cx = al_get_bitmap_width(oceanHex[static_cast<unsigned char>(pieces[i])]) / 2.0;
		float cy = al_get_bitmap_height(oceanHex[static_cast<unsigned char>(pieces[i])]) / 2.0;
		float dx = gameCoords::myHexagonCoords[i + '0'].xCoord;
		float dy = gameCoords::myHexagonCoords[i + '0'].yCoord;
		float angle = gameCoords::myHexagonCoords[i + '0'].angle;
		al_draw_rotated_bitmap(bitmapToDraw, cx, cy, dx, dy, angle, 0);
	}
	for (unsigned char i = 0; i < HEX_COUNT; i++)
	{
		bitmapToDraw = resourcesHex[(pieces[i + NUMBER_OF_OCEAN_PIECES])];
		float dx = gameCoords::myHexagonCoords[i + 'A'].xCoord - al_get_bitmap_width(bitmapToDraw) / 2;
		float dy = gameCoords::myHexagonCoords[i + 'A'].yCoord - al_get_bitmap_height(bitmapToDraw) / 2;
		al_draw_bitmap(bitmapToDraw, dx, dy, 0);
	}
}

void mapViewer::viewTokens()
{
	string token = myMap->getCircularTokens();
	ALLEGRO_BITMAP *bitmapToDraw;
	float dx, dy;
	for (unsigned char i = 0; i < HEX_COUNT; i++)
	{
		if (token[i] != 7)
		{
			if (token[i] < 7)
			{
				bitmapToDraw = tokens[token[i] - 2];

			}
			else
			{
				bitmapToDraw = tokens[token[i] - 3];
			}
			dx = gameCoords::myHexagonCoords[i + 'A'].xCoord - al_get_bitmap_width(bitmapToDraw) / 2;
			dy = gameCoords::myHexagonCoords[i + 'A'].yCoord - al_get_bitmap_height(bitmapToDraw) / 2;
			al_draw_bitmap(bitmapToDraw, dx, dy, 0);
		}
	}

}

void mapViewer::viewBuildings()
{
	list<string> p1Settlements = myMap->getP1Settlements();
	list<string> p2Settlements = myMap->getP2Settlements();
	list<string> p1Cities = myMap->getP1Cities();
	list<string> p2Cities = myMap->getP2Cities();
	list<string> p1Roads = myMap->getP1Roads();
	list<string> p2Roads = myMap->getP2Roads();
	list<string>::iterator it;
	for (it = p1Roads.begin(); it != p1Roads.end(); it++)
	{
		al_draw_rotated_bitmap(road1Bitmap, al_get_bitmap_width(road1Bitmap) / 2.0, al_get_bitmap_height(road1Bitmap) / 2.0, gameCoords::myEdgesCoords[*it].xCoord, gameCoords::myEdgesCoords[*it].yCoord, gameCoords::myEdgesCoords[*it].angle, 0);		//roto desde el centro
	}
	for (it = p2Roads.begin(); it != p2Roads.end(); it++)
	{
		al_draw_rotated_bitmap(road2Bitmap, al_get_bitmap_width(road2Bitmap) / 2.0, al_get_bitmap_height(road2Bitmap) / 2.0, gameCoords::myEdgesCoords[*it].xCoord, gameCoords::myEdgesCoords[*it].yCoord, gameCoords::myEdgesCoords[*it].angle, 0);
	}
	for (it = p1Settlements.begin(); it != p1Settlements.end(); it++)
	{
		float w = al_get_bitmap_width(settlement1Bitmap) / 2.0;
		float dx = gameCoords::myVertexCoords[*it].xCoord - (al_get_bitmap_width(settlement1Bitmap) / 2.0);
		al_draw_bitmap(settlement1Bitmap, dx, gameCoords::myVertexCoords[*it].yCoord - (al_get_bitmap_height(settlement1Bitmap) / 2.0), 0);		//pongo corrimientos para que me dibuje la imagen centrada
	}
	for (it = p2Settlements.begin(); it != p2Settlements.end(); it++)
	{
		al_draw_bitmap(settlement2Bitmap, gameCoords::myVertexCoords[*it].xCoord - (al_get_bitmap_width(settlement2Bitmap) / 2.0), gameCoords::myVertexCoords[*it].yCoord - (al_get_bitmap_height(settlement2Bitmap) / 2), 0);
	}
	for (it = p1Cities.begin(); it != p1Cities.end(); it++)
	{
		al_draw_bitmap(city1Bitmap, gameCoords::myVertexCoords[*it].xCoord - (al_get_bitmap_width(city1Bitmap) / 2.0), gameCoords::myVertexCoords[*it].yCoord - (al_get_bitmap_height(city1Bitmap) / 2), 0);
	}
	for (it = p2Cities.begin(); it != p2Cities.end(); it++)
	{
		al_draw_bitmap(city2Bitmap, gameCoords::myVertexCoords[*it].xCoord - (al_get_bitmap_width(city2Bitmap) / 2.0), gameCoords::myVertexCoords[*it].yCoord - (al_get_bitmap_height(city2Bitmap) / 2), 0);
	}
}

void mapViewer::viewRobber()
{
	unsigned char robberPos = myMap->getRobberPos();
	al_draw_bitmap(robberBitmap, gameCoords::myHexagonCoords[robberPos].xCoord - al_get_bitmap_width(robberBitmap) / 2, gameCoords::myHexagonCoords[robberPos].yCoord - al_get_bitmap_height(robberBitmap) / 2, 0);
}

void mapViewer::viewPendingConstruction()
{
	construction_t pendingConstruction = myMap->getPendingConstruction();
	switch (pendingConstruction.type)
	{
	case SETTLEMENT:
		al_draw_tinted_bitmap(settlement1Bitmap, al_map_rgba_f(0.5, 0.5, 0.5, 0.5), gameCoords::myVertexCoords[pendingConstruction.coords].xCoord, gameCoords::myVertexCoords[pendingConstruction.coords].yCoord, 0);
		break;
	case CITY:
		al_draw_tinted_bitmap(city1Bitmap, al_map_rgba_f(0.5, 0.5, 0.5, 0.5), gameCoords::myVertexCoords[pendingConstruction.coords].xCoord, gameCoords::myVertexCoords[pendingConstruction.coords].yCoord, 0);
		break;
	case ROAD:
		al_draw_tinted_bitmap(road1Bitmap, al_map_rgba_f(0.5, 0.5, 0.5, 0.5), gameCoords::myEdgesCoords[pendingConstruction.coords].xCoord, gameCoords::myEdgesCoords[pendingConstruction.coords].yCoord, 0);
		break;
	}
}

mapViewer::~mapViewer()
{
}