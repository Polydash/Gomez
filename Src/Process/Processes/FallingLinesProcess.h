#ifndef FALLINGLINESPROCESS_H
#define FALLINGLINESPROCESS_H

#include <vector>

#include "../Process.h"
#include "../../TetrisLogic/TetrisGrid.h"

class FallingLinesProcess : public Process
{
	private :
	
		TetrisGrid *m_pGrid;
	
		float m_speed;
		
		std::vector<int> m_linesToDelete;
		ProcessSharedPtr m_lastProc;
		
	public : 
	
		FallingLinesProcess(TetrisGrid *pGrid, float speed, const std::vector<int> &linesToDelete);
		~FallingLinesProcess();
		
		virtual void VUpdate(unsigned int elapsedTime);
		
	protected :
	
		virtual void VOnSuccess();
		virtual bool VOnInit();
		
	private :
	
		void AttachLineAnimProc(int j, int lowerValue);
};

#endif
