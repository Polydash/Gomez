#include "GameStateManager.h"
#include "../GameStd.h"
#include "../Event/EventManager.h"
#include "../Event/Events/Evt_StateChange.h"
#include "MenuState.h"
#include "IntroState.h"
#include "MainGameState.h"

GameStateManager::GameStateManager():
m_pCurrentState(NULL)
{
}

GameStateManager::~GameStateManager()
{
	DestroyState(m_pCurrentState);
	EventManager::Get()->RemoveListener(MakeDelegate(this, &GameStateManager::StateChangeDelegate), ET_STATECHANGE);
}

bool GameStateManager::Init()
{
	EventManager::Get()->AddListener(MakeDelegate(this, &GameStateManager::StateChangeDelegate), ET_STATECHANGE);
		
	ChangeState(GS_INTRO);
	
	return true;
}

void GameStateManager::Update(unsigned int elapsedTime)
{
	m_pCurrentState->VUpdate(elapsedTime);
}

void GameStateManager::StateChangeDelegate(EventSharedPtr pEvent)
{
	shared_ptr<Evt_StateChange> pEvt = static_pointer_cast<Evt_StateChange>(pEvent);
	ChangeState(pEvt->GetState());
}

BaseGameState* GameStateManager::CreateState(const eGameState gameState)
{
	if(gameState == GS_INTRO)
		return new IntroState();
		
	if(gameState == GS_MENU)
		return new MenuState();
		
	if(gameState == GS_MAINGAME)
		return new MainGameState();

	ERROR("Invalid game state type");
	return NULL;
}

void GameStateManager::ChangeState(const eGameState gameState)
{		
	if(m_pCurrentState != NULL) 			
	{
		m_pCurrentState->VOnLeave(); 	
		DestroyState(m_pCurrentState); 	
	}
			
	m_pCurrentState = CreateState(gameState);
	if(!m_pCurrentState->Init())
		ERROR("Failed to init GameState");
	else
		m_pCurrentState->VOnEnter(); 			
}

void GameStateManager::DestroyState(BaseGameState* &pGameState)
{
	SAFE_DELETE(pGameState);
}
