#include "gameCoords.h"


const map<string, coords> gameCoords::myVertexCoords = {
	{ "0A",{ 676,165,MAP_NONE } },{ "0B",{ 820,165,MAP_NONE } },{ "01C",{ 966,165,MAP_NONE } },
	{ "05A",{ 606,206,MAP_NONE } },{ "0AB",{ 747,206,MAP_NONE } },{ "0BC",{ 891,206,MAP_NONE } },{ "1C",{ 1034,206,MAP_NONE } },
	{ "5AD",{ 606,290,MAP_NONE } },{ "ABE",{ 747,290,MAP_NONE } },{ "BCF",{ 891,290,MAP_NONE } },{ "1CG",{ 1034,290,MAP_NONE } },
	{ "5D",{ 532,332,MAP_NONE } },{ "ADE",{ 676,332,MAP_NONE } },{ "BEF",{ 820,332,MAP_NONE } },{ "CFG",{ 966,332,MAP_NONE } },{ "1G",{ 1109,332,MAP_NONE } },
	{ "5DH",{ 532,415,MAP_NONE } },{ "DEI",{ 676,415,MAP_NONE } },{ "EFJ",{ 820,415,MAP_NONE } },{ "FGK",{ 966,415,MAP_NONE } },{ "1GL",{ 1109,415,MAP_NONE } },
	{ "5H",{ 460,457,MAP_NONE } },{ "DHI",{ 606,457,MAP_NONE } },{ "EIJ",{ 747,457,MAP_NONE } },{ "FJK",{ 891,457,MAP_NONE } },{ "GKL",{ 1034,457,MAP_NONE } },{ "12L",{ 1186,457,MAP_NONE } },
	{ "45H",{ 460,542,MAP_NONE } },{ "HIM",{ 606,542,MAP_NONE } },{ "IJN",{ 747,542,MAP_NONE } },{ "JKO",{ 891,542,MAP_NONE } },{ "KLP",{ 1034,542,MAP_NONE } },{ "2L",{ 1186,542,MAP_NONE } },
	{ "4HM",{ 532,583,MAP_NONE } },{ "IMN",{ 676,583,MAP_NONE } },{ "JNO",{ 820,583,MAP_NONE } },{ "KOP",{ 966,583,MAP_NONE } },{ "2LP",{ 1109,583,MAP_NONE } },
	{ "4M",{ 532,669,MAP_NONE } },{ "MNQ",{ 676,669,MAP_NONE } },{ "NOR",{ 820,669,MAP_NONE } },{ "OPS",{ 966,669,MAP_NONE } },{ "2P",{ 1109,669,MAP_NONE } },
	{ "4MQ",{ 606,708,MAP_NONE } },{ "NQR",{ 747,708,MAP_NONE } },{ "ORS",{ 891,708,MAP_NONE } },{ "2PS",{ 1034,708,MAP_NONE } },
	{ "4Q",{ 606,793,MAP_NONE } },{ "3QR",{ 747,793,MAP_NONE } },{ "3RS",{ 891,793,MAP_NONE } },{ "3S2",{ 1034,793,MAP_NONE } },
	{ "34Q",{ 676,833,MAP_NONE } },{ "3R",{ 820,833,MAP_NONE } },{ "3S",{ 966,833,MAP_NONE } }
};

const map<string, coords> gameCoords::myEdgesCoords = {
	{ "0A5",{ 641,185.5,MAP_ALPHA } },{ "0AB",{ 711.5,185.5,MAP_BETA } },{ "0BA",{ 783.5,185.5,MAP_ALPHA } },{ "0BC",{ 855.5,185.5,MAP_BETA } },{ "0C",{ 928.5,185.5,MAP_ALPHA } },{ "1CO",{ 1000,185.5,MAP_BETA } },
	{ "5A",{ 606,248,MAP_VERTICAL } },{ "AB",{ 747,248,MAP_VERTICAL } },{ "BC",{ 891,248,MAP_VERTICAL } },{ "1CG",{ 1034,248,MAP_VERTICAL } },
	{ "5DA",{ 569,311,MAP_ALPHA } },{ "AD",{ 640,311,MAP_BETA } },{ "AE",{ 711.5,311,MAP_ALPHA } },{ "BE",{ 783.5,311,MAP_BETA } },{ "BF",{ 855.5,311,MAP_ALPHA } },{ "CF",{ 928.5,311,MAP_BETA } },{ "CG",{ 1000,311,MAP_ALPHA } },{ "1GC",{ 1072,311,MAP_BETA } },
	{ "5DH",{ 532,373.5,MAP_VERTICAL } },{ "DE",{ 676,373.5,MAP_VERTICAL } },{ "EF",{ 820,373.5,MAP_VERTICAL } },{ "FG",{ 966,373.5,MAP_VERTICAL } },{ "1GL",{ 1109,373.5,MAP_VERTICAL } },
	{ "5HD",{ 496,436,MAP_ALPHA } },{ "DH",{ 569,436,MAP_BETA } },{ "DI",{ 641,436,MAP_ALPHA } },{ "EI",{ 711.5,436,MAP_BETA } },{ "EJ",{ 783.5,436,MAP_ALPHA } },{ "FJ",{ 855.5,436,MAP_BETA } },{ "FK",{ 928.5,436,MAP_ALPHA } },{ "GK",{ 1000,436,MAP_BETA } },{ "GL",{ 1072,436,MAP_ALPHA } },{ "1L",{ 1148,436,MAP_BETA } },
	{ "5H4",{ 460,499.5,MAP_VERTICAL } },{ "HI",{ 606,499.5,MAP_VERTICAL } },{ "IJ",{ 747,499.5,MAP_VERTICAL } },{ "JK",{ 891,499.5,MAP_VERTICAL } },{ "KL",{ 1034,499.5,MAP_VERTICAL } },{ "2L1",{ 1186,499.5,MAP_VERTICAL } },
	{ "H4",{ 496,562.5,MAP_BETA } },{ "HM",{ 569,562.5,MAP_ALPHA } },{ "IM",{ 641,562.5,MAP_BETA } },{ "IN",{ 711.5,562.5,MAP_ALPHA } },{ "JN",{ 783.5,562.5,MAP_BETA } },{ "JO",{ 855.5,562.5,MAP_ALPHA } },{ "KO",{ 928.5,562.5,MAP_BETA } },{ "KP",{ 1000,562.5,MAP_ALPHA } },{ "LP",{ 1072,562.5,MAP_BETA } },{ "2LP",{ 1148,562.5,MAP_ALPHA } },
	{ "4MH",{ 532,626,MAP_VERTICAL } },{ "MN",{ 676,626,MAP_VERTICAL } },{ "NO",{ 820,626,MAP_VERTICAL } },{ "OP",{ 966,626,MAP_VERTICAL } },{ "2PL",{ 1109,626,MAP_VERTICAL } },
	{ "4MQ",{ 569,688.5,MAP_BETA } },{ "MQ",{ 641,688.5,MAP_ALPHA } },{ "NQ",{ 711.5,688.5,MAP_BETA } },{ "NR",{ 783.5,688.5,MAP_ALPHA } },{ "OR",{ 855.5,688.5,MAP_BETA } },{ "OS",{ 928.5,688.5,MAP_ALPHA } },{ "PS",{ 1000,688.5,MAP_BETA } },{ "2PS",{ 1072,688.5,MAP_ALPHA } },
	{ "4QM",{ 606,750.5,MAP_VERTICAL } },{ "QR",{ 747,750.5,MAP_VERTICAL } },{ "RS",{ 891,750.5,MAP_VERTICAL } },{ "2S",{ 1034,750.5,MAP_VERTICAL } },
	{ "4Q3",{ 641,813,MAP_BETA } },{ "3Q",{ 711.5,813,MAP_ALPHA } },{ "3RQ",{ 783.5,813,MAP_BETA } },{ "3RS",{ 855.5,813,MAP_ALPHA } },{ "3SR",{ 928.5,813,MAP_BETA } },{ "3S2",{ 1000,813,MAP_ALPHA } }
};

const map<unsigned char, coords> gameCoords::myHexagonCoords = {
	{ 'A',{ 676,248,MAP_NONE } },{ 'B',{ 820,247,MAP_NONE } },{ 'C',{ 963,248,MAP_NONE } },
{ 'D',{ 606,373.5,MAP_NONE } },{ 'E',{ 747,373.5,MAP_NONE } },{ 'F',{ 891,373.5,MAP_NONE } },{ 'G',{ 1034,373.5,MAP_NONE } },
{ 'H',{ 534,499.5,MAP_NONE } },{ 'I',{ 676,499.5,MAP_NONE } },{ 'J',{ 820,499.5,MAP_NONE } },{ 'K',{ 963,498.5,MAP_NONE } },{ 'L',{ 1106,499.5,MAP_NONE } },
{ 'M',{ 606,626,MAP_NONE } },{ 'N',{ 747,626,MAP_NONE } },{ 'O',{ 891,626,MAP_NONE } },{ 'P',{ 1034,626,MAP_NONE } },
{ 'Q',{ 676,750.5,MAP_NONE } },{ 'R',{ 820,750.5,MAP_NONE } },{ 'S',{ 964,750.5,MAP_NONE } },
{ '0',{ 750,125,SEA_0_ROTATION } },{ '1',{ 1105,249,SEA_1_ROTATION } },{ '2',{ 1177,626,SEA_2_ROTATION } },{ '3',{ 891,875,SEA_3_ROTATION } },{ '4',{ 534,750.5,SEA_4_ROTATION } },{ '5',{ 464,373.5,SEA_5_ROTATION } },
};
