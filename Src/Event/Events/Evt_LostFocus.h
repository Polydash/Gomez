#ifndef EVT_LOSTFOCUS_H
#define EVT_LOSTFOCUS_H

#include "../IEvent.h"

class Evt_LostFocus : public IEvent
{
public :

	Evt_LostFocus(){}
	~Evt_LostFocus(){}
	
	virtual eEventType VGetType() const{ return ET_LOSTFOCUS; }
};

#endif
