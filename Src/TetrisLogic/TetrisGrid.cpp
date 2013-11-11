#include "TetrisGrid.h"
#include "../GameApp/SDLApp.h"
#include "../Graphics/GfxManager.h"

TetrisGrid::TetrisGrid(int width, int height, int posX, int posY):
m_width(width),
m_height(height),
m_posX(posX),
m_posY(posY)
{
	m_pGfxGrid = shared_ptr<GfxImage>(new GfxImage(2, "grid24.png"));
	float posGridX = TetrisGfxBlock::s_pieceSize*m_width/2 + m_posX;
	float posGridY = TetrisGfxBlock::s_pieceSize*m_height/2 + m_posY;
	m_pGfxGrid->SetPosition(posGridX, posGridY);
	g_pApp->GetGfxMgr()->AddElement(m_pGfxGrid);
	m_pGfxGrid->VSetAlpha(40);
	
	AllocateBlocksArray();
}

TetrisGrid::~TetrisGrid()
{
	g_pApp->GetGfxMgr()->RemoveElement(m_pGfxGrid);
	DeallocateBlocksArray();
}

void TetrisGrid::AddBlock(int i, int j, ePieceType pieceType)
{
	if(i < 0 || i >= m_width || j < 0 || j >= m_height || m_pBlocksArray[j*m_width + i])
	{
		ERROR("Failed to add block (" << i << ", " << j << ")");
		return;
	}
	
	m_pBlocksArray[j*m_width + i] = new TetrisGfxBlock(1, pieceType);
	
	float posX = TetrisGfxBlock::s_pieceSize*(i + 0.5f) + m_posX;
	float posY = TetrisGfxBlock::s_pieceSize*(j + 0.5f) + m_posY; 
	m_pBlocksArray[j*m_width + i]->GetGfxImage()->SetPosition(posX, posY); 
}

void TetrisGrid::MoveBlock(int i1, int j1, int i2, int j2)
{
	if(!m_pBlocksArray[j1*m_width + i1] || m_pBlocksArray[j2*m_width + i2])
	{
		ERROR("Failed to move block from (" << i1 << ", " << j1 << ") to (" << i2 << ", " << j2 << ")");
		return;
	}
	
	m_pBlocksArray[j2*m_width + i2] = m_pBlocksArray[j1*m_width + i1];
	m_pBlocksArray[j1*m_width + i1] = NULL;
	
	float posX = TetrisGfxBlock::s_pieceSize*(i2 + 0.5f) + m_posX;
	float posY = TetrisGfxBlock::s_pieceSize*(j2 + 0.5f) + m_posY; 
	m_pBlocksArray[j2*m_width + i2]->GetGfxImage()->SetPosition(posX, posY);
}

void TetrisGrid::RemoveBlock(int i, int j)
{
	if(!m_pBlocksArray[j*m_width + i])
	{
		ERROR("Failed to remove block (" << i << ", " << j << ")");
		return;
	}
	
	delete m_pBlocksArray[j*m_width + i];
	m_pBlocksArray[j*m_width + i] = NULL;
}

void TetrisGrid::LowerBlocks(int line)
{
	for(int i=0; i<m_width; i++)
	{
		if(GetBlock(i, line))
			RemoveBlock(i, line);
	}
	
	for(int j=line; j>0; j--)
	{
		for(int i=0; i<m_width; i++)
		{
			if(GetBlock(i, j-1))
				MoveBlock(i, j-1, i, j);
		}
	}
}

TetrisGfxBlock* TetrisGrid::GetBlock(int i, int j) const
{
	return m_pBlocksArray[j*m_width + i];
}


void TetrisGrid::InitPosition(TetrisPiece *pPiece)
{
	pPiece->InitPosition((m_width - 1)/2, 2);
}

void TetrisGrid::InitPosition(GfxImageSharedPtr pImage)
{
	float posX = m_posX + (((m_width - 1)/2 + 0.5f)*TetrisGfxBlock::s_pieceSize);
	float posY = m_posY + 2.5f*TetrisGfxBlock::s_pieceSize;
	pImage->SetPosition(posX, posY);
}

void TetrisGrid::AllocateBlocksArray()
{
	m_pBlocksArray = new TetrisGfxBlock*[m_width*m_height];
	for(int i=0; i<m_width*m_height; i++)
		m_pBlocksArray[i] = NULL;
}

void TetrisGrid::DeallocateBlocksArray()
{
	for(int i=0; i<m_width*m_height; i++)
	{
		if(m_pBlocksArray[i])
		{
			delete m_pBlocksArray[i];
			m_pBlocksArray[i] = NULL;
		}
	}
}
