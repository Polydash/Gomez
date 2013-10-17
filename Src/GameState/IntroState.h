#ifndef INTROSTATE_H
#define INTROSTATE_H

#include "IGameState.h"

class IntroState : public IGameState
{
public:

	IntroState(){}
	virtual ~IntroState(){}
	
	virtual void VUpdate(unsigned int elapsedTime);
		
	virtual eGameState VGetState() const { return GS_INTRO; }
};

#endif
