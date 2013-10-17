#ifndef IEVENT_H
#define IEVENT_H

#include "FastDelegate.h"

class IEvent;

enum eEventType{ ET_TEST, EVENT_NB };
typedef fastdelegate::FastDelegate1<IEvent*> EventListenerDelegate;

class IEvent
{
public :

	virtual eEventType VGetType() const = 0;

};

#endif
