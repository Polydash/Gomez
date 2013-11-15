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
	
	float 		 m_speed;
	unsigned int m_timeCount;
	bool  		 m_bIsDone;
	bool  		 m_bIsDropped;
	
	GfxImageSharedPtr m_pImage;
	shared_ptr<SmoothFollowProcess> m_pMoveProc;
	
public :

	FallingPieceProcess(TetrisGrid *pGrid, TetrisPiece *pPiece, float speed);
	~FallingPieceProcess(); 

	virtual void VUpdate(unsigned int elapsedTime);
	
protected :

	virtual bool VOnInit();
	virtual void VOnSuccess();
	virtual void VOnAbort();
	
private :

	//Gameplay methods
	bool Move(bool bMoveToRight);
	bool Lower();
	void Rotate();
	bool CheckCollision();
	
	//Ending methods
	void PlacePiece();
	void DropPiece();
	
	//Init methods
	void SetProc();
	void SetImage(TetrisPiece *pPiece);
	void RegisterEvents();
	void UnregisterEvents();
	
	//Input delegate
	void MainGameInputDelegate(EventSharedPtr pEvent);
};

#endif
