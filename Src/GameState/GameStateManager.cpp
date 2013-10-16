#include "GameStateManager.h"
#include "../GameStd.h"

GameStateManager::GameStateManager():
m_pCurrentState(NULL),
m_bIsPaused(false)
{
}

GameStateManager::~GameStateManager()
{
	DestroyState(); // destroy state when quit
}

bool GameStateManager::Init()
{
	IGameState *pState = CreateState(GS_INTRO);
	ChangeState(pState);
	
	return true;
}

void GameStateManager::Update(unsigned int elapsedTime)
{
	if(!m_bIsPaused)
		m_pCurrentState->VUpdate(elapsedTime);
		
	//Create a request to change states	
		
	//~ if(!m_pCurrentState->VGetStateActive()) // if we need to change state
	//~ {
		//~ if(m_pCurrentState->VGetState() == GS_INTRO) // if intro is over
			//~ ChangeState(CreateState(GS_MENU));
	//~ }
}

IGameState* GameStateManager::CreateState(const eGameState gameState)
{
	if(gameState == GS_INTRO)
	{
		return new IntroState();
	}
	else //if(gameState == GS_MENU)
	{
		return new MenuState();
	}
}

void GameStateManager::ChangeState(IGameState *pState)
{
	if(!pState)
		ERROR("GameState is invalid");
		
	if(m_pCurrentState != 0) // if there is a state
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

void GameStateManager::Pause()
{
	m_bIsPaused = !m_bIsPaused;
	LOG("Pause");
}
