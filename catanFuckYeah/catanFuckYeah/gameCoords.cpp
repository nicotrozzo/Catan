#include "gameCoords.h"

 map<string, const coords> gameCoords::myVertexCoords = {
	{ "0A",{ 676*PROP_X,165*PROP_Y ,MAP_NONE } },{ "0B",{ 820 * PROP_X,165 * PROP_Y,MAP_NONE } },{ "01C",{ 966 * PROP_X,165 * PROP_Y,MAP_NONE } },
	{ "05A",{ 606 * PROP_X,206 * PROP_Y,MAP_NONE } },{ "0AB",{ 747 * PROP_X,206 * PROP_Y,MAP_NONE } },{ "0BC",{ 891 * PROP_X,206 * PROP_Y,MAP_NONE } },{ "1C",{ 1034 * PROP_X,206 * PROP_Y,MAP_NONE } },
	{ "5AD",{ 606 * PROP_X,290 * PROP_Y,MAP_NONE } },{ "ABE",{ 747 * PROP_X,290 * PROP_Y,MAP_NONE } },{ "BCF",{ 891 * PROP_X,290 * PROP_Y,MAP_NONE } },{ "1CG",{ 1034 * PROP_X,290 * PROP_Y,MAP_NONE } },
	{ "5D",{ 532 * PROP_X,332 * PROP_Y,MAP_NONE } },{ "ADE",{ 676 * PROP_X,332 * PROP_Y,MAP_NONE } },{ "BEF",{ 820 * PROP_X,332 * PROP_Y,MAP_NONE } },{ "CFG",{ 966 * PROP_X,332 * PROP_Y,MAP_NONE } },{ "1G",{ 1109 * PROP_X,332 * PROP_Y,MAP_NONE } },
	{ "5DH",{ 532 * PROP_X,415 * PROP_Y,MAP_NONE } },{ "DEI",{ 676 * PROP_X,415 * PROP_Y,MAP_NONE } },{ "EFJ",{ 820 * PROP_X,415 * PROP_Y,MAP_NONE } },{ "FGK",{ 966 * PROP_X,415 * PROP_Y,MAP_NONE } },{ "1GL",{ 1109 * PROP_X,415 * PROP_Y,MAP_NONE } },
	{ "5H",{ 460 * PROP_X,457 * PROP_Y,MAP_NONE } },{ "DHI",{ 606 * PROP_X,457 * PROP_Y,MAP_NONE } },{ "EIJ",{ 747 * PROP_X,457 * PROP_Y,MAP_NONE } },{ "FJK",{ 891 * PROP_X,457 * PROP_Y,MAP_NONE } },{ "GKL",{ 1034 * PROP_X,457 * PROP_Y,MAP_NONE } },{ "12L",{ 1186 * PROP_X,457 * PROP_Y,MAP_NONE } },
	{ "45H",{ 460 * PROP_X,542 * PROP_Y,MAP_NONE } },{ "HIM",{ 606 * PROP_X,542 * PROP_Y,MAP_NONE } },{ "IJN",{ 747 * PROP_X,542 * PROP_Y,MAP_NONE } },{ "JKO",{ 891 * PROP_X,542 * PROP_Y,MAP_NONE } },{ "KLP",{ 1034 * PROP_X,542 * PROP_Y,MAP_NONE } },{ "2L",{ 1186 * PROP_X,542 * PROP_Y,MAP_NONE } },
	{ "4HM",{ 532 * PROP_X,583 * PROP_Y,MAP_NONE } },{ "IMN",{ 676 * PROP_X,583 * PROP_Y,MAP_NONE } },{ "JNO",{ 820 * PROP_X,583 * PROP_Y,MAP_NONE } },{ "KOP",{ 966 * PROP_X,583 * PROP_Y,MAP_NONE } },{ "2LP",{ 1109 * PROP_X,583 * PROP_Y,MAP_NONE } },
	{ "4M",{ 532 * PROP_X,669 * PROP_Y,MAP_NONE } },{ "MNQ",{ 676 * PROP_X,669 * PROP_Y,MAP_NONE } },{ "NOR",{ 820 * PROP_X,669 * PROP_Y,MAP_NONE } },{ "OPS",{ 966 * PROP_X,669 * PROP_Y,MAP_NONE } },{ "2P",{ 1109 * PROP_X,669 * PROP_Y,MAP_NONE } },
	{ "4MQ",{ 606 * PROP_X,708 * PROP_Y,MAP_NONE } },{ "NQR",{ 747 * PROP_X,708 * PROP_Y,MAP_NONE } },{ "ORS",{ 891 * PROP_X,708 * PROP_Y,MAP_NONE } },{ "2PS",{ 1034 * PROP_X,708 * PROP_Y,MAP_NONE } },
	{ "4Q",{ 606 * PROP_X,793 * PROP_Y,MAP_NONE } },{ "3QR",{ 747 * PROP_X,793 * PROP_Y,MAP_NONE } },{ "3RS",{ 891 * PROP_X,793 * PROP_Y,MAP_NONE } },{ "23S",{ 1034 * PROP_X,793 * PROP_Y,MAP_NONE } },
	{ "34Q",{ 676 * PROP_X,833 * PROP_Y,MAP_NONE } },{ "3R",{ 820 * PROP_X,833 * PROP_Y,MAP_NONE } },{ "3S",{ 966 * PROP_X,833 * PROP_Y,MAP_NONE } }
};

 map<string, const coords> gameCoords::myEdgesCoords = {
	{ "0A5",{ 641*PROP_X,185.5*PROP_Y,MAP_ALPHA } },{ "0AB",{ 711.5*PROP_X,185.5*PROP_Y,MAP_BETA } },{ "0BA",{ 783.5*PROP_X,185.5*PROP_Y,MAP_ALPHA } },{ "0BC",{ 855.5*PROP_X,185.5*PROP_Y,MAP_BETA } },{ "0C",{ 928.5*PROP_X,185.5*PROP_Y,MAP_ALPHA } },{ "1C0",{ 1000 * PROP_X,185.5*PROP_Y,MAP_BETA } },
	{ "5A",{ 606 * PROP_X,248 * PROP_Y,MAP_VERTICAL } },{ "AB",{ 747 * PROP_X,248 * PROP_Y,MAP_VERTICAL } },{ "BC",{ 891 * PROP_X,248 * PROP_Y,MAP_VERTICAL } },{ "1CG",{ 1034 * PROP_X,248 * PROP_Y,MAP_VERTICAL } },
	{ "5DA",{ 569 * PROP_X,311 * PROP_Y,MAP_ALPHA } },{ "AD",{ 640 * PROP_X,311 * PROP_Y,MAP_BETA } },{ "AE",{ 711.5*PROP_X,311 * PROP_Y,MAP_ALPHA } },{ "BE",{ 783.5*PROP_X,311 * PROP_Y,MAP_BETA } },{ "BF",{ 855.5*PROP_X,311 * PROP_Y,MAP_ALPHA } },{ "CF",{ 928.5*PROP_X,311 * PROP_Y,MAP_BETA } },{ "CG",{ 1000 * PROP_X,311 * PROP_Y,MAP_ALPHA } },{ "1GC",{ 1072 * PROP_X,311 * PROP_Y,MAP_BETA } },
	{ "5DH",{ 532 * PROP_X,373.5*PROP_Y,MAP_VERTICAL } },{ "DE",{ 676 * PROP_X,373.5*PROP_Y,MAP_VERTICAL } },{ "EF",{ 820 * PROP_X,373.5*PROP_Y,MAP_VERTICAL } },{ "FG",{ 966 * PROP_X,373.5*PROP_Y,MAP_VERTICAL } },{ "1GL",{ 1109 * PROP_X,373.5*PROP_Y,MAP_VERTICAL } },
	{ "5HD",{ 496 * PROP_X,436 * PROP_Y,MAP_ALPHA } },{ "DH",{ 569 * PROP_X,436 * PROP_Y,MAP_BETA } },{ "DI",{ 641 * PROP_X,436 * PROP_Y,MAP_ALPHA } },{ "EI",{ 711.5*PROP_X,436 * PROP_Y,MAP_BETA } },{ "EJ",{ 783.5*PROP_X,436 * PROP_Y,MAP_ALPHA } },{ "FJ",{ 855.5*PROP_X,436 * PROP_Y,MAP_BETA } },{ "FK",{ 928.5*PROP_X,436 * PROP_Y,MAP_ALPHA } },{ "GK",{ 1000 * PROP_X,436 * PROP_Y,MAP_BETA } },{ "GL",{ 1072 * PROP_X,436 * PROP_Y,MAP_ALPHA } },{ "1L",{ 1148 * PROP_X,436 * PROP_Y,MAP_BETA } },
	{ "5H4",{ 460 * PROP_X,499.5*PROP_Y,MAP_VERTICAL } },{ "HI",{ 606 * PROP_X,499.5*PROP_Y,MAP_VERTICAL } },{ "IJ",{ 747 * PROP_X,499.5*PROP_Y,MAP_VERTICAL } },{ "JK",{ 891 * PROP_X,499.5*PROP_Y,MAP_VERTICAL } },{ "KL",{ 1034 * PROP_X,499.5*PROP_Y,MAP_VERTICAL } },{ "2L1",{ 1186 * PROP_X,499.5*PROP_Y,MAP_VERTICAL } },
	{ "4H",{ 496 * PROP_X,562.5*PROP_Y,MAP_BETA } },{ "HM",{ 569 * PROP_X,562.5*PROP_Y,MAP_ALPHA } },{ "IM",{ 641 * PROP_X,562.5*PROP_Y,MAP_BETA } },{ "IN",{ 711.5*PROP_X,562.5*PROP_Y,MAP_ALPHA } },{ "JN",{ 783.5*PROP_X,562.5*PROP_Y,MAP_BETA } },{ "JO",{ 855.5*PROP_X,562.5*PROP_Y,MAP_ALPHA } },{ "KO",{ 928.5*PROP_X,562.5*PROP_Y,MAP_BETA } },{ "KP",{ 1000 * PROP_X,562.5*PROP_Y,MAP_ALPHA } },{ "LP",{ 1072 * PROP_X,562.5*PROP_Y,MAP_BETA } },{ "2LP",{ 1148 * PROP_X,562.5*PROP_Y,MAP_ALPHA } },
	{ "4MH",{ 532 * PROP_X,626 * PROP_Y,MAP_VERTICAL } },{ "MN",{ 676 * PROP_X,626 * PROP_Y,MAP_VERTICAL } },{ "NO",{ 820 * PROP_X,626 * PROP_Y,MAP_VERTICAL } },{ "OP",{ 966 * PROP_X,626 * PROP_Y,MAP_VERTICAL } },{ "2PL",{ 1109 * PROP_X,626 * PROP_Y,MAP_VERTICAL } },
	{ "4MQ",{ 569 * PROP_X,688.5*PROP_Y,MAP_BETA } },{ "MQ",{ 641 * PROP_X,688.5*PROP_Y,MAP_ALPHA } },{ "NQ",{ 711.5*PROP_X,688.5*PROP_Y,MAP_BETA } },{ "NR",{ 783.5*PROP_X,688.5*PROP_Y,MAP_ALPHA } },{ "OR",{ 855.5*PROP_X,688.5*PROP_Y,MAP_BETA } },{ "OS",{ 928.5*PROP_X,688.5*PROP_Y,MAP_ALPHA } },{ "PS",{ 1000 * PROP_X,688.5*PROP_Y,MAP_BETA } },{ "2PS",{ 1072 * PROP_X,688.5*PROP_Y,MAP_ALPHA } },
	{ "4QM",{ 606 * PROP_X,750.5*PROP_Y,MAP_VERTICAL } },{ "QR",{ 747 * PROP_X,750.5*PROP_Y,MAP_VERTICAL } },{ "RS",{ 891 * PROP_X,750.5*PROP_Y,MAP_VERTICAL } },{ "2S",{ 1034 * PROP_X,750.5*PROP_Y,MAP_VERTICAL } },
	{ "4Q3",{ 641 * PROP_X,813 * PROP_Y,MAP_BETA } },{ "3Q",{ 711.5*PROP_X,813 * PROP_Y,MAP_ALPHA } },{ "3RQ",{ 783.5*PROP_X,813 * PROP_Y,MAP_BETA } },{ "3RS",{ 855.5*PROP_X,813 * PROP_Y,MAP_ALPHA } },{ "3SR",{ 928.5*PROP_X,813 * PROP_Y,MAP_BETA } },{ "3S2",{ 1000 * PROP_X,813 * PROP_Y,MAP_ALPHA } }
};

 map<unsigned char,const coords> gameCoords::myHexagonCoords = {
	{ 'A',{ 676 * PROP_X,248 * PROP_Y,MAP_NONE } },{ 'B',{ 820 * PROP_X,247 * PROP_Y,MAP_NONE } },{ 'C',{ 963 * PROP_X,248 * PROP_Y,MAP_NONE } },
	{ 'D',{ 606 * PROP_X,373.5*PROP_Y,MAP_NONE } },{ 'E',{ 747 * PROP_X,373.5*PROP_Y,MAP_NONE } },{ 'F',{ 891 * PROP_X,373.5*PROP_Y,MAP_NONE } },{ 'G',{ 1034 * PROP_X,373.5*PROP_Y,MAP_NONE } },
	{ 'H',{ 534 * PROP_X,499.5*PROP_Y,MAP_NONE } },{ 'I',{ 676 * PROP_X,499.5*PROP_Y,MAP_NONE } },{ 'J',{ 820 * PROP_X,499.5*PROP_Y,MAP_NONE } },{ 'K',{ 963 * PROP_X,498.5*PROP_Y,MAP_NONE } },{ 'L',{ 1106 * PROP_X,499.5*PROP_Y,MAP_NONE } },
	{ 'M',{ 606 * PROP_X,626 * PROP_Y,MAP_NONE } },{ 'N',{ 747 * PROP_X,626 * PROP_Y,MAP_NONE } },{ 'O',{ 891 * PROP_X,626 * PROP_Y,MAP_NONE } },{ 'P',{ 1034 * PROP_X,626 * PROP_Y,MAP_NONE } },
	{ 'Q',{ 676 * PROP_X,750.5*PROP_Y,MAP_NONE } },{ 'R',{ 820 * PROP_X,750.5*PROP_Y,MAP_NONE } },{ 'S',{ 964 * PROP_X,750.5*PROP_Y,MAP_NONE } },
	{ '0',{ 750 * PROP_X,125 * PROP_Y,SEA_0_ROTATION } },{ '1',{ 1105 * PROP_X,249 * PROP_Y,SEA_1_ROTATION } },{ '2',{ 1177 * PROP_X,626 * PROP_Y,SEA_2_ROTATION } },{ '3',{ 891 * PROP_X,875 * PROP_Y,SEA_3_ROTATION } },{ '4',{ 534 * PROP_X,750.5*PROP_Y,SEA_4_ROTATION } },{ '5',{ 464 * PROP_X,373.5*PROP_Y,SEA_5_ROTATION } },
};

 map<string, const coords> gameCoords::cardsCoords = {	//tiene coordenadas de la esquina de arriba a la izq de cada carta de recursos en el trueque
	 {"ORE1",{460 * PROP_X,170 * PROP_Y,MAP_NONE}}, {"WHEAT1",{637 * PROP_X,170 * PROP_Y,MAP_NONE}}, {"WOOL1",{818 * PROP_X,170 * PROP_Y,MAP_NONE}}, {"WOOD1",{995 * PROP_X,170 * PROP_Y,MAP_NONE}}, {"BRICK1",{1171 * PROP_X,170 * PROP_Y,MAP_NONE}},
	 {"ORE2",{460 * PROP_X,552 * PROP_Y,MAP_NONE}}, {"WHEAT2",{637 * PROP_X,552 * PROP_Y,MAP_NONE}}, {"WOOL2",{818 * PROP_X,552 * PROP_Y,MAP_NONE}}, {"WOOD2",{995 * PROP_X,552 * PROP_Y,MAP_NONE}}, {"BRICK2",{1171 * PROP_X,552 * PROP_Y,MAP_NONE}}
 };

 map<string, const coords> gameCoords::buttonCoords = {
 {"END_TURN",{1419 * PROP_X,123 * PROP_Y,MAP_NONE}}, {"EXIT",{1562 * PROP_X,9 * PROP_Y,MAP_NONE}}, {"QUIT",{851 * PROP_X,500 * PROP_Y,MAP_NONE}}, {"PLAY",{410 * PROP_X,500 * PROP_Y,MAP_NONE}},
 {"PLAYER_TRADE",{1530 * PROP_X,220 * PROP_Y,MAP_NONE}}, {"BANK_TRADE",{1405 * PROP_X,220 * PROP_Y,MAP_NONE}}, {"YES",{1413 * PROP_X,876 * PROP_Y,MAP_NONE}}, {"NO",{1540 * PROP_X,876 * PROP_Y,MAP_NONE}},
 {"REMATCH/PLAY_AGAIN",{236 * PROP_X,494 * PROP_Y,MAP_NONE}},{"SCAPE",{991 * PROP_X, 494 * PROP_Y, MAP_NONE}}
 };