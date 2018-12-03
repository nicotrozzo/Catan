#pragma once
#include "EDAInputController.h"

/*Controller de botones de PASS, OFFER_TRADE Y BANK_TRADE*/
class inputActionButtonController : public EDAInputController
{
public:
	inputActionButtonController();
	virtual void parseMouseEvent(mouseEvent * ev);
	virtual void parseKeyboardEvent(keyboardEvent * ev);
	~inputActionButtonController();
};

