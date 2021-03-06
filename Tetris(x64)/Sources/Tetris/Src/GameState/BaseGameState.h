#ifndef BASEGAMESTATE_H
#define BASEGAMESTATE_H

/**
 * \file BaseGameState.h 
 * \brief Base class for Game States
 */

#include <SDL2/SDL.h>

#include "../Event/IEvent.h"
#include "../Process/Process.h"

class ProcessManager;

/// Enumeration defining every GameState
enum eGameState{ GS_INVALID = -1,
				 GS_INTRO,
				 GS_MENU,
				 GS_MAINGAME
			   };

/**
 * \class BaseGameState
 * \brief Base class for Game States
 * 
 * BaseGameState holds the main methods of all GameStates. It includes a
 * ProcessManager that represents the logic processes running with each
 * GameState.
 * 
 * Every GameState shall inherit from this class.
 */
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
	virtual void VOnUpdate(unsigned int elapsedTime){}
	virtual void VOnEnter(){}
	virtual void VOnLeave(){}
	
	virtual eGameState VGetState() const = 0;
	
protected :

	void AttachLogicProcess(ProcessSharedPtr pProcess);
	void AbortAllProcesses();
	
private :

	void AttachLogicProcessDelegate(EventSharedPtr pEvent);
	void RegisterEvents();
	void UnregisterEvents();
};

#endif
