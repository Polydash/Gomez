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
	
	float m_speed;
	bool  m_bIsDone;
	bool  m_bIsDropped;
	
	GfxImageSharedPtr m_pImage;
	shared_ptr<SmoothFollowProcess> m_pMoveProc;
	
public :

	FallingPieceProcess(TetrisGrid *pGrid, float speed);
	~FallingPieceProcess(); 

	virtual void VUpdate(unsigned int elapsedTime);
	
protected :

	virtual bool VOnInit();
	
private :

	//Gameplay methods
	void Move(bool bMoveToRight);
	bool Lower();
	void Rotate();
	bool CheckCollision();
	
	//Ending methods
	void PlacePiece();
	void DropPiece();
	
	//Init methods
	void SetPiece();
	void SetMoveProc();
	void SetImage(TetrisPiece *pPiece);
	void RegisterEvents();
	void UnregisterEvents();
	
	//Input delegate
	void MainGameInputDelegate(EventSharedPtr pEvent);
};

#endif
