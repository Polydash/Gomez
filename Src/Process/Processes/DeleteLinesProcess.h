#ifndef DELETELINESPROCESS_H
#define DELETELINESPROCESS_H

#include "../Process.h"
#include "../../TetrisLogic/TetrisGrid.h"
#include <vector>

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
	
	void VUpdate(unsigned int elapsedTime);
	
protected :

	bool VOnInit();
	void VOnSuccess();

private :

	bool IsLineFull(int i) const;
	void AttachAnimationProc(int i, int j);
};
	
#endif
