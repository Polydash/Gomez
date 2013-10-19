#include "PauseState.h"
#include "../GameStd.h"
#include "../GameApp/SDLApp.h"
#include "../Event/Events.h"
#include "../Event/EventManager.h"

void PauseState::VUpdate(unsigned int elapsedTime)
{ 
	//To remove
	static unsigned int time = 0;
	time += elapsedTime;
	if(time > 1000)
	{
		shared_ptr<Evt_StateChange> pEvent(new Evt_StateChange(GS_INTRO));
		g_pApp->GetEventMgr()->QueueEvent(pEvent);
		time = 0;
	}
}

void PauseState::VOnEnter()
{
	INFO("Entering PAUSE state");
	LOG("Entering PAUSE state");
}
