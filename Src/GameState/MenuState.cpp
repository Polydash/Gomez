#include "MenuState.h"
#include "../GameStd.h"
#include "../GameApp/SDLApp.h"
#include "../Event/Events.h"
#include "../Event/EventManager.h"

void MenuState::VUpdate(unsigned int elapsedTime)
{ 
	//To remove
	static unsigned int time = 0;
	time += elapsedTime;
	if(time > 1000)
	{
		shared_ptr<Evt_StateChange> pEvent(new Evt_StateChange(GS_PAUSE));
		EventManager::Get()->QueueEvent(pEvent);
		time = 0;
	}
}

void MenuState::VOnEnter()
{
	INFO("Entering MENU state");
	LOG("Entering MENU state");
}
