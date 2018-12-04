#pragma once
#include <map>
#include <string>

using namespace std;

const typedef struct
{
	float xCoord;
	float yCoord;
}coords;


const map<string, coords> myVertexCoords;

const map<string, coords> myEdgesCoords;

const map<unsigned char, coords> myHexagonCoords;