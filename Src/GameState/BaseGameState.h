#ifndef BASEGAMESTATE_H
#define BASEGAMESTATE_H

#include <SDL2/SDL.h>

#include "../Event/IEvent.h"
#include "../Process/Process.h"

class ProcessManager;

enum eGameState{ GS_INVALID = -1,
				 GS_INTRO,
				 GS_MENU,
				 GS_MAINGAME
			   };

class BaseGameState
{
private :

	ProcessManager *m_pProcessMgr;

public :
	
	BaseGameState();
	virtual ~BaseGameState();
	
	bool Init();
	
	virtual void VOnInput(const SDL_Event &event){}
	virtual void VUpdate(unsigned int elapsedTime);
	virtual void VOnEnter(){}
	virtual void VOnLeave(){}
	
	virtual eGameState VGetState() const = 0;
	
protected :

	void AttachLogicProcess(ProcessSharedPtr pProcess);
	
private :

	void AttachLogicProcessDelegate(EventSharedPtr pEvent);
	void RegisterEvents();
	void UnregisterEvents();
};

#endif
