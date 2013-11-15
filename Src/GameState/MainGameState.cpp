#include "MainGameState.h"
#include "../GameStd.h"
#include "../GameApp/SDLApp.h"
#include "../Graphics/GfxManager.h"
#include "../Event/EventManager.h"
#include "../Event/Events/Evt_MainGameInput.h"
#include "../Event/Events/Evt_LostFocus.h"
#include "../Event/Events/Evt_EndTetrisLoop.h"
#include "../Event/Events/Evt_StateChange.h"
#include "../Resource/ResourceManager.h"
#include "../Process/Processes/FallingPieceProcess.h"
#include "../Process/Processes/SpawnAnimationProcess.h"
#include "../Process/Processes/DisappearAnimationProcess.h"
#include "../Process/Processes/DelayProcess.h"
#include "../Process/Processes/FadeProcess.h"
#include "../TetrisLogic/TetrisGrid.h"
#include "../TetrisLogic/TetrisPiece.h"
#include "../TetrisLogic/TetrisScore.h"

MainGameState::MainGameState():
m_pTetrisGrid(NULL),
m_pTetrisScore(NULL),
m_pCurrentPiece(NULL),
m_pNextPiece(NULL),
m_moveRight(false),
m_moveLeft(false),
m_inputRepeat(0)
{
	RegisterEvents();
}

MainGameState::~MainGameState()
{
	UnregisterEvents();
	
	SAFE_DELETE(m_pTetrisScore);
	SAFE_DELETE(m_pTetrisGrid);
	SAFE_DELETE(m_pCurrentPiece);
	SAFE_DELETE(m_pNextPiece);
}

void MainGameState::VOnInput(const SDL_Event &event)
{
	//Possibly send some input to UI
	
	if(event.type == SDL_KEYDOWN && !event.key.repeat)
	{
		EventSharedPtr pEvt;
		switch(event.key.keysym.sym)
		{
			case SDLK_ESCAPE :
				if(m_pDisappearProc && m_pDisappearProc->IsDone())
				{				
					pEvt.reset(new Evt_StateChange(GS_MENU));
					EventManager::Get()->QueueEvent(pEvt);
					AbortAllProcesses();
				}
				break;
			
			case SDLK_LEFT :
				m_moveLeft = true;
				pEvt.reset(new Evt_MainGameInput(GI_MOVELEFT));
				EventManager::Get()->QueueEvent(pEvt);
				break;
				
			case SDLK_RIGHT :
				m_moveRight = true;
				pEvt.reset(new Evt_MainGameInput(GI_MOVERIGHT));
				EventManager::Get()->QueueEvent(pEvt);
				break;
				
			case SDLK_DOWN : 
				pEvt.reset(new Evt_MainGameInput(GI_DROP));
				EventManager::Get()->QueueEvent(pEvt);
				break;
				
			case SDLK_UP :
				pEvt.reset(new Evt_MainGameInput(GI_ROTATE));
				EventManager::Get()->QueueEvent(pEvt);
				break;
				
			default :
				break;
		}
	}
	else if(event.type == SDL_KEYUP)
	{
		shared_ptr<Evt_MainGameInput> pEvt;
		switch(event.key.keysym.sym)
		{
			case SDLK_DOWN :
				pEvt.reset(new Evt_MainGameInput(GI_DROP, false));
				EventManager::Get()->QueueEvent(pEvt);
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
	//Key repeat handling
	if(m_moveLeft && !m_moveRight)
	{
		m_inputRepeat += elapsedTime;
		if(m_inputRepeat > 150)
		{
			shared_ptr<Evt_MainGameInput> pEvt;
			pEvt.reset(new Evt_MainGameInput(GI_MOVELEFT));
			EventManager::Get()->QueueEvent(pEvt);
			m_inputRepeat = 0;
		}
	}
	else if(m_moveRight && !m_moveLeft)
	{
		m_inputRepeat += elapsedTime;
		if(m_inputRepeat > 150)
		{
			shared_ptr<Evt_MainGameInput> pEvt;
			pEvt.reset(new Evt_MainGameInput(GI_MOVERIGHT));
			EventManager::Get()->QueueEvent(pEvt);
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
	
	m_pTetrisGrid = new TetrisGrid(10, 20, g_pApp->GetScreenHeight()/10, g_pApp->GetScreenHeight()/10);
	m_pTetrisScore = new TetrisScore(240, 150, 500, 60);
	
	m_pBackgroundImage.reset(new GfxImage(2, "background.png"));
	g_pApp->GetGfxMgr()->AddElement(m_pBackgroundImage);
	m_pBackgroundImage->SetPosition(g_pApp->GetScreenWidth()/2, g_pApp->GetScreenHeight()/2);

	m_pFadeRect.reset(new GfxRect(0));
	m_pFadeRect->SetDimensions(g_pApp->GetScreenWidth(), g_pApp->GetScreenHeight());
	m_pFadeRect->SetPosition(g_pApp->GetScreenWidth()/2, g_pApp->GetScreenHeight()/2);
	m_pFadeRect->VSetColor(0, 0, 0);
	g_pApp->GetGfxMgr()->AddElement(m_pFadeRect);
	
	UpdatePieces();
	SetProc();
}

void MainGameState::VOnLeave()
{
	g_pApp->GetGfxMgr()->RemoveElement(m_pBackgroundImage);
	g_pApp->GetGfxMgr()->RemoveElement(m_pFadeRect);
}

void MainGameState::SetProc()
{
	ProcessSharedPtr pFadeInProc;
	pFadeInProc.reset(new FadeProcess(m_pFadeRect, 255, 0, 0.3f));
	
	GfxTextSharedPtr pText = GfxTextSharedPtr(new GfxText(-1, "operator.ttf", "GO !"));
	pText->SetPosition(g_pApp->GetScreenWidth()/2, g_pApp->GetScreenHeight()/2);
	g_pApp->GetGfxMgr()->AddElement(pText);
	ProcessSharedPtr pSpawnProc = ProcessSharedPtr(new SpawnAnimationProcess(pText, 0.004f));
	pFadeInProc->AttachChild(pSpawnProc);
	
	ProcessSharedPtr pDelayProc = ProcessSharedPtr(new DelayProcess(250));
	pSpawnProc->AttachChild(pDelayProc);
	
	m_pDisappearProc = ProcessSharedPtr(new DisappearAnimationProcess(pText, 1.0f, true));
	pDelayProc->AttachChild(m_pDisappearProc);
	
	ProcessSharedPtr pGameProc = ProcessSharedPtr(new FallingPieceProcess(m_pTetrisGrid, m_pCurrentPiece, 2.0f));
	m_pDisappearProc->AttachChild(pGameProc);
	
	AttachLogicProcess(pFadeInProc);
}

void MainGameState::UpdatePieces()
{
	ePieceType type;
	SAFE_DELETE(m_pCurrentPiece);
	
	if(!m_pNextPiece)
	{
		type = static_cast<ePieceType>(rand()%PIECETYPE_NB);
		m_pNextPiece = new TetrisPiece(type);
		m_pTetrisGrid->InitPosition(m_pNextPiece);
	}
	
	m_pCurrentPiece = m_pNextPiece;
	
	do
	{
		type = static_cast<ePieceType>(rand()%PIECETYPE_NB);
	}
	while(type == m_pCurrentPiece->GetPieceType());
	
	m_pNextPiece = new TetrisPiece(type);
	m_pTetrisGrid->InitPosition(m_pNextPiece);
}

void MainGameState::LostFocusDelegate(EventSharedPtr pEvent)
{
	//Toggle Pause
}

void MainGameState::EndTetrisLoopDelegate(EventSharedPtr pEvent)
{
	UpdatePieces();
	ProcessSharedPtr pProcess = ProcessSharedPtr(new FallingPieceProcess(m_pTetrisGrid, m_pCurrentPiece, 2.0f));
	AttachLogicProcess(pProcess);
}

void MainGameState::RegisterEvents()
{
	EventManager::Get()->AddListener(MakeDelegate(this, &MainGameState::LostFocusDelegate), ET_LOSTFOCUS);
	EventManager::Get()->AddListener(MakeDelegate(this, &MainGameState::EndTetrisLoopDelegate), ET_ENDTETRISLOOP);
}

void MainGameState::UnregisterEvents()
{
	EventManager::Get()->RemoveListener(MakeDelegate(this, &MainGameState::LostFocusDelegate), ET_LOSTFOCUS);
	EventManager::Get()->RemoveListener(MakeDelegate(this, &MainGameState::EndTetrisLoopDelegate), ET_ENDTETRISLOOP);
}
