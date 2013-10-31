#include "TetrisPiece.h"

const int TetrisPiece::s_pieceSize = 24;

TetrisPiece::TetrisPiece(ePieceType pieceType):
m_currentRotation(0)
{
	for(int i=0; i<4; i++)
		m_blocks[i].SetPieceType(pieceType);
		
	CreatePositions(pieceType);
	UpdateBlocks();
}

TetrisPiece::~TetrisPiece()
{
}

void TetrisPiece::RotateRight()
{
	m_currentRotation = (m_currentRotation + 1) % 4;
	UpdateBlocks();
}

void TetrisPiece::SetPosition(float posX, float posY)
{
	m_blocks[0].SetPosition(posX, posY);
	UpdateBlocks();
}

void TetrisPiece::Translate(float deltaX, float deltaY)
{
	m_blocks[0].Translate(deltaX, deltaY);
	UpdateBlocks();
}

float TetrisPiece::GetPosX() const
{
	return m_blocks[0].GetPosX();
}

float TetrisPiece::GetPosY() const
{
	return m_blocks[0].GetPosY();
}

void TetrisPiece::CreatePositions(ePieceType pieceType)
{
	int type = static_cast<int>(pieceType);
	
	m_positions[0][0][0] = ((type != 0) ? 1.0f : 0.0f); 
	m_positions[0][0][1] = ((type > 3) ? 0.0f : type - 2.0f); 
	
	int tmp = ((type & 1) << 1) - 1;
	m_positions[0][1][0] = ((type != 4) ? 0.0f : 1.0f);
	m_positions[0][1][1] = tmp;
	
	m_positions[0][2][0] = ((type > 4) ? 1.0f : 0.0f);
	m_positions[0][2][1] = ((type > 4) ? 1.0f : -tmp);
	
	for(int i=1; i<=3; i++)
	{
		for(int j=0; j<3; j++)
		{
			m_positions[i][j][0] = -m_positions[i-1][j][1];
			m_positions[i][j][1] = m_positions[i-1][j][0];
		}
	}
}

void TetrisPiece::UpdateBlocks()
{
	float x = m_blocks[0].GetPosX();
	float y = m_blocks[0].GetPosY();
	int rot = m_currentRotation;
	
	for(int i=0; i<3; i++)
		m_blocks[i+1].SetPosition(x + s_pieceSize*m_positions[rot][i][0], y + s_pieceSize*m_positions[rot][i][1]);
}
