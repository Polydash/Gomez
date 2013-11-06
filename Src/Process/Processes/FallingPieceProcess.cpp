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
	GfxImageSharedPtr pImage = GetImage(m_pPiece);
	m_pMoveProc.reset(new SmoothFollowProcess(pImage, 0.01f));
		
	shared_ptr<Evt_AttachLogicProcess> pEvt;
	pEvt.reset(new Evt_AttachLogicProcess(m_pMoveProc));
	EventManager::Get()->QueueEvent(pEvt);
}

void FallingPieceProcess::SetPiece()
{
	m_pPiece = new TetrisPiece(PT_SBLOCK);
}

GfxImageSharedPtr FallingPieceProcess::GetImage(TetrisPiece *pPiece)
{
	ePieceType type = pPiece->GetPieceType();
	SDL_Color color;
	GfxImageSharedPtr pImage;
	
	color = TetrisGfxBlock::GetColor(type);
	
	switch(type)
	{
		case PT_IBLOCK : 
			pImage.reset(new GfxImage(0, "ipiece24.png"));
			break;
			
		case PT_JBLOCK :
			pImage.reset(new GfxImage(0, "jpiece24.png"));
			break;
			
		case PT_TBLOCK :
			pImage.reset(new GfxImage(0, "tpiece24.png"));
			break;
		
		case PT_LBLOCK :
			pImage.reset(new GfxImage(0, "lpiece24.png"));
			break;
		
		case PT_ZBLOCK :
			pImage.reset(new GfxImage(0, "zpiece24.png"));
			break;
		
		case PT_OBLOCK :
			pImage.reset(new GfxImage(0, "opiece24.png"));
			break;
			
		case PT_SBLOCK :
			pImage.reset(new GfxImage(0, "spiece24.png"));
			break;
		
		default :
			break;
	}
	
	g_pApp->GetGfxMgr()->AddElement(pImage);
	pImage->VSetColor(color.r, color.g, color.b);
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
