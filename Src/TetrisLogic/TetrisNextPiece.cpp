#include "TetrisNextPiece.h"
#include "../GameApp/SDLApp.h"
#include "../Graphics/GfxManager.h"

TetrisNextPiece::TetrisNextPiece(int width, int height, int posX, int posY):
m_width(width),
m_height(height),
m_posX(posX),
m_posY(posY)
{
	m_pTitle.reset(new GfxText(2, "operator.ttf", "Next piece"));
	m_pTitle->SetPosition(posX + width/2, posY + height/8);
	m_pTitle->SetScale((width/240)*0.4f);
	g_pApp->GetGfxMgr()->AddElement(m_pTitle);
}

TetrisNextPiece::~TetrisNextPiece()
{
	g_pApp->GetGfxMgr()->RemoveElement(m_pTitle);
	if(m_pImage)
		g_pApp->GetGfxMgr()->RemoveElement(m_pImage);
}

void TetrisNextPiece::UpdateNextPiece(ePieceType type)
{
	if(m_pImage)
		g_pApp->GetGfxMgr()->RemoveElement(m_pImage);
		
	SDL_Color color;
	color = TetrisGfxBlock::GetColor(type);
	m_pImage.reset(new GfxImage(0, TetrisPiece::GetPieceFile(type)));
	g_pApp->GetGfxMgr()->AddElement(m_pImage);
	m_pImage->VSetColor(color.r, color.g, color.b);
	m_pImage->SetPosition(m_posX + m_width/2, m_posY + m_height/8*5);
}
