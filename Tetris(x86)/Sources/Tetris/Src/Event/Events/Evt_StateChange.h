#ifndef EVT_STATECHANGE_H
#define EVT_STATECHANGE_H

/**
 * \file Evt_StateChange.h 
 * \brief State Change Event
 */

#include "../IEvent.h"
#include "../../GameState/BaseGameState.h"

/**
 * \class Evt_StateChange
 * \brief State Change Event
 * 
 * Event allowing an object to request a new GameState. 
 */
class Evt_StateChange : public IEvent
{
private :

	eGameState m_requestedState;

public :

	Evt_StateChange(eGameState state){ m_requestedState = state; }
	~Evt_StateChange(){}
	
	eGameState GetState() const{ return m_requestedState; }
	
	virtual eEventType VGetType() const{ return ET_STATECHANGE; }
};

#endif
