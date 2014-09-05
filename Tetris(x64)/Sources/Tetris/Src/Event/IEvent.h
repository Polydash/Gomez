#ifndef IEVENT_H
#define IEVENT_H

/**
 * \file IEvent.h
 * \brief Event interface
 */

#include <sstream>
#include <tr1/memory>
using std::tr1::shared_ptr;
using std::tr1::static_pointer_cast;

#include "FastDelegate.h"
using fastdelegate::MakeDelegate;

/// Enumeration defining every Event type
enum eEventType{ ET_STATECHANGE,
				 ET_LOSTFOCUS,
				 ET_ATTACHLOGICPROCESS,
				 ET_MAINGAMEINPUT,
				 ET_ADDSCORE,
				 ET_ENDTETRISLOOP,
				 ET_NEWTETRISLOOP,
				 EVENT_NB
			   };
			   
class IEvent;

/// Typedef defining an Event shared pointer 
typedef shared_ptr<IEvent> EventSharedPtr;

/// Typedef defining delegates needed by EventManager
typedef fastdelegate::FastDelegate1<EventSharedPtr> EventListenerDelegate;

/**
 * \class IEvent
 * \brief Event interface
 * 
 * Event interface needed by EventManager. Events must inherit from this
 * class.  
 */
class IEvent
{
public :

	virtual eEventType VGetType() const = 0;
	virtual void VSerialize(std::ostringstream &oss){}
	virtual void VDeserialize(std::istringstream &iss){}
};

#endif
