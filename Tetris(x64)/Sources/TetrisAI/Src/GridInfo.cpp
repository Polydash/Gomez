/**
 * \file GridInfo.cpp 
 * \brief Stores grid information
 */

#include "GridInfo.h"

GridInfo::GridInfo(int width, int height):
m_width(width),
m_height(height)
{ 
}

void GridInfo::Set(const GridVector &grid)
{
	m_grid = grid;
}

void GridInfo::SetBlock(int i, int j, bool bVal)
{
	m_grid[j*m_width+i] = bVal;
}

void GridInfo::DeleteLine(int j)
{
	for(int it=j; it>0; it--)
	{
		for(int i=0; i<m_width; i++)
			SetBlock(i, it, Get(i, it-1));
	}
}

GridInfo* GridInfo::GetDuplicate() const
{
	GridInfo* pGrid = new GridInfo(m_width, m_height);
	pGrid->Set(m_grid);
	return pGrid;
}
