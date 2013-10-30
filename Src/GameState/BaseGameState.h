#ifndef BASEGAMESTATE_H
#define BASEGAMESTATE_H

#include "../Event/IEvent.h"

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
	
	virtual void VUpdate(unsigned int elapsedTime) = 0;
	virtual void VOnEnter(){}
	virtual void VOnLeave(){}
	
	virtual eGameState VGetState() const = 0;
	
private :

	void AttachLogicProcessDelegate(EventSharedPtr pEvent);

	void RegisterEvents();
	void UnregisterEvents();
};

#endif
