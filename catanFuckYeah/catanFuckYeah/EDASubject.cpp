#include "EDASubject.h"

void
EDASubject::attach(observer * observerPtr)
{
	listOfObservers.push_back(observerPtr);
}

void
EDASubject::detach(observer * observerPtr)
{
	listOfObservers.remove(observerPtr);
}

void
EDASubject::notifyAllObservers(void)
{
	list<observer * > :: iterator it;
	for (it = listOfObservers.begin(); it != listOfObservers.end(); it++)
		(*it)->update();
}
