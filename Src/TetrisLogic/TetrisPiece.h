#ifndef TETRISPIECE_H
#define TETRISPIECE_H

#include "TetrisBlock.h"



class TetrisPiece
{
private :

	TetrisBlock m_blocks[4];
	float m_positions[4][3][2];
	int m_currentRotation;

public :

	TetrisPiece(ePieceType pieceType);
	~TetrisPiece();
	
	static const int s_pieceSize;
	
	void RotateRight();
	
	void SetPosition(float posX, float posY);
	void Translate(float deltaX, float deltaY);
	float GetPosX() const;
	float GetPosY() const;
	
private :

	void CreatePositions(ePieceType pieceType);
	void UpdateBlocks();
};

#endif
