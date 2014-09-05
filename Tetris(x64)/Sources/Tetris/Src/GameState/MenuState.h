#ifndef MENUSTATE_H
#define MENUSTATE_H

/**
 * \file MenuState.h 
 * \brief Menu State
 */

#include "BaseGameState.h"
#include "../Graphics/GfxRect.h"
#include "../Graphics/GfxImage.h"
#include "../Graphics/GfxText.h"

/**
 * \class MenuState
 * \brief Menu State
 * 
 * GameState specific to the Tetris game. It manages every aspect of the
 * main menu, allowing a new game to start or the application to end. 
 */
class MenuState : public BaseGameState
{
private :

	ProcessSharedPtr  m_pScrollingProc[3];
	ProcessSharedPtr  m_pFadeInProc;
	ProcessSharedPtr  m_pFadeOutProc;
	ProcessSharedPtr  m_pScale;
	ProcessSharedPtr  m_pFlash;
	ProcessSharedPtr  m_pBlink;
	GfxRectSharedPtr  m_pFadeRect;
	GfxImageSharedPtr m_pTitle[2];
	GfxTextSharedPtr  m_pOptions[2];
	
	bool m_bIsDone, m_bHasInput;
	bool m_joystickDeadZone;
	int m_option;
	
public :

	MenuState();
	virtual ~MenuState(){}
	
	virtual void VOnInput(const SDL_Event &event);
	virtual void VOnUpdate(unsigned int elapsedTime);
	virtual void VOnEnter();						
	virtual void VOnLeave();						
								  
	virtual eGameState VGetState() const { return GS_MENU; }
	
private :

	void OnKeyboardEvent(const SDL_Event &event);
	void OnJoystickEvent(const SDL_Event &event);

	void SetDisplay();
	void SetProc();
};

#endif
