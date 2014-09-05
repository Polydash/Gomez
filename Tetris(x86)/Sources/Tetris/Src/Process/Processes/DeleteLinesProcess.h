#ifndef DELETELINESPROCESS_H
#define DELETELINESPROCESS_H

/**
 * \file DeleteLinesProcess.h 
 * \brief Process deleting full lines in Tetris grid
 */

#include "../Process.h"
#include "../../TetrisLogic/TetrisGrid.h"
#include <vector>

/**
 * \class DeleteLinesProcess 
 * \brief Process deleting full lines in Tetris grid
 * 
 * This Process checks if the grid contains lines that should be deleted.
 * If there are lines to delete, blocks are faded out with an animation
 * and then a FallingLinesProcess is attached. If there are no lines to 
 * delete, it declares the end of a game loop.
 */
class DeleteLinesProcess : public Process
{
private :

	TetrisGrid *m_pGrid;
	
	float m_speed;
	int m_leftIt, m_rightIt;
	unsigned int m_time;
	
	std::vector<int> m_linesToDelete;
	
	ProcessSharedPtr m_pLastAnimProc[2];
	
public :

	DeleteLinesProcess(TetrisGrid *pGrid, float speed);
	~DeleteLinesProcess();
	
	virtual void VUpdate(unsigned int elapsedTime);
	
protected :

	virtual bool VOnInit();
	virtual void VOnSuccess();

private :

	bool IsLineFull(int i) const;
	void AttachAnimationProc(int i, int j);
};
	
#endif
