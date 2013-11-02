#include "TetrisGfxBlock.h"
#include "../GameApp/SDLApp.h"
#include "../Graphics/GfxManager.h"

const int TetrisGfxBlock::s_pieceSize = 24;

TetrisGfxBlock::TetrisGfxBlock(int layer, ePieceType pieceType):
m_pieceType(pieceType)
{
	m_pGfxImage = shared_ptr<GfxImage>(new GfxImage(layer, "block24.png"));
	g_pApp->GetGfxMgr()->AddElement(m_pGfxImage);
	SetColor(pieceType);
}

TetrisGfxBlock::~TetrisGfxBlock()
{
	g_pApp->GetGfxMgr()->RemoveElement(m_pGfxImage);
}

void TetrisGfxBlock::SetColor(ePieceType pieceType)
{
	switch(pieceType)
	{
		case PT_IBLOCK :
			m_pGfxImage->VSetColor(0, 128, 255);
			break;
			
		case PT_JBLOCK :
			m_pGfxImage->VSetColor(0, 0, 255);
			break;
		
		case PT_TBLOCK :
			m_pGfxImage->VSetColor(160, 45, 220);
			break;
			
		case PT_LBLOCK :
			m_pGfxImage->VSetColor(255, 140, 20);
			break;
			
		case PT_ZBLOCK :
			m_pGfxImage->VSetColor(255, 20, 20);
			break;
			
		case PT_OBLOCK :
			m_pGfxImage->VSetColor(255, 230, 20);
			break;
			
		case PT_SBLOCK :
			m_pGfxImage->VSetColor(0, 180, 45);
			break;
			
		default :
			break;
	}
}
