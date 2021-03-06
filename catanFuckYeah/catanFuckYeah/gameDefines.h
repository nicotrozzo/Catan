#pragma once
#include <iostream>
#include "gameCoords.h"
#define NUMBER_OF_PLAYERS 2
#define MAX_NAME_LENGTH 255
#define NUMBER_OF_OCEAN_PIECES 6
#define NUMBER_OF_HABITATS 6
#define NUMBER_OF_RESOURCES 5
#define HEX_COUNT 19
#define RESOURCES_STR "LMNOPT"
#define POINTS_TO_WIN 8
#define AMOUNT_OF_SETTLEMENTS 5
#define AMOUNT_OF_CITIES 4
#define AMOUNT_OF_ROADS 15
#define OFFSET_CARD_X (149*PROP_X)
#define OFFSET_CARD_Y (189*PROP_Y)
#define OFFSET_YES_X (80*PROP_X)
#define OFFSET_YES_Y (80*PROP_Y)
#define OFFSET_NO_X (80*PROP_X)
#define OFFSET_NO_Y (80*PROP_Y)
#define OFFSET_END_TURN_X (200*PROP_X)
#define OFFSET_END_TURN_Y (89*PROP_Y)
#define OFFSET_TRADE_X (90*PROP_X)
#define OFFSET_TRADE_Y (64*PROP_Y)
#define OFFSET_EXIT_X (80*PROP_X)
#define OFFSET_EXIT_Y (80*PROP_Y)
#define OFFSET_QUIT_X (371*PROP_X)
#define OFFSET_QUIT_Y (136*PROP_Y)
#define OFFSET_HEXAGON_X (90*PROP_X)
#define OFFSET_HEXAGON_Y (90*PROP_Y)
#define OFFSET_VERTEX_X (30*PROP_X)
#define OFFSET_VERTEX_Y (30*PROP_Y)
#define OFFSET_EDGE_X (30*PROP_X)
#define OFFSET_EDGE_Y (30*PROP_Y)
#define OFFSET_PLAY_X (371*PROP_X)	
#define OFFSET_PLAY_Y (136*PROP_Y)
#define OFFSET_REMATCH_X ( 450*PROP_Y)
#define OFFSET_REMATCH_Y ( 195*PROP_Y)
#define OFFSET_PLAY_AGAIN_X (450 *PROP_X)
#define OFFSET_PLAY_AGAIN_Y ( 195*PROP_X)
#define OFFSET_SCAPE_X ( 450*PROP_X)
#define OFFSET_SCAPE_Y ( 195*PROP_X)
typedef enum resourceType { BRICK = 'L', WOOD, DESSERT, WOOL, ORE, WHEAT = 'T'};

