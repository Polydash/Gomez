#include "MenuState.h"
#include "../GameStd.h"
#include "../Event/Events/Evt_StateChange.h"
#include "../Event/EventManager.h"
#include "../Resource/ResourceManager.h"

void MenuState::VOnUpdate(unsigned int elapsedTime)
{ 
	//To remove
	static unsigned int time = 0;
	time += elapsedTime;
	if(time > 1000)
	{
		shared_ptr<Evt_StateChange> pEvent(new Evt_StateChange(GS_MAINGAME));
		EventManager::Get()->QueueEvent(pEvent);
		time = 0;
	}
}

void MenuState::VOnEnter()
{
	INFO("Entering MENU state");
	LOG("Entering MENU state");
	ResourceManager::Get()->Clear();
}
