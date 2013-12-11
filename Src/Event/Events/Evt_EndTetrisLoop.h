#ifndef EVT_ENDTETRISLOOP_H
#define EVT_ENDTETRISLOOP_H

/**
 * \file Evt_EndTetrisLoop.h 
 * \brief End of Tetris Loop Event
 */

#include "../IEvent.h"

/**
 * \class Evt_EndTetrisLoop
 * \brief End of Tetris Loop Event
 * 
 * Event indicating the end of a game loop. It gives this information to
 * the current GameState to launch a new loop or indicate a Game Over.
 */
class Evt_EndTetrisLoop : public IEvent
{
public :

	Evt_EndTetrisLoop(){}
	~Evt_EndTetrisLoop(){}
	
	virtual eEventType VGetType() const{ return ET_ENDTETRISLOOP; }
};

#endif
