#ifndef MAINGAMESTATE_H
#define MAINGAMESTATE_H

#include "BaseGameState.h"
#include "../Event/IEvent.h"

class TetrisGrid;

class MainGameState : public BaseGameState
{
private :

	TetrisGrid* m_pTetrisGrid;
	
public:

	MainGameState();
	virtual ~MainGameState();
	
	virtual void VOnInput(const SDL_Event &event);
	virtual void VOnEnter();						
												  
	virtual eGameState VGetState() const { return GS_MAINGAME; }
	
	void LostFocusDelegate(EventSharedPtr pEvent);
};

#endif
