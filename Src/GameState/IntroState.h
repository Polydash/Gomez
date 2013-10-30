#ifndef INTROSTATE_H
#define INTROSTATE_H

#include "BaseGameState.h"

class IntroState : public BaseGameState
{
public:

	IntroState(){}
	virtual ~IntroState(){}
	
	virtual void VUpdate(unsigned int elapsedTime);
	virtual void VOnEnter(); 
		
	virtual eGameState VGetState() const { return GS_INTRO; }
};

#endif
