#include "MenuState.h"
#include "../GameStd.h"
#include "../Event/Events/Evt_StateChange.h"
#include "../Event/EventManager.h"
#include "../Process/Processes/HorizontalScrollProcess.h"
#include "../Resource/ResourceManager.h"

void MenuState::VOnUpdate(unsigned int elapsedTime)
{ 
}

void MenuState::VOnEnter()
{
	INFO("Entering MENU state");
	LOG("Entering MENU state");
	ResourceManager::Get()->Clear();
	
	m_pScrollingProc[0].reset(new HorizontalScrollProcess(0.3f, 2, "yoshi.png"));
	AttachLogicProcess(m_pScrollingProc[0]);
}
