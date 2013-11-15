#include "TetrisPiece.h"

TetrisPiece::TetrisPiece(ePieceType pieceType):
m_currentRotation(0),
m_pieceType(pieceType)
{
	AllocateArray();
	CreatePiece(pieceType);
}

TetrisPiece::~TetrisPiece()
{
	DeallocateArray();
}

std::string TetrisPiece::GetPieceFile(ePieceType type)
{
	std::string fileName;
	
	switch(type)
	{
		case PT_IBLOCK : 
			fileName = "ipiece24.png";
			break;
			
		case PT_JBLOCK :
			fileName = "jpiece24.png";
			break;
			
		case PT_TBLOCK :
			fileName = "tpiece24.png";
			break;
		
		case PT_LBLOCK :
			fileName = "lpiece24.png";
			break;
		
		case PT_ZBLOCK :
			fileName = "zpiece24.png";
			break;
		
		case PT_OBLOCK :
			fileName = "opiece24.png";
			break;
			
		case PT_SBLOCK :
			fileName = "spiece24.png";
			break;
		
		default :
			break;
	}
	
	return fileName;
}

void TetrisPiece::InitPosition(int centerX, int centerY)
{
	m_centerX = centerX;
	m_centerY = centerY;
}

void TetrisPiece::RotateRight()
{
	m_currentRotation = (m_currentRotation + 1) % 4;
}

void TetrisPiece::RotateLeft()
{
	m_currentRotation = (m_currentRotation - 1) % 4;
	if(m_currentRotation < 0)
		m_currentRotation += 4;
}

void TetrisPiece::Move(int x, int y)
{
	m_centerX += x;
	m_centerY += y;
}

int** TetrisPiece::GetPositions() const
{
	return m_positions[m_currentRotation];
}

void TetrisPiece::CreatePiece(ePieceType pieceType)
{
	int type = static_cast<int>(pieceType);
	
	m_positions[0][0][0] = ((type != 0) ? 1 : 0); 
	m_positions[0][0][1] = ((type > 3) ? 0 : type - 2);

	int tmp = ((type & 1) << 1) - 1;
	m_positions[0][1][0] = ((type != 4) ? 0 : 1);
	m_positions[0][1][1] = tmp;
	
	m_positions[0][2][0] = ((type > 4) ? 1 : 0);
	m_positions[0][2][1] = ((type > 4) ? 1 : -tmp);
	
	for(int i=1; i<=3; i++)
	{
		for(int j=0; j<3; j++)
		{
			m_positions[i][j][0] = -m_positions[i-1][j][1];
			m_positions[i][j][1] = m_positions[i-1][j][0];
		}
	}
}

void TetrisPiece::AllocateArray()
{
	m_positions = new int**[4];
		
	for(int i=0; i<4; i++)
	{
		m_positions[i] = new int*[3];
		
		for(int j=0; j<3; j++)
			m_positions[i][j] = new int[2];
	}
}

void TetrisPiece::DeallocateArray()
{
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<3; j++)
			delete m_positions[i][j];
		
		delete m_positions[i];
	}
	
	delete m_positions;
}
		
