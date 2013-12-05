/**
 * \file DeleteLinesProcess.cpp 
 * \brief Process deleting full lines in Tetris grid
 */

#include "DeleteLinesProcess.h"
#include "FallingPieceProcess.h"
#include "FallingLinesProcess.h"
#include "DisappearAnimationProcess.h"
#include "../../GameApp/SDLApp.h"
#include "../../Event/EventManager.h"
#include "../../Event/Events/Evt_AttachLogicProcess.h"
#include "../../Event/Events/Evt_EndTetrisLoop.h"

DeleteLinesProcess::DeleteLinesProcess(TetrisGrid *pGrid, float speed):
m_pGrid(pGrid),
m_speed(speed),
m_time(0)
{
}

DeleteLinesProcess::~DeleteLinesProcess()
{
}

void DeleteLinesProcess::VUpdate(unsigned int elapsedTime)
{
	m_time += m_speed*elapsedTime;
	
	if(m_time > 125)
	{
		m_time = 0;
		for(unsigned int i=0; i<m_linesToDelete.size(); i++)
		{
			if(m_leftIt >= 0)
				AttachAnimationProc(m_leftIt, m_linesToDelete[i]);
			
			if(m_rightIt <= m_pGrid->GetWidth()-1)
				AttachAnimationProc(m_rightIt, m_linesToDelete[i]);
		}
		
		m_leftIt--;
		m_rightIt++;
	}
	
	if(m_pLastAnimProc[0] && m_pLastAnimProc[1])
	{
		if(m_pLastAnimProc[0]->IsDone() && m_pLastAnimProc[1]->IsDone())
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
	for(unsigned int j=0; j<m_linesToDelete.size(); j++)
	{
		for(int i=0; i<m_pGrid->GetWidth()-1; i++)
			m_pGrid->RemoveBlock(i, m_linesToDelete[j]);
	}
	
	if(m_linesToDelete.size() > 0)
	{
		ProcessSharedPtr pProc;
		pProc.reset(new FallingLinesProcess(m_pGrid, 0.01f, m_linesToDelete));
		AttachChild(pProc);
	}
	else
	{
		EventSharedPtr pEvt;
		pEvt.reset(new Evt_EndTetrisLoop());
		EventManager::Get()->QueueEvent(pEvt);
	}
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

void DeleteLinesProcess::AttachAnimationProc(int i, int j)
{
	GfxImageSharedPtr pImage = m_pGrid->GetBlock(i, j)->GetGfxImage();
	
	ProcessSharedPtr pProc;
	shared_ptr<Evt_AttachLogicProcess> pEvt;
	
	pProc.reset(new DisappearAnimationProcess(pImage, 1.0f));
	pEvt.reset(new Evt_AttachLogicProcess(pProc));
	EventManager::Get()->QueueEvent(pEvt);
	
	if(i == 0)
	{
		m_pLastAnimProc[0] = pProc;
	}
	else if(i == m_pGrid->GetWidth() - 1)
	{
		m_pLastAnimProc[1] = pProc;
	}
}
