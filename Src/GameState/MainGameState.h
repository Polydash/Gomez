#ifndef MAINGAMESTATE_H
#define MAINGAMESTATE_H

#include "BaseGameState.h"
#include "../Event/IEvent.h"
#include "../Graphics/GfxImage.h"
#include "../Graphics/GfxRect.h"

class TetrisGrid;
class TetrisScore;
class TetrisPiece;
class TetrisNextPiece;

class MainGameState : public BaseGameState
{
private :

	TetrisGrid      *m_pTetrisGrid;
	TetrisScore     *m_pTetrisScore;
	TetrisNextPiece *m_pTetrisGfxNextPiece;
	TetrisPiece *m_pCurrentPiece, *m_pNextPiece;
	
	GfxRectSharedPtr m_pFadeRect;
	ProcessSharedPtr m_pDisappearProc;
	ProcessSharedPtr m_pFadeOutProc;
	ProcessSharedPtr m_pScrollingProc[3];
	ProcessSharedPtr m_pEasterEggProc;
	
	bool m_moveRight, m_moveLeft;
	unsigned int m_inputRepeat;
	
	GfxImageSharedPtr m_pBackgroundImage;
	
public:

	MainGameState();
	virtual ~MainGameState();
	
	virtual void VOnInput(const SDL_Event &event);
	virtual void VOnUpdate(unsigned int elapsedTime);
	virtual void VOnEnter();
	virtual void VOnLeave();					
												  
	virtual eGameState VGetState() const { return GS_MAINGAME; }

private :

	bool CheckCollision();
	void SetProc();
	void UpdatePieces();

	void LostFocusDelegate(EventSharedPtr pEvent);
	void EndTetrisLoopDelegate(EventSharedPtr pEvent);
	void AddScoreDelegate(EventSharedPtr pEvent);

	void RegisterEvents();
	void UnregisterEvents();
};

#endif
