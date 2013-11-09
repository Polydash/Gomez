#include "MainGameState.h"
#include "../GameStd.h"
#include "../Event/EventManager.h"
#include "../Event/Events/Evt_MainGameInput.h"
#include "../Event/Events/Evt_LostFocus.h"
#include "../Resource/ResourceManager.h"
#include "../Process/Processes/FallingPieceProcess.h"
#include "../TetrisLogic/TetrisGrid.h"

MainGameState::MainGameState():
m_pTetrisGrid(NULL),
m_moveRight(false),
m_moveLeft(false),
m_inputRepeat(0)
{
	EventManager::Get()->AddListener(MakeDelegate(this, &MainGameState::LostFocusDelegate), ET_LOSTFOCUS);
}

MainGameState::~MainGameState()
{
	EventManager::Get()->RemoveListener(MakeDelegate(this, &MainGameState::LostFocusDelegate), ET_LOSTFOCUS);

	if(m_pTetrisGrid)
		SAFE_DELETE(m_pTetrisGrid);
}

void MainGameState::LostFocusDelegate(EventSharedPtr pEvent)
{
	//Toggle Pause
}

void MainGameState::VOnInput(const SDL_Event &event)
{
	//Possibly send some input to UI
	
	if(event.type == SDL_KEYDOWN && !event.key.repeat)
	{
		shared_ptr<Evt_MainGameInput> pInput;
		switch(event.key.keysym.sym)
		{
			case SDLK_LEFT :
				m_moveLeft = true;
				pInput.reset(new Evt_MainGameInput(GI_MOVELEFT));
				EventManager::Get()->QueueEvent(pInput);
				break;
				
			case SDLK_RIGHT :
				m_moveRight = true;
				pInput.reset(new Evt_MainGameInput(GI_MOVERIGHT));
				EventManager::Get()->QueueEvent(pInput);
				break;
				
			case SDLK_DOWN : 
				pInput.reset(new Evt_MainGameInput(GI_DROP));
				EventManager::Get()->QueueEvent(pInput);
				break;
				
			case SDLK_UP :
				pInput.reset(new Evt_MainGameInput(GI_ROTATE));
				EventManager::Get()->QueueEvent(pInput);
				break;
				
			default :
				break;
		}
	}
	else if(event.type == SDL_KEYUP)
	{
		shared_ptr<Evt_MainGameInput> pInput;
		switch(event.key.keysym.sym)
		{
			case SDLK_DOWN :
				pInput.reset(new Evt_MainGameInput(GI_DROP, false));
				EventManager::Get()->QueueEvent(pInput);
				break;
				
			case SDLK_LEFT : 
				m_moveLeft = false;
				break;
				
			case SDLK_RIGHT :
				m_moveRight = false;
				break;
				
			default :
				break;
		}
	}		
}

void MainGameState::VOnUpdate(unsigned int elapsedTime)
{
	if(m_moveLeft && !m_moveRight)
	{
		m_inputRepeat += elapsedTime;
		if(m_inputRepeat > 150)
		{
			shared_ptr<Evt_MainGameInput> pInput;
			pInput.reset(new Evt_MainGameInput(GI_MOVELEFT));
			EventManager::Get()->QueueEvent(pInput);
			m_inputRepeat = 0;
		}
	}
	else if(m_moveRight && !m_moveLeft)
	{
		m_inputRepeat += elapsedTime;
		if(m_inputRepeat > 150)
		{
			shared_ptr<Evt_MainGameInput> pInput;
			pInput.reset(new Evt_MainGameInput(GI_MOVERIGHT));
			EventManager::Get()->QueueEvent(pInput);
			m_inputRepeat = 0;
		}
	}
	else
		m_inputRepeat = 0;
}

void MainGameState::VOnEnter()
{
	INFO("Entering MAINGAME state");
	LOG("Entering MAINGAME state");
	ResourceManager::Get()->Clear();
	
	m_pTetrisGrid = new TetrisGrid(10, 20, 60, 60);
	
	ProcessSharedPtr pProcess = ProcessSharedPtr(new FallingPieceProcess(m_pTetrisGrid, 2.0f));
	AttachLogicProcess(pProcess);
}
