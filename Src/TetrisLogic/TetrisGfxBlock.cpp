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

SDL_Color TetrisGfxBlock::GetColor(ePieceType pieceType)
{
	SDL_Color color;
	color.r = 255; color.g = 255; color.b = 255;
	
	switch(pieceType)
	{
		case PT_IBLOCK :
			color.r = 0; color.g = 128; color.b = 255;
			break;
			
		case PT_JBLOCK :
			color.r = 0; color.g = 0; color.b = 255;
			break;
		
		case PT_TBLOCK :
			color.r = 160; color.g = 45; color.b = 120;
			break;
			
		case PT_LBLOCK :
			color.r = 255; color.g = 140; color.b = 20;
			break;
			
		case PT_ZBLOCK :
			color.r = 255; color.g = 20; color.b = 20;
			break;
			
		case PT_OBLOCK :
			color.r = 255; color.g = 230; color.b = 20;
			break;
			
		case PT_SBLOCK :
			color.r = 0; color.g = 180; color.b = 45;
			break;
			
		default :
			break;
	}
	
	return color;
}

void TetrisGfxBlock::SetColor(ePieceType pieceType)
{
	SDL_Color color = GetColor(pieceType);
	m_pGfxImage->VSetColor(color.r, color.g, color.b);
}
