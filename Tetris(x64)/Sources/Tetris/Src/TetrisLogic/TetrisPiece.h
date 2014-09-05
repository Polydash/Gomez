#ifndef TETRISPIECE_H
#define TETRISPIECE_H

/**
 * \file TetrisPiece.h 
 * \brief Tetris piece (logic)
 */

#include <string>

#include "TetrisGfxBlock.h"

/**
 * \class TetrisPiece
 * \brief Tetris piece (logic)
 * 
 * This class contains logic informations about a TetrisPiece.
 */
class TetrisPiece
{
private :

	int  ***m_positions;
	
	int m_currentRotation;
	int m_centerX, m_centerY;
	ePieceType m_pieceType;

public :

	static std::string GetPieceFile(ePieceType type); 

	TetrisPiece(ePieceType pieceType);
	~TetrisPiece();
	
	void InitPosition(int centerX, int centerY);
	
	void RotateRight();
	void RotateLeft();
	void Move(int x, int y);
	
	int GetCenterX() const{ return m_centerX; }
	int GetCenterY() const{ return m_centerY; } 
	ePieceType GetPieceType() const{ return m_pieceType; }
	
	int** GetPositions() const;
	
private :

	void CreatePiece(ePieceType pieceType);
	void AllocateArray();
	void DeallocateArray();
};

#endif
