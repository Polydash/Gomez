#include "DeleteLinesProcess.h"
#include "FallingPieceProcess.h"

DeleteLinesProcess::DeleteLinesProcess(TetrisGrid *pGrid, float speed):
m_pGrid(pGrid),
m_speed(speed)
{
}

DeleteLinesProcess::~DeleteLinesProcess()
{
}

void DeleteLinesProcess::VUpdate(unsigned int elapsedTime)
{
	static unsigned int time = 0;
	time += m_speed*elapsedTime;
	
	if(time > 100)
	{
		time = 0;
		for(unsigned int i=0; i<m_linesToDelete.size(); i++)
		{
			if(m_leftIt >= 0)
				m_pGrid->RemoveBlock(m_leftIt, m_linesToDelete[i]);
			
			if(m_rightIt <= m_pGrid->GetWidth()-1)
				m_pGrid->RemoveBlock(m_rightIt, m_linesToDelete[i]);
		}
		
		m_leftIt--;
		m_rightIt++;
		
		if(m_leftIt < 0 && m_rightIt > m_pGrid->GetWidth() - 1)
			Success();
	}
	
	if(m_linesToDelete.empty())
		Success();
}

bool DeleteLinesProcess::VOnInit()
{	
	for(int j=m_pGrid->GetHeight() - 1; j>0; j--)
	{
		if(IsLineFull(j))
			m_linesToDelete.push_back(j);
	}
	
	m_leftIt = (m_pGrid->GetWidth() - 1)/2;
	m_rightIt = m_leftIt + 1;
	
	return true;
}

void DeleteLinesProcess::VOnSuccess()
{
	for(unsigned int i=0; i<m_linesToDelete.size(); i++)
		m_pGrid->LowerBlocks(m_linesToDelete[i] + i);
	
	ProcessSharedPtr pProc = ProcessSharedPtr(new FallingPieceProcess(m_pGrid, 2.0f));
	AttachChild(pProc);
}

bool DeleteLinesProcess::IsLineFull(int j) const
{
	for(int i=0; i<m_pGrid->GetWidth(); i++)
	{
		if(!m_pGrid->GetBlock(i, j))
			return false;
	}
	
	return true;
}
