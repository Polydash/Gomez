#include "FallingPieceProcess.h"
#include "../../GameStd.h"
#include "../../GameApp/SDLApp.h"
#include "../../Graphics/GfxManager.h"
#include "../../Event/EventManager.h"
#include "../../Event/Events/Evt_MainGameInput.h"
#include "../../Event/Events/Evt_AttachLogicProcess.h"

FallingPieceProcess::FallingPieceProcess(TetrisGrid *pGrid):
m_pGrid(pGrid),
m_pPiece(NULL)
{
}

FallingPieceProcess::~FallingPieceProcess()
{
	SAFE_DELETE(m_pPiece);
	UnregisterEvents();
}

bool FallingPieceProcess::VOnInit()
{
	RegisterEvents();
	
	SetPiece();
	SetMoveProc();
		
	return true;
}

void FallingPieceProcess::VUpdate(unsigned int elapsedTime)
{
}

void FallingPieceProcess::SetMoveProc()
{
	GfxImageSharedPtr pImage = SetImage(m_pPiece);
	m_pMoveProc.reset(new SmoothFollowProcess(pImage, 0.01f));
		
	shared_ptr<Evt_AttachLogicProcess> pEvt;
	pEvt.reset(new Evt_AttachLogicProcess(m_pMoveProc));
	EventManager::Get()->QueueEvent(pEvt);
}

void FallingPieceProcess::SetPiece()
{
	m_pPiece = new TetrisPiece(PT_IBLOCK);
}

GfxImageSharedPtr FallingPieceProcess::SetImage(TetrisPiece *pPiece)
{
	ePieceType type = pPiece->GetPieceType();
	byte r, g, b;
	GfxImageSharedPtr pImage;
	
	switch(type)
	{
		case PT_IBLOCK : 
			pImage.reset(new GfxImage(0, "ipiece24.png"));
			r = 0; g = 128; b = 255;
			break;
			
		default :
			pImage.reset(new GfxImage(0, "block24.png"));
			r = 255; g = 255; b = 255;
			break;
	}
	
	g_pApp->GetGfxMgr()->AddElement(pImage);
	pImage->VSetColor(r, g, b);
	m_pGrid->InitPosition(pImage);
	
	return pImage;
}

void FallingPieceProcess::MainGameInputDelegate(EventSharedPtr pEvent)
{
	shared_ptr<Evt_MainGameInput> pEvt = static_pointer_cast<Evt_MainGameInput>(pEvent);
	eGameInput input = pEvt->GetInput();
	
	switch(input)
	{
		case GI_MOVELEFT :
			INFO("Moved left");
			m_pMoveProc->Translate(-TetrisGfxBlock::s_pieceSize, 0);
			break;
			
		case GI_MOVERIGHT :
			INFO("Moved right");
			m_pMoveProc->Translate(TetrisGfxBlock::s_pieceSize, 0);
			break;
			
		case GI_DROP :
			INFO("Dropped");
			m_pMoveProc->Translate(0, TetrisGfxBlock::s_pieceSize);
			break;
			
		case GI_ROTATE :
			INFO("Rotated");
			m_pMoveProc->AddAngle(90);
			break;
			
		default :
			break;
	}
}

void FallingPieceProcess::RegisterEvents()
{
	EventManager::Get()->AddListener(MakeDelegate(this, &FallingPieceProcess::MainGameInputDelegate), ET_MAINGAMEINPUT);
}

void FallingPieceProcess::UnregisterEvents()
{
	EventManager::Get()->RemoveListener(MakeDelegate(this, &FallingPieceProcess::MainGameInputDelegate), ET_MAINGAMEINPUT);
}
