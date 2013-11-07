#include "DeleteLinesProcess.h"
#include "FallingPieceProcess.h"

DeleteLinesProcess::DeleteLinesProcess(TetrisGrid *pGrid):
m_pGrid(pGrid)
{
}

DeleteLinesProcess::~DeleteLinesProcess()
{
}

bool DeleteLinesProcess::VOnInit()
{	
	for(int j=0; j<m_pGrid->GetHeight(); j++)
	{
		std::string str = "|";
		for(int i=0; i<m_pGrid->GetWidth(); i++)
		{
			if(m_pGrid->GetBlock(i, j))
				str += " X |";
			else
				str += "   |";
		}
		
		LOG(str);
	}
	
	for(int j=m_pGrid->GetHeight() - 1; j>0; j--)
	{
		if(IsLineFull(j))
		{
			m_pGrid->LowerBlocks(j);
			j++;
		}
	}
	
	Success();
	
	return true;
}

void DeleteLinesProcess::VOnSuccess()
{
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
