#include "IntroState.h"
#include "../GameStd.h"
#include "../Event/EventManager.h"
#include "../Event/Events/Evt_StateChange.h"
#include "../Resource/ResourceManager.h"

void IntroState::VOnUpdate(unsigned int elapsedTime)
{
	//To remove
	static unsigned int time = 0;
	time += elapsedTime;
	if(time > 1000)
	{
		shared_ptr<Evt_StateChange> pEvent(new Evt_StateChange(GS_MENU));
		EventManager::Get()->QueueEvent(pEvent);
		time = 0;
	}
}

void IntroState::VOnEnter()
{
	INFO("Entering INTRO state");
	LOG("Entering INTRO state");
	ResourceManager::Get()->Clear();
}
