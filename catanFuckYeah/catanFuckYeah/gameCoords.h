#pragma once
#include <map>
#include <string>
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


const typedef struct
{
	float xCoord;
	float yCoord;
	float angle;
}coords;

class gameCoords
{
public:
	static const map<string, coords> myVertexCoords;
	static const map<string, coords> myEdgesCoords;
	const static map<unsigned char, coords> myHexagonCoords;

	//static const map<, point> cardsCoords = {
	//cardsCoords[{WHEAT,1}] ->devuelve centro de la carta, o esquina sup izquierda
	//}
};