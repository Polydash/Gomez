#ifndef DROPPEDPIECEPROCESS_H
#define DROPPEDPIECEPROCESS_H

/**
 * \file DroppedPieceProcess.h 
 * \brief Process allowing a piece to fall on the grid with animation
 */

#include "../Process.h"
#include "../../TetrisLogic/TetrisGrid.h"

/**
 * \class DroppedPieceProcess 
 * \brief Process allowing a piece to fall on the grid with animation
 * 
 * This Process is attached as the "Drop Piece" game input is pressed.
 * It makes the piece fall on the grid with a "gravity" effect. Then,
 * a DeleteLinesProcess is attached to check grid for lines to delete.
 */
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
		
		virtual void VUpdate(unsigned int elapsedTime);
	
	protected :
	
		virtual bool VOnInit();
		virtual void VOnSuccess();
		virtual void VOnAbort();
	
	private :
	
		bool Lower();
		bool CheckCollision();
		void PlacePiece();
};

#endif
