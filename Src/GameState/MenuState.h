#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "IGameState.h"

class MenuState : public IGameState
{
public:

	MenuState(){}
	~MenuState(){}
	
	virtual void VUpdate(unsigned int elapsedTime);
												  
	virtual eGameState VGetState() const { return GS_MENU; }
};

#endif
