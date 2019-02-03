#pragma once
#include <map>
#include <string>

#define DIS_W	1642
#define DIS_H	1000
#define MY_DIS_W 1642
#define MY_DIS_H 1000
#define PROP_X (MY_DIS_W/DIS_W)
#define PROP_Y (MY_DIS_H/DIS_H)

#define PI 3.14159265359
#define SEA_0_ROTATION PI
#define SEA_1_ROTATION (PI*4/3)
#define SEA_2_ROTATION (PI*5/3)
#define SEA_3_ROTATION 0
#define SEA_4_ROTATION (PI/3)
#define SEA_5_ROTATION	(2*PI/3)
#define MAP_ALPHA (5*PI/3 + PI/7)
#define MAP_BETA (PI/3 - PI/7)
#define MAP_VERTICAL (PI/2)
#define MAP_NONE 0

using namespace std;

typedef struct
{
	double xCoord;
	double yCoord;
	double angle;
}coords;

class gameCoords
{
public:
	static map<string, const coords> myVertexCoords;
	static map<string, const coords> myEdgesCoords;
	static map<unsigned char,const coords> myHexagonCoords;
	static map<string, const coords> buttonCoords;
	static map<string, const coords> cardsCoords;
};