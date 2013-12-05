#ifndef EVT_ENDTETRISLOOP_H
#define EVT_ENDTETRISLOOP_H

/**
 * \file Evt_EndTetrisLoop.h 
 * \brief End of Tetris Loop Event
 */

#include "../IEvent.h"

class Evt_EndTetrisLoop : public IEvent
{
public :

	Evt_EndTetrisLoop(){}
	~Evt_EndTetrisLoop(){}
	
	virtual eEventType VGetType() const{ return ET_ENDTETRISLOOP; }
};

#endif
