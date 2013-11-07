#ifndef DELETELINESPROCESS_H
#define DELETELINESPROCESS_H

#include "../Process.h"
#include "../../TetrisLogic/TetrisGrid.h"

class DeleteLinesProcess : public Process
{
private :

	TetrisGrid *m_pGrid;
	
public :

	DeleteLinesProcess(TetrisGrid *pGrid);
	~DeleteLinesProcess();
	
	void VUpdate(unsigned int elapsedTime){}
	
protected :

	bool VOnInit();
	void VOnSuccess();

private :

	bool IsLineFull(int i) const;
};
	
#endif
