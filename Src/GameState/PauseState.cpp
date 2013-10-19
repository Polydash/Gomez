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
		ERROR("Game state Intro asked");
		shared_ptr<Evt_StateChange> pEvent(new Evt_StateChange(GS_INTRO));
		g_pApp->GetEventMgr()->QueueEvent(pEvent);
		time = 0;
	}
}
