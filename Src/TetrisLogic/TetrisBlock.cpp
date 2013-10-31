#include "TetrisBlock.h"
#include "../GameApp/SDLApp.h"
#include "../Graphics/GfxManager.h"

TetrisBlock::TetrisBlock():
m_posX(0.0f),
m_posY(0.0f)
{
	m_pGfxBlock = shared_ptr<GfxImage>(new GfxImage(0, "block24.png"));
	g_pApp->GetGfxMgr()->AddElement(m_pGfxBlock);
	UpdateGfxPosition();
}

TetrisBlock::TetrisBlock(ePieceType pieceType):
m_posX(0.0f),
m_posY(0.0f)
{
	m_pGfxBlock = shared_ptr<GfxImage>(new GfxImage(0, "block24.png"));
	g_pApp->GetGfxMgr()->AddElement(m_pGfxBlock);
	SetColor(pieceType);
	UpdateGfxPosition();
}

TetrisBlock::~TetrisBlock()
{
	g_pApp->GetGfxMgr()->RemoveElement(m_pGfxBlock);
}

void TetrisBlock::SetPieceType(ePieceType pieceType)
{
	SetColor(pieceType);
}

void TetrisBlock::SetPosition(float posX, float posY)
{
	m_posX = posX;
	m_posY = posY;
	UpdateGfxPosition();
}

void TetrisBlock::Translate(float deltaX, float deltaY)
{
	m_posX += deltaX;
	m_posY += deltaY;
	UpdateGfxPosition();
}

void TetrisBlock::UpdateGfxPosition()
{
	m_pGfxBlock->SetPosition(m_posX, m_posY);
}

void TetrisBlock::SetColor(ePieceType pieceType)
{
	switch(pieceType)
	{
		case PT_IBLOCK :
			m_pGfxBlock->VSetColor(0, 128, 255);
			break;
			
		case PT_JBLOCK :
			m_pGfxBlock->VSetColor(0, 0, 255);
			break;
		
		case PT_TBLOCK :
			m_pGfxBlock->VSetColor(160, 45, 220);
			break;
			
		case PT_LBLOCK :
			m_pGfxBlock->VSetColor(255, 140, 20);
			break;
			
		case PT_ZBLOCK :
			m_pGfxBlock->VSetColor(255, 20, 20);
			break;
			
		case PT_OBLOCK :
			m_pGfxBlock->VSetColor(255, 230, 20);
			break;
			
		case PT_SBLOCK :
			m_pGfxBlock->VSetColor(0, 180, 45);
			break;
			
		default :
			break;
	}
}
