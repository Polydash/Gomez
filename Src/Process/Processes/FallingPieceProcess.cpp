#include "FallingPieceProcess.h"
#include "DroppedPieceProcess.h"
#include "SpawnAnimationProcess.h"
#include "DeleteLinesProcess.h"
#include "../../GameStd.h"
#include "../../GameApp/SDLApp.h"
#include "../../Graphics/GfxManager.h"
#include "../../Network/Server.h"
#include "../../Event/EventManager.h"
#include "../../Event/Events/Evt_MainGameInput.h"
#include "../../Event/Events/Evt_AttachLogicProcess.h"
#include "../../Event/Events/Evt_NewTetrisLoop.h"

FallingPieceProcess::FallingPieceProcess(TetrisGrid *pGrid, TetrisPiece *pPiece, float speed):
m_pGrid(pGrid),
m_pPiece(pPiece),
m_speed(speed),
m_timeCount(0),
m_bIsDone(false),
m_bLowerAccel(false),
m_bIsDropped(false)
{
}

FallingPieceProcess::~FallingPieceProcess()
{
	UnregisterEvents();
}

void FallingPieceProcess::VUpdate(unsigned int elapsedTime)
{	
	if(m_bLowerAccel)
		m_timeCount += elapsedTime*m_speed*15;
	else
		m_timeCount += elapsedTime*m_speed;
	
	
	if(m_timeCount >= 1000 && !m_bIsDone)
	{
		m_timeCount = 0;
		if(!Lower())
			m_bIsDone = true;
	}
	
	if(m_bIsDone && !m_pMoveProc->IsMoving(1.0f))
	{
		m_pMoveProc->Success();
		Success();
	}
}

bool FallingPieceProcess::VOnInit()
{
	RegisterEvents();
	SetProc();
	BroadcastNewLoop();
		
	return true;
}

void FallingPieceProcess::VOnSuccess()
{
	if(!m_bIsDropped)
	{	
		PlacePiece();
		g_pApp->GetGfxMgr()->RemoveElement(m_pImage);
	}
	else
		DropPiece();
}

void FallingPieceProcess::VOnAbort()
{
	g_pApp->GetGfxMgr()->RemoveElement(m_pImage);
}

bool FallingPieceProcess::Move(bool bMoveToRight)
{
	int x = 1;
	if(!bMoveToRight)
		x *= -1;
	
	m_pPiece->Move(x, 0);
	if(CheckCollision())
	{
		m_pPiece->Move(-x, 0);
		return false;
	}
	else
	{
		m_pMoveProc->Translate(x*TetrisGfxBlock::s_pieceSize, 0);
		return true;
	}
}

bool FallingPieceProcess::Lower()
{
	m_pPiece->Move(0, 1);
	if(CheckCollision())
	{
		m_pPiece->Move(0, -1);
		return false;
	}
	else
	{
		m_pMoveProc->Translate(0, TetrisGfxBlock::s_pieceSize);
	}
		
	return true;
}

void FallingPieceProcess::Rotate()
{
	bool result = true;
	
	if(m_pPiece->GetPieceType() == PT_OBLOCK)
	{
		m_pMoveProc->AddAngle(90);
		return;
	}
	
	m_pPiece->RotateRight();
	if(CheckCollision() && !Move(true) && !Move(false))
	{
		m_pPiece->RotateLeft();
		result = false;
	}
	
	if(result)
		m_pMoveProc->AddAngle(90);
}

bool FallingPieceProcess::CheckCollision()
{
	int **positions = m_pPiece->GetPositions();
	int centerX = m_pPiece->GetCenterX();
	int centerY = m_pPiece->GetCenterY();
	int gridWidth = m_pGrid->GetWidth();
	int gridHeight = m_pGrid->GetHeight();
	
	if(centerX < 0 || centerX >= gridWidth || centerY < 0 || centerY >= gridHeight)
		return true;
		
	if(m_pGrid->GetBlock(centerX, centerY) != NULL)
		return true;
		
	for(int i=0; i<3; i++)
	{
		int x = centerX + positions[i][0];
		int y = centerY + positions[i][1];
		
		if(x < 0 || x >= gridWidth || y < 0 || y >= gridHeight)
			return true;
			
		if(m_pGrid->GetBlock(x, y) != NULL)
			return true;
	}
		
	return false;
}

void FallingPieceProcess::PlacePiece()
{
	int **positions = m_pPiece->GetPositions();
	ePieceType type = m_pPiece->GetPieceType();
	int centerX = m_pPiece->GetCenterX();
	int centerY = m_pPiece->GetCenterY();
	
	m_pGrid->AddBlock(centerX, centerY, type);
	
	for(int i=0; i<3; i++)
	{
		int x = centerX + positions[i][0];
		int y = centerY + positions[i][1];
		
		m_pGrid->AddBlock(x, y, type);
	}
	
	ProcessSharedPtr pProc = ProcessSharedPtr(new DeleteLinesProcess(m_pGrid, 1.0f));
	AttachChild(pProc);
}

void FallingPieceProcess::DropPiece()
{
	ProcessSharedPtr pProc = ProcessSharedPtr(new DroppedPieceProcess(m_pGrid, m_pPiece, m_pImage));
	AttachChild(pProc);
}

void FallingPieceProcess::SetProc()
{
	SetImage(m_pPiece);
	m_pMoveProc.reset(new SmoothFollowProcess(m_pImage, 0.01f));
	
	shared_ptr<Evt_AttachLogicProcess> pEvt;
	pEvt.reset(new Evt_AttachLogicProcess(m_pMoveProc));
	EventManager::Get()->QueueEvent(pEvt);
	
	ProcessSharedPtr m_pSpawn;
	m_pSpawn.reset(new SpawnAnimationProcess(m_pImage, 0.008f));
	
	pEvt.reset(new Evt_AttachLogicProcess(m_pSpawn));
	EventManager::Get()->QueueEvent(pEvt);
}

void FallingPieceProcess::SetImage(TetrisPiece *pPiece)
{
	ePieceType type = pPiece->GetPieceType();
	SDL_Color color;
	
	color = TetrisGfxBlock::GetColor(type);
	m_pImage.reset(new GfxImage(0, TetrisPiece::GetPieceFile(type)));
	g_pApp->GetGfxMgr()->AddElement(m_pImage);
	m_pImage->VSetColor(color.r, color.g, color.b);
	m_pGrid->InitPosition(m_pImage);
	
	if(m_pPiece->GetPieceType() == PT_OBLOCK)
		m_pImage->Translate(TetrisGfxBlock::s_pieceSize*0.5f, TetrisGfxBlock::s_pieceSize*0.5f);
}

void FallingPieceProcess::MainGameInputDelegate(EventSharedPtr pEvent)
{
	shared_ptr<Evt_MainGameInput> pEvt = static_pointer_cast<Evt_MainGameInput>(pEvent);
	eGameInput input = pEvt->GetInput();
	
	if(!m_bIsDone)
	{
		switch(input)
		{
			case GI_MOVELEFT :
				Move(false);
				break;
				
			case GI_MOVERIGHT :
				Move(true);
				break;
				
			case GI_LOWER :
				if(pEvt->GetPressed())
					m_bLowerAccel = true;
				else
					m_bLowerAccel = false;
				break;
			
			case GI_DROP :
				m_bIsDone = true;
				m_bIsDropped = true;
				break;
				
			case GI_ROTATE :
				Rotate();
				break;
				
			default :
				break;
		}
	}
}

void FallingPieceProcess::BroadcastNewLoop()
{
	EventSharedPtr pEvt;
	pEvt.reset(new Evt_NewTetrisLoop(m_pGrid, m_pPiece->GetPieceType()));
	
	std::ostringstream oss;
	pEvt->VSerialize(oss);
	g_pApp->GetServer()->Broadcast(oss);
}

void FallingPieceProcess::RegisterEvents()
{
	EventManager::Get()->AddListener(MakeDelegate(this, &FallingPieceProcess::MainGameInputDelegate), ET_MAINGAMEINPUT);
}

void FallingPieceProcess::UnregisterEvents()
{
	EventManager::Get()->RemoveListener(MakeDelegate(this, &FallingPieceProcess::MainGameInputDelegate), ET_MAINGAMEINPUT);
}
