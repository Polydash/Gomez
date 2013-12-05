#ifndef INTROSTATE_H
#define INTROSTATE_H

/**
 * \file IntroState.h 
 * \brief Intro Game State
 */

#include "BaseGameState.h"
#include "../Graphics/GfxText.h"
#include "../Graphics/GfxRect.h"

class IntroState : public BaseGameState
{
private :

	GfxTextSharedPtr m_pTextPolydash;
	GfxTextSharedPtr m_pTextDeveloppedBy;
	GfxTextSharedPtr m_pTextNames;
	GfxRectSharedPtr m_pFadeRect;
	ProcessSharedPtr m_pFadeOutProc;
	
public :

	IntroState(){}
	virtual ~IntroState(){}
	
	virtual void VOnUpdate(unsigned int elapsedTime);
	virtual void VOnEnter(); 
	virtual void VOnLeave();
		
	virtual eGameState VGetState() const{ return GS_INTRO; }
	
private :

	void SetDisplay();
	void SetProc();
};

#endif
