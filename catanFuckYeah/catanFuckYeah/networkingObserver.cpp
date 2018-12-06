#include "networkingObserver.h"



networkingObserver::networkingObserver(catanGameModel * game, connector * connect) : gameModel(game), netwDelivery(connect)
{

}

void networkingObserver::update()
{
	/*le pregunta al modelo que es lo que se modifico, y en funcion de eso envia el paquete de networking correspondiente
	es muy importante que el modelo tenga en sus valores por defecto todo lo que no este siendo usado, */
	if (gameModel->getTrade())
	{

		netwDelivery->sendPackage()
	}
	else if (gameModel->getConstruction())
	{

	}
	else if (gameModel->getRobbMove())
	{

	}
}


networkingObserver::~networkingObserver()
{
}
