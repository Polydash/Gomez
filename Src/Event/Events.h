#ifndef EVENTS_H
#define EVENTS_H

#include "IEvent.h"
#include "../GameState/IGameState.h"

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

class Evt_FocusLost : public IEvent
{
public :

	Evt_FocusLost(){}
	~Evt_FocusLost(){}
	
	virtual eEventType VGetType() const{ return ET_FOCUSLOST; }
};

#endif
