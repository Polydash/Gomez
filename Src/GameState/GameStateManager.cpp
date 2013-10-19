#include "GameStateManager.h"
#include "../GameStd.h"
#include "../GameApp/SDLApp.h"
#include "../Event/EventManager.h"
#include "../Event/Events.h"
#include "MenuState.h"
#include "IntroState.h"
#include "PauseState.h"

GameStateManager::GameStateManager():
m_pCurrentState(NULL),
m_pPausedState(NULL)
{
}

GameStateManager::~GameStateManager()
{
	DestroyState(m_pCurrentState);
	DestroyState(m_pPausedState);
	g_pApp->GetEventMgr()->RemoveListener(MakeDelegate(this, &GameStateManager::StateChangeDelegate), ET_STATECHANGE);
}

bool GameStateManager::Init()
{
	g_pApp->GetEventMgr()->AddListener(MakeDelegate(this, &GameStateManager::StateChangeDelegate), ET_STATECHANGE);
		
	ChangeState(GS_INTRO);
	
	return true;
}

void GameStateManager::Update(unsigned int elapsedTime)
{
	m_pCurrentState->VUpdate(elapsedTime);
}

void GameStateManager::StateChangeDelegate(EventSharedPtr pEvent)
{
	ERROR("Game state change processed");
	shared_ptr<Evt_StateChange> pEvt = static_pointer_cast<Evt_StateChange>(pEvent);
	ChangeState(pEvt->GetState());
}

IGameState* GameStateManager::CreateState(const eGameState gameState)
{
	if(gameState == GS_PAUSE)
	{		
		LOG("Entered Pause state");
		return new PauseState();
	}
	if(gameState == GS_INTRO)
	{
		LOG("Entered Intro state");
		return new IntroState();
	}
	else if(gameState == GS_MENU)
	{
		LOG("Entered Menu state");
		return new MenuState();
	}

	ERROR("Invalid game state type");
	return NULL;
}

void GameStateManager::ChangeState(const eGameState gameState)
{		
	if(m_pCurrentState != NULL) 			
	{
		if(gameState == GS_PAUSE)
		{
			if(m_pPausedState != NULL)
				ERROR("Game has already been paused");
				
			m_pPausedState = m_pCurrentState;
		}
		else
		{
			m_pCurrentState->VOnLeave(); 	
			DestroyState(m_pCurrentState);
		} 	
	}
	
	if(gameState == GS_PREVIOUS)
	{
		m_pCurrentState = m_pPausedState;
		m_pPausedState = NULL;
	}
	else
	{
		if(m_pPausedState != NULL && gameState != GS_PAUSE)
			DestroyState(m_pPausedState);
			
		m_pCurrentState = CreateState(gameState);
	}
	
	m_pCurrentState->VOnEnter(); 			
}

void GameStateManager::DestroyState(IGameState* &pGameState)
{
	SAFE_DELETE(pGameState);
}
