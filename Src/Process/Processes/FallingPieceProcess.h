#ifndef FALLINGPIECEPROCESS_H
#define FALLINGPIECEPROCESS_H

#include "../Process.h"
#include "../../Event/IEvent.h"
#include "../../TetrisLogic/TetrisGrid.h"

class FallingPieceProcess : public Process
{
private :
	
	TetrisGrid  *m_pGrid;
	TetrisPiece *m_pPiece;
	
public :

	FallingPieceProcess(TetrisGrid *pGrid);
	~FallingPieceProcess(); 

	virtual bool VOnInit();
	virtual void VUpdate(unsigned int elapsedTime);
	
private :

	void MainGameInputDelegate(EventSharedPtr pEvent);
	void RegisterEvents();
	void UnregisterEvents();
};

#endif
