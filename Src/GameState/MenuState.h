#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "BaseGameState.h"

class MenuState : public BaseGameState
{
private :

	ProcessSharedPtr m_pScrollingProc[2];
	
public :

	MenuState(){}
	virtual ~MenuState(){}
	
	virtual void VOnUpdate(unsigned int elapsedTime);
	virtual void VOnEnter();						
												  
	virtual eGameState VGetState() const { return GS_MENU; }
};

#endif
