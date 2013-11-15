#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "BaseGameState.h"
#include "../Graphics/GfxRect.h"
#include "../Graphics/GfxImage.h"
#include "../Graphics/GfxText.h"

class MenuState : public BaseGameState
{
private :

	ProcessSharedPtr  m_pScrollingProc[3];
	ProcessSharedPtr  m_pFadeInProc;
	ProcessSharedPtr  m_pFadeOutProc;
	ProcessSharedPtr  m_pScale;
	GfxRectSharedPtr  m_pFadeRect;
	GfxImageSharedPtr m_pTitle[2];
	GfxTextSharedPtr  m_pOptions[2];
	
public :

	MenuState(){}
	virtual ~MenuState(){}
	
	virtual void VOnUpdate(unsigned int elapsedTime);
	virtual void VOnEnter();						
	virtual void VOnLeave();						
												  
	virtual eGameState VGetState() const { return GS_MENU; }
	
private :

	void SetDisplay();
	void SetProc();
};

#endif
