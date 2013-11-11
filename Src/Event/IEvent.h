#ifndef IEVENT_H
#define IEVENT_H

#include <tr1/memory>
using std::tr1::shared_ptr;
using std::tr1::static_pointer_cast;

#include "FastDelegate.h"
using fastdelegate::MakeDelegate;

enum eEventType{ ET_STATECHANGE,
				 ET_LOSTFOCUS,
				 ET_ATTACHLOGICPROCESS,
				 ET_MAINGAMEINPUT,
				 ET_ADDSCORE,
				 EVENT_NB
			   };
			   
class IEvent;

typedef shared_ptr<IEvent> EventSharedPtr;
typedef fastdelegate::FastDelegate1<EventSharedPtr> EventListenerDelegate;

class IEvent
{
public :

	virtual eEventType VGetType() const = 0;
};

#endif
