#ifndef EVT_LOSTFOCUS_H
#define EVT_LOSTFOCUS_H

/**
 * \file Evt_LostFocus.h
 * \brief Lost Focus Event
 */

#include "../IEvent.h"

class Evt_LostFocus : public IEvent
{
public :

	Evt_LostFocus(){}
	~Evt_LostFocus(){}
	
	virtual eEventType VGetType() const{ return ET_LOSTFOCUS; }
};

#endif
