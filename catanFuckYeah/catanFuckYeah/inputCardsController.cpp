#include "inputCardsController.h"
#include "inputEventGenerator.h"
#include "gameCoords.h"


#define OFFSET_CARD_X 15		//ponele, es nomas para tener algo y acordarme
#define OFFSET_CARD_Y 15

inputCardsController::inputCardsController(catanGameModel * game) : gameModel(game)
{
}

bool inputCardsController::parseMouseEvent(mouseEvent * ev)
{
	//agarrar coordenadas de las cartas, sumarles un offset en la que puede estar y ver que esa carta la tenga disponible
	//ver game coords.h
	//tomo arriba a la izquierda para los bitmaps
	//cardsCoords[{WHEAT, 1}];		// {recurso,jugadro} devuelve point
	bool ret = false;
	string resources = RESOURCES_STR;
	unsigned char player = gameModel->getCurrentPlayer().getPlayerNumber();
	point coords = ev->getClickCoords();
	for (auto c : resources)
	{
		if ((coords.x >= cardsCoords[{c, player}].x) && (coords.x <= OFFSET_CARD_X))	//falta definir el offset del bitmap en el cual puede estar el mouse
		{
			if ((coords.y >= cardsCoords[{c, player}].y) && (coords.y <= OFFSET_CARD_y))
			{
				//llamar a los metodos del modelo
				if (playerTrade)
				{
					ret = gameModel->preparePlayerTrade(,);	//pensar como concvertir el char a enum de resourceType
				}
				else
				{
					ret = gameModel->prepareBankTrade(,);	//pensar como mandar si es del banco el recurso o mio
				}
			}
		}
	}

}

void inputCardsController::parseKeyboardEvent(keyboardEvent * ev)
{


}


inputCardsController::~inputCardsController()
{
}
