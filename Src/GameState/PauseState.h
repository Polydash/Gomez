#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include "IGameState.h"

class PauseState : public IGameState
{
public:

	PauseState(){}
	virtual ~PauseState(){}
	
	virtual void VUpdate(unsigned int elapsedTime);
	virtual void VOnEnter();
												  
	virtual eGameState VGetState() const { return GS_PAUSE; }
};

#endif
