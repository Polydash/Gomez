#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "IGameState.h"

class MenuState : public IGameState
{
public:

	MenuState(){}
	virtual ~MenuState(){}
	
	virtual void VUpdate(unsigned int elapsedTime);
	virtual void VOnEnter();						
												  
	virtual eGameState VGetState() const { return GS_MENU; }
};

#endif
