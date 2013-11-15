#include "FallingLinesProcess.h"
#include "SmoothFollowProcess.h"
#include "FallingPieceProcess.h"
#include "../../GameApp/SDLApp.h"
#include "../../Event/EventManager.h"
#include "../../Event/Events/Evt_AttachLogicProcess.h"
#include "../../Event/Events/Evt_EndTetrisLoop.h"
#include "../../Event/Events/Evt_AddScore.h"
#include "../../TetrisLogic/TetrisScore.h"

FallingLinesProcess::FallingLinesProcess(TetrisGrid *pGrid, float speed, const std::vector<int> &linesToDelete):
m_pGrid(pGrid),
m_speed(speed),
m_linesToDelete(linesToDelete)
{
}

FallingLinesProcess::~FallingLinesProcess()
{
}

void FallingLinesProcess::VUpdate(unsigned int elapsedTime)
{
	if(!m_lastProc || m_lastProc->IsDone())
		Success();
}

void FallingLinesProcess::VOnSuccess()
{	
	for(unsigned int i=0; i<m_linesToDelete.size(); i++)
		m_pGrid->LowerBlocks(m_linesToDelete[i] + i);
		
	EventSharedPtr pEvt;
	pEvt.reset(new Evt_EndTetrisLoop());
	EventManager::Get()->QueueEvent(pEvt);
}

bool FallingLinesProcess::VOnInit()
{
	for(unsigned int i=0; i<m_linesToDelete.size(); i++)
	{
		int min;
		if(i == m_linesToDelete.size() - 1)
			min = 0;
		else
			min = m_linesToDelete[i+1];
			
		for(int j=m_linesToDelete[i]-1; j>min; j--)
		{
			AttachLineAnimProc(j, i+1);
		}
	}
	
	if(m_linesToDelete.size() > 0)
	{
		EventSharedPtr pEvt;
		pEvt.reset(new Evt_AddScore(TetrisScore::GetScoreValue(m_linesToDelete.size())));
		EventManager::Get()->QueueEvent(pEvt);
	}
	
	return true;
}

void FallingLinesProcess::AttachLineAnimProc(int j, int lowerValue)
{
	shared_ptr<SmoothFollowProcess> pProc;
	shared_ptr<Evt_AttachLogicProcess> pEvt;
	
	for(int i=0; i<m_pGrid->GetWidth(); i++)
	{
		if(m_pGrid->GetBlock(i,j))
		{
			GfxImageSharedPtr pImage = m_pGrid->GetBlock(i, j)->GetGfxImage();
	
			pProc.reset(new SmoothFollowProcess(pImage, m_speed, true));
			pProc->Translate(0.0f, TetrisGfxBlock::s_pieceSize*lowerValue);
			pEvt.reset(new Evt_AttachLogicProcess(pProc));
			EventManager::Get()->QueueEvent(pEvt);
			m_lastProc = pProc;
		}
	}
}
