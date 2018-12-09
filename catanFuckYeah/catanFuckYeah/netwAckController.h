#pragma once
#include "EDANetworkingController.h"

typedef enum cases { ROBBER_CASE, OTHER_CASE };
//typedef enum robberPhases { F_PHASE, S_PHASE, T_PHASE };

class netwAckController : public EDANetworkingController
{
public:
	netwAckController(catanGameModel *);
	virtual netwControllerTypes getType() { return CTRL_ACK; }
	bool parseNetworkingEvent(networkingEv *ev);
	void setActionToDo(cases action_);
	~netwAckController();
private:
	catanGameModel * gameModel;
	cases action;
	//robberPhases phases;
	bool validAction(cases action_);
	unsigned char currentAmountCards;
	unsigned char otherAmountCards;
	queue
};

