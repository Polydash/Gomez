#ifndef MAINGAMESTATE_H
#define MAINGAMESTATE_H

#include "BaseGameState.h"
#include "../Event/IEvent.h"
#include "../Graphics/GfxImage.h"

class TetrisGrid;
class TetrisScore;

class MainGameState : public BaseGameState
{
private :

	TetrisGrid*  m_pTetrisGrid;
	TetrisScore* m_pTetrisScore;
	
	bool m_moveRight, m_moveLeft;
	unsigned int m_inputRepeat;
	
	GfxImageSharedPtr m_pBackgroundImage;
	
public:

	MainGameState();
	virtual ~MainGameState();
	
	virtual void VOnInput(const SDL_Event &event);
	virtual void VOnUpdate(unsigned int elapsedTime);
	virtual void VOnEnter();						
												  
	virtual eGameState VGetState() const { return GS_MAINGAME; }

	void LostFocusDelegate(EventSharedPtr pEvent);
};

#endif
