#pragma once
#include "observer.h"
#include "catanGameModel.h"
#include "netwEmisor.h"

class networkingObserver : public observer
{
public:
	networkingObserver(catanGameModel * game, netwEmisor * delivery);
	void update();
	~networkingObserver();
private:
	catanGameModel * gameModel;
	netwEmisor * netwDelivery;
};

