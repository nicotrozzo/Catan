#pragma once
#include "observer.h"
#include <list>

class EDASubject
{

public:
	EDASubject() {}
	virtual ~EDASubject() {}
	void attach(observer * observerPtr);
	void detach(observer * observerPtr);

protected:
	void notifyAllObservers(void);

private:
	list<observer * > listOfObservers;

};
