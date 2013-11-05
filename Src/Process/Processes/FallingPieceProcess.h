#ifndef FALLINGPIECEPROCESS_H
#define FALLINGPIECEPROCESS_H

#include "../Process.h"
#include "../../Event/IEvent.h"
#include "../../TetrisLogic/TetrisGrid.h"
#include "SmoothFollowProcess.h"

class FallingPieceProcess : public Process
{
private :
	
	TetrisGrid  *m_pGrid;
	TetrisPiece *m_pPiece;
	
	shared_ptr<SmoothFollowProcess> m_pMoveProc;
	
public :

	FallingPieceProcess(TetrisGrid *pGrid);
	~FallingPieceProcess(); 

	virtual bool VOnInit();
	virtual void VUpdate(unsigned int elapsedTime);
	
private :

	void SetPiece();
	void SetMoveProc();
	GfxImageSharedPtr SetImage(TetrisPiece *pPiece);
	void MainGameInputDelegate(EventSharedPtr pEvent);
	void RegisterEvents();
	void UnregisterEvents();
};

#endif
