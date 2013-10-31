#ifndef MAINGAMESTATE_H
#define MAINGAMESTATE_H

#include "BaseGameState.h"
#include "../Event/IEvent.h"

class MainGameState : public BaseGameState
{
public:

	MainGameState();
	virtual ~MainGameState();
	
	virtual void VOnInput(const SDL_Event &event);
	virtual void VOnEnter();						
												  
	virtual eGameState VGetState() const { return GS_MAINGAME; }
	
	void LostFocusDelegate(EventSharedPtr pEvent);
};

#endif
