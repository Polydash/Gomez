#ifndef MAINGAMESTATE_H
#define MAINGAMESTATE_H

#include "IGameState.h"
#include "../Event/IEvent.h"

class MainGameState : public IGameState
{
public:

	MainGameState();
	virtual ~MainGameState();
	
	virtual void VUpdate(unsigned int elapsedTime);
	virtual void VOnEnter();						
												  
	virtual eGameState VGetState() const { return GS_MAINGAME; }
	
	void FocusChangeDelegate(EventSharedPtr pEvent);
};

#endif
