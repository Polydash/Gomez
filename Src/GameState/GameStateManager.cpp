#include "GameStateManager.h"
#include "../GameStd.h"
#include "../GameApp/SDLApp.h"
#include "../Event/EventManager.h"
#include "../Event/Events.h"
#include "MenuState.h"
#include "IntroState.h"

GameStateManager::GameStateManager():
m_pCurrentState(NULL)
{
}

GameStateManager::~GameStateManager()
{
	DestroyState();
	g_pApp->GetEventMgr()->RemoveListener(MakeDelegate(this, &GameStateManager::StateChangeDelegate), ET_STATECHANGE);
}

bool GameStateManager::Init()
{
	g_pApp->GetEventMgr()->AddListener(MakeDelegate(this, &GameStateManager::StateChangeDelegate), ET_STATECHANGE);
	
	IGameState *pState = CreateState(GS_INTRO);
	if(!pState)
		return false;
		
	ChangeState(pState);
	
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
	ChangeState(CreateState(pEvt->GetState()));
}

IGameState* GameStateManager::CreateState(const eGameState gameState)
{
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

void GameStateManager::ChangeState(IGameState *pState)
{		
	if(m_pCurrentState != NULL) // if there is a state
	{
		m_pCurrentState->VOnLeave(); // leave the state
		DestroyState(); // and destroy it
	}
	
	m_pCurrentState = pState;
	m_pCurrentState->VOnEnter(); // enter new state
}

void GameStateManager::DestroyState()
{
	if(m_pCurrentState)
		SAFE_DELETE(m_pCurrentState);
}
