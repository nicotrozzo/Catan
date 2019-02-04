#pragma once
#include "EDANetworkingController.h"
#include <queue>

typedef enum cases { ROBBER_CARDS_CASE, DICES_CASE,OTHER_CASE };
//typedef enum robberPhases { I_PHASE, F_PHASE, S_PHASE, T_PHASE };

class netwAckController : public EDANetworkingController
{
public:
	netwAckController(catanGameModel *);
	virtual netwControllerTypes getType() { return CTRL_ACK; }
	bool parseNetworkingEvent(networkingEv *ev);
	bool setAction(cases action_);
	~netwAckController();
private:
	catanGameModel *gameModel;
	cases action;
	//robberPhases phases;
	bool validAction(cases action_);
	/*unsigned char currentAmountCards;
	unsigned char otherAmountCards;
	bool checkPhase();
	void setPhase();
	void init();
	unsigned int amountOfAckExpected;
	unsigned int numberOfCalls;
	bool initial;*/
};

