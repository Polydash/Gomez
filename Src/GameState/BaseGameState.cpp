#include "BaseGameState.h"
#include "../GameStd.h"
#include "../Process/ProcessManager.h"
#include "../Event/EventManager.h"
#include "../Event/Events/Evt_AttachLogicProcess.h"

BaseGameState::BaseGameState():
m_pProcessMgr(NULL)
{
}

BaseGameState::~BaseGameState()
{
	SAFE_DELETE(m_pProcessMgr);
	UnregisterEvents();
}

bool BaseGameState::Init()
{
	RegisterEvents();
	
	m_pProcessMgr = new ProcessManager();
	if(!m_pProcessMgr)
	{
		ERROR("Failed to create Process Manager");
		return false;
	}
	
	return true;
}

void BaseGameState::VUpdate(unsigned int elapsedTime)
{
	m_pProcessMgr->UpdateProcesses(elapsedTime);
}

void BaseGameState::AttachLogicProcessDelegate(EventSharedPtr pEvent)
{
	shared_ptr<Evt_AttachLogicProcess> pEvt = static_pointer_cast<Evt_AttachLogicProcess>(pEvent);
	m_pProcessMgr->AttachProcess(pEvt->GetProcessPtr());
}

void BaseGameState::RegisterEvents()
{
	EventManager::Get()->AddListener(MakeDelegate(this, &BaseGameState::AttachLogicProcessDelegate), ET_ATTACHLOGICPROCESS);
}

void BaseGameState::UnregisterEvents()
{
	EventManager::Get()->RemoveListener(MakeDelegate(this, &BaseGameState::AttachLogicProcessDelegate), ET_ATTACHLOGICPROCESS);
}	
