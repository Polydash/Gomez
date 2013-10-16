#ifndef IEVENT_H
#define IEVENT_H

#include "FastDelegate.h"
#include "FastDelegateBind.h"

class IEvent;

enum eEventType{ ET_TEST };
typedef fastdelegate::FastDelegate1<IEvent*> EventListenerDelegate;

class IEvent
{
public :

	virtual eEventType VGetType() const = 0;

};

#endif
