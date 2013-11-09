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
	
	std::vector<int> m_linesToDelete;
	
public :

	DeleteLinesProcess(TetrisGrid *pGrid, float speed);
	~DeleteLinesProcess();
	
	void VUpdate(unsigned int elapsedTime);
	
protected :

	bool VOnInit();
	void VOnSuccess();

private :

	bool IsLineFull(int i) const;
};
	
#endif
