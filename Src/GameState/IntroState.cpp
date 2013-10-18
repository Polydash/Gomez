#include "IntroState.h"
#include "../GameStd.h"
#include "../GameApp/SDLApp.h"
#include "../Event/Events.h"

void IntroState::VUpdate(unsigned int elapsedTime)
{
	//To remove
	static unsigned int time = 0;
	time += elapsedTime;
	if(time > 1000)
	{
		ERROR("Game state Menu asked");
		shared_ptr<Evt_StateChange> pEvent(new Evt_StateChange(GS_MENU));
		g_pApp->GetEventMgr()->QueueEvent(pEvent);
		time = 0;
	}
}
