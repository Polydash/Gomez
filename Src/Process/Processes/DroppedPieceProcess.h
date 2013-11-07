#ifndef DROPPEDPIECEPROCESS_H
#define DROPPEDPIECEPROCESS_H

#include "../Process.h"
#include "../../TetrisLogic/TetrisGrid.h"

class DroppedPieceProcess : public Process
{
	private :
	
		TetrisGrid  *m_pGrid;
		TetrisPiece *m_pPiece;
		
		GfxImageSharedPtr m_pImage;
		
		float m_accel;
		float m_speed;
		float m_maxSpeed;
		
	public :
	
		DroppedPieceProcess(TetrisGrid *pGrid, TetrisPiece *pPiece, GfxImageSharedPtr pImage);
		~DroppedPieceProcess();
		
		void SetVelocity(float accel, float maxSpeed);
		
		void VUpdate(unsigned int elapsedTime);
	
	protected :
	
		virtual bool VOnInit();
		virtual void VOnSuccess();
	
	private :
	
		bool Lower();
		bool CheckCollision();
		void PlacePiece();
};

#endif
