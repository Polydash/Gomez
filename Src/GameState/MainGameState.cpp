#include "MainGameState.h"
#include "../GameStd.h"
#include "../Event/EventManager.h"
#include "../Event/Events.h"
#include "../Resource/ResourceManager.h"

MainGameState::MainGameState()
{
	EventManager::Get()->AddListener(MakeDelegate(this, &MainGameState::FocusChangeDelegate), ET_FOCUSLOST);
}

MainGameState::~MainGameState()
{
	EventManager::Get()->RemoveListener(MakeDelegate(this, &MainGameState::FocusChangeDelegate), ET_FOCUSLOST);
}

void MainGameState::FocusChangeDelegate(EventSharedPtr pEvent)
{
	shared_ptr<Evt_StateChange> pEventChange(new Evt_StateChange(GS_PAUSE));
	EventManager::Get()->QueueEvent(pEventChange);
	
	ResourceManager::Get()->Clear();
}

void MainGameState::VUpdate(unsigned int elapsedTime)
{ 
}

void MainGameState::VOnEnter()
{
	INFO("Entering MAINGAME state");
	LOG("Entering MAINGAME state");
	ResourceManager::Get()->Clear();
}
