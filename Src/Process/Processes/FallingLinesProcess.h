#ifndef FALLINGLINESPROCESS_H
#define FALLINGLINESPROCESS_H

/**
 * \file FallingLinesProcess.h 
 * \brief Process creating an animation for falling lines
 */

#include <vector>

#include "../Process.h"
#include "../../TetrisLogic/TetrisGrid.h"

/**
 * \class FallingLinesProcess 
 * \brief Process creating an animation for falling lines
 * 
 * Creates an animation for lines to fall smoothly as other lines may
 * have been deleted. Then, it declares the end of a game loop.
 */
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
