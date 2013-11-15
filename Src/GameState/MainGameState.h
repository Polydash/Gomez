#ifndef MAINGAMESTATE_H
#define MAINGAMESTATE_H

#include "BaseGameState.h"
#include "../Event/IEvent.h"
#include "../Graphics/GfxImage.h"

class TetrisGrid;
class TetrisScore;
class TetrisPiece;

class MainGameState : public BaseGameState
{
private :

	TetrisGrid  *m_pTetrisGrid;
	TetrisScore *m_pTetrisScore;
	TetrisPiece *m_pCurrentPiece, *m_pNextPiece;
	
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

private :

	void LostFocusDelegate(EventSharedPtr pEvent);
	void EndTetrisLoopDelegate(EventSharedPtr pEvent);

	void RegisterEvents();
	void UnregisterEvents();
};

#endif
