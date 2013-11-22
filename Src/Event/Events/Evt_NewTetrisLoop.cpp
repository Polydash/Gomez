#include "Evt_NewTetrisLoop.h"

Evt_NewTetrisLoop::Evt_NewTetrisLoop(TetrisGrid *pGrid, ePieceType type):
m_pieceType(type)
{
	SetGrid(pGrid);
}

Evt_NewTetrisLoop::~Evt_NewTetrisLoop()
{
}

void Evt_NewTetrisLoop::VSerialize(std::ostringstream &oss)
{
	oss << VGetType() << " ";
	oss << m_pieceType << " ";
	
	for(unsigned int i=0; i<m_grid.size(); i++)
		oss << ((m_grid[i])?"1":"0");
}

void Evt_NewTetrisLoop::VDeserialize(std::istringstream &iss)
{
	int type;
	iss >> type;
	m_pieceType = static_cast<ePieceType>(type);
	
	m_grid.clear();
	std::string str;
	iss >> str;
	
	std::string::iterator i;
	for(i = str.begin(); i != str.end(); i++)
		m_grid.push_back(*i == '1');
}

void Evt_NewTetrisLoop::SetGrid(TetrisGrid *pGrid)
{	
	int width = pGrid->GetWidth();
	int height = pGrid->GetHeight();

	m_grid.clear();
	for(int j=0; j<height; j++)
	{
		for(int i=0; i<width; i++)
			m_grid.push_back(pGrid->GetBlock(i, j));
	}
}
