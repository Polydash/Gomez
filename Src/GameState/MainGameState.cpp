#include "MainGameState.h"
#include "../GameStd.h"
#include "../GameApp/SDLApp.h"
#include "../Graphics/GfxManager.h"
#include "../Event/EventManager.h"
#include "../Event/Events/Evt_MainGameInput.h"
#include "../Event/Events/Evt_LostFocus.h"
#include "../Event/Events/Evt_EndTetrisLoop.h"
#include "../Event/Events/Evt_StateChange.h"
#include "../Event/Events/Evt_AddScore.h"
#include "../Resource/ResourceManager.h"
#include "../Process/Processes/FallingPieceProcess.h"
#include "../Process/Processes/SpawnAnimationProcess.h"
#include "../Process/Processes/DisappearAnimationProcess.h"
#include "../Process/Processes/HorizontalScrollProcess.h"
#include "../Process/Processes/DelayProcess.h"
#include "../Process/Processes/FadeProcess.h"
#include "../Process/Processes/LinearMoveProcess.h"
#include "../TetrisLogic/TetrisGrid.h"
#include "../TetrisLogic/TetrisPiece.h"
#include "../TetrisLogic/TetrisScore.h"
#include "../TetrisLogic/TetrisNextPiece.h"

MainGameState::MainGameState():
m_pTetrisGrid(NULL),
m_pTetrisScore(NULL),
m_pTetrisGfxNextPiece(NULL),
m_pCurrentPiece(NULL),
m_pNextPiece(NULL),
m_moveRight(false),
m_moveLeft(false),
m_joystickDeadZone(true),
m_inputRepeat(0)
{
	RegisterEvents();
}

MainGameState::~MainGameState()
{
	UnregisterEvents();
	
	SAFE_DELETE(m_pTetrisScore);
	SAFE_DELETE(m_pTetrisGfxNextPiece);
	SAFE_DELETE(m_pTetrisGrid);
	SAFE_DELETE(m_pCurrentPiece);
	SAFE_DELETE(m_pNextPiece);
}

void MainGameState::VOnInput(const SDL_Event &event)
{
	//Possibly send some input to UI
	
	if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
		OnKeyboardEvent(event);	
		
	if(event.type == SDL_JOYAXISMOTION || event.type == SDL_JOYBUTTONDOWN || event.type == SDL_JOYBUTTONUP)
		OnJoystickEvent(event);
}

void MainGameState::VOnUpdate(unsigned int elapsedTime)
{	
	if(m_pFadeOutProc && m_pFadeOutProc->IsDone())
	{
		EventSharedPtr pEvt;
		pEvt.reset(new Evt_StateChange(GS_MENU));
		EventManager::Get()->QueueEvent(pEvt);
	}
	
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
	g_linesCleared = 0;
	INFO("Entering MAINGAME state");
	LOG("Entering MAINGAME state");
	ResourceManager::Get()->Clear();
	
	m_pTetrisGrid = new TetrisGrid(10, 20, g_pApp->GetScreenHeight()/10, g_pApp->GetScreenHeight()/10);
	m_pTetrisScore = new TetrisScore(240, 150, 500, 60);
	m_pTetrisGfxNextPiece = new TetrisNextPiece(240, 200, 500, 260);
	
	m_pBackgroundImage.reset(new GfxImage(2, "background.png"));
	g_pApp->GetGfxMgr()->AddElement(m_pBackgroundImage);
	m_pBackgroundImage->SetPosition(g_pApp->GetScreenWidth()/2, g_pApp->GetScreenHeight()/2);

	m_pFadeRect.reset(new GfxRect(0));
	m_pFadeRect->SetDimensions(g_pApp->GetScreenWidth(), g_pApp->GetScreenHeight());
	m_pFadeRect->SetPosition(g_pApp->GetScreenWidth()/2, g_pApp->GetScreenHeight()/2);
	m_pFadeRect->VSetColor(0, 0, 0);
	g_pApp->GetGfxMgr()->AddElement(m_pFadeRect);
	
	m_pScrollingProc[0].reset(new HorizontalScrollProcess(0.05f, 5, "starsBG.png"));
	m_pScrollingProc[1].reset(new HorizontalScrollProcess(0.07f, 4, "starsFG.png"));
	m_pScrollingProc[2].reset(new HorizontalScrollProcess(0.1f, 3, "starsFG2.png"));
	
	AttachLogicProcess(m_pScrollingProc[0]);
	AttachLogicProcess(m_pScrollingProc[1]);
	AttachLogicProcess(m_pScrollingProc[2]);
	
	UpdatePieces();
	SetProc();
}

void MainGameState::VOnLeave()
{
	INFO("Lines : " << g_linesCleared);
	m_pScrollingProc[0]->Success();
	m_pScrollingProc[1]->Success();
	m_pScrollingProc[2]->Success();
	
	g_pApp->GetGfxMgr()->RemoveElement(m_pBackgroundImage);
	g_pApp->GetGfxMgr()->RemoveElement(m_pFadeRect);
}

bool MainGameState::CheckCollision()
{
	int **positions = m_pCurrentPiece->GetPositions();
	int centerX = m_pCurrentPiece->GetCenterX();
	int centerY = m_pCurrentPiece->GetCenterY();
	int gridWidth = m_pTetrisGrid->GetWidth();
	int gridHeight = m_pTetrisGrid->GetHeight();
	
	if(centerX < 0 || centerX >= gridWidth || centerY < 0 || centerY >= gridHeight)
		return true;
		
	if(m_pTetrisGrid->GetBlock(centerX, centerY) != NULL)
		return true;
		
	for(int i=0; i<3; i++)
	{
		int x = centerX + positions[i][0];
		int y = centerY + positions[i][1];
		
		if(x < 0 || x >= gridWidth || y < 0 || y >= gridHeight)
			return true;
			
		if(m_pTetrisGrid->GetBlock(x, y) != NULL)
			return true;
	}
		
	return false;
}

void MainGameState::SetProc()
{
	ProcessSharedPtr pFadeInProc;
	pFadeInProc.reset(new FadeProcess(m_pFadeRect, 255, 0, 0.3f));
	
	GfxTextSharedPtr pText = GfxTextSharedPtr(new GfxText(1, "operator.ttf", "GO !"));
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
	m_pTetrisGfxNextPiece->UpdateNextPiece(m_pNextPiece->GetPieceType());
}

void MainGameState::OnKeyboardEvent(const SDL_Event &event)
{
	if(event.type == SDL_KEYDOWN && !event.key.repeat)
	{
		EventSharedPtr pEvt;
		switch(event.key.keysym.sym)
		{
			case SDLK_ESCAPE :
				if(!m_pFadeOutProc && m_pDisappearProc && m_pDisappearProc->IsDone())
				{				
					pEvt.reset(new Evt_StateChange(GS_MENU));
					EventManager::Get()->QueueEvent(pEvt);
					AbortAllProcesses();
				}
				break;
			
			case SDLK_SPACE :
				pEvt.reset(new Evt_MainGameInput(GI_DROP));
				EventManager::Get()->QueueEvent(pEvt);
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
				pEvt.reset(new Evt_MainGameInput(GI_LOWER, true));
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
				pEvt.reset(new Evt_MainGameInput(GI_LOWER, false));
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

void MainGameState::OnJoystickEvent(const SDL_Event &event)
{
	const int inputZone = 20000;
	const int deadZone = 10000;
	
	if(event.type == SDL_JOYAXISMOTION && event.jaxis.axis == 0)
	{
		EventSharedPtr pEvt;
		if(event.jaxis.value > inputZone && m_joystickDeadZone)
		{
			m_moveRight = true;
			m_joystickDeadZone = false;
			pEvt.reset(new Evt_MainGameInput(GI_MOVERIGHT));
			EventManager::Get()->QueueEvent(pEvt);
		}
		else if(event.jaxis.value < -inputZone && m_joystickDeadZone)
		{
			m_moveLeft = true;
			m_joystickDeadZone = false;
			pEvt.reset(new Evt_MainGameInput(GI_MOVELEFT));
			EventManager::Get()->QueueEvent(pEvt);
		}
		else if(fabs(event.jaxis.value) < deadZone)
		{
			m_joystickDeadZone = true;
			m_moveLeft = false;
			m_moveRight = false;
		}
	}
	
	if(event.type == SDL_JOYBUTTONDOWN)
	{
		EventSharedPtr pEvt;
		switch(event.jbutton.button)
		{
			case 2 : 
				pEvt.reset(new Evt_MainGameInput(GI_ROTATE));
				EventManager::Get()->QueueEvent(pEvt);
				break;
				
			case 0 :
				pEvt.reset(new Evt_MainGameInput(GI_LOWER, true));
				EventManager::Get()->QueueEvent(pEvt);
				break;
			
			case 1 :
				pEvt.reset(new Evt_MainGameInput(GI_DROP));
				EventManager::Get()->QueueEvent(pEvt);
				break;
			
			case 7 :
				if(!m_pFadeOutProc && m_pDisappearProc && m_pDisappearProc->IsDone())
				{				
					pEvt.reset(new Evt_StateChange(GS_MENU));
					EventManager::Get()->QueueEvent(pEvt);
					AbortAllProcesses();
				}
				break;
		}
	}
	else if(event.type == SDL_JOYBUTTONUP && event.jbutton.button == 0)
	{
		EventSharedPtr pEvt;
		pEvt.reset(new Evt_MainGameInput(GI_LOWER, false));
		EventManager::Get()->QueueEvent(pEvt);
	}
}

void MainGameState::LostFocusDelegate(EventSharedPtr pEvent)
{
	//Toggle Pause
}

void MainGameState::EndTetrisLoopDelegate(EventSharedPtr pEvent)
{
	UpdatePieces();
	
	if(!CheckCollision())
	{
		ProcessSharedPtr pProcess = ProcessSharedPtr(new FallingPieceProcess(m_pTetrisGrid, m_pCurrentPiece, 2.0f));
		AttachLogicProcess(pProcess);
	}
	else
	{
		ProcessSharedPtr pFadeProc = ProcessSharedPtr(new FadeProcess(m_pFadeRect, 0, 192, 0.3f));
		
		GfxTextSharedPtr pText = GfxTextSharedPtr(new GfxText(-1, "operator.ttf", "Game Over"));
		pText->SetPosition(g_pApp->GetScreenWidth()/2, g_pApp->GetScreenHeight()/2);
		g_pApp->GetGfxMgr()->AddElement(pText);
		ProcessSharedPtr pSpawnProc = ProcessSharedPtr(new SpawnAnimationProcess(pText, 0.004f));
		pFadeProc->AttachChild(pSpawnProc);
		
		ProcessSharedPtr pDelayProc = ProcessSharedPtr(new DelayProcess(2500));
		pSpawnProc->AttachChild(pDelayProc);
		
		ProcessSharedPtr pDisappearProc = ProcessSharedPtr(new DisappearAnimationProcess(pText, 1.0f, true));
		pDelayProc->AttachChild(pDisappearProc);
		
		m_pFadeOutProc.reset(new FadeProcess(m_pFadeRect, 255, 0.3f));
		pDisappearProc->AttachChild(m_pFadeOutProc);
		
		AttachLogicProcess(pFadeProc);
	}
}

void MainGameState::AddScoreDelegate(EventSharedPtr pEvent)
{
	shared_ptr<Evt_AddScore> pEvt = static_pointer_cast<Evt_AddScore>(pEvent);
	unsigned int scoreToAdd = pEvt->GetScore();
	
	int max = 1;
	if(scoreToAdd == TetrisScore::GetScoreValue(4))
		max = 10;
		
	for(int i=0; i<max; i++)
	{
		float sourceX = -100;
		float destX = g_pApp->GetScreenWidth() + 100;
		float posY = ((float) rand()/RAND_MAX)*g_pApp->GetScreenHeight();
		
		ProcessSharedPtr pEasterEggProc;
		GfxImageSharedPtr pImage;
		pImage.reset(new GfxImage(4, "easter.png"));
		pImage->SetPosition(sourceX, posY);
		g_pApp->GetGfxMgr()->AddElement(pImage);
		pEasterEggProc.reset(new LinearMoveProcess(pImage, destX, posY, 0.6f, true));
		
		if(i > 0)
		{
			ProcessSharedPtr pDelayProc;
			pDelayProc.reset(new DelayProcess(250*i));
			pDelayProc->AttachChild(pEasterEggProc);
			AttachLogicProcess(pDelayProc);			
		}
		else
			AttachLogicProcess(pEasterEggProc);
	}
}

void MainGameState::RegisterEvents()
{
	EventManager::Get()->AddListener(MakeDelegate(this, &MainGameState::LostFocusDelegate), ET_LOSTFOCUS);
	EventManager::Get()->AddListener(MakeDelegate(this, &MainGameState::EndTetrisLoopDelegate), ET_ENDTETRISLOOP);
	EventManager::Get()->AddListener(MakeDelegate(this, &MainGameState::AddScoreDelegate), ET_ADDSCORE);
}

void MainGameState::UnregisterEvents()
{
	EventManager::Get()->RemoveListener(MakeDelegate(this, &MainGameState::LostFocusDelegate), ET_LOSTFOCUS);
	EventManager::Get()->RemoveListener(MakeDelegate(this, &MainGameState::EndTetrisLoopDelegate), ET_ENDTETRISLOOP);
	EventManager::Get()->RemoveListener(MakeDelegate(this, &MainGameState::AddScoreDelegate), ET_ADDSCORE);
}
