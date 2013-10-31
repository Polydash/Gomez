#ifndef TETRISBLOCK_H
#define TETRISBLOCK_H

#include "../Graphics/GfxImage.h"

enum ePieceType{ PT_IBLOCK,
				 PT_JBLOCK,
				 PT_TBLOCK,
				 PT_LBLOCK,
				 PT_ZBLOCK,
				 PT_OBLOCK,
				 PT_SBLOCK
			   };

class TetrisBlock
{
private :

	GfxImageSharedPtr m_pGfxBlock;
	
	float m_posX, m_posY;
	
public :

	TetrisBlock();
	TetrisBlock(ePieceType pieceType);
	~TetrisBlock();
	
	void SetPieceType(ePieceType pieceType);
	
	void SetPosition(float posX, float posY);
	void Translate(float deltaX, float deltaY);
	float GetPosX() const{ return m_posX; }
	float GetPosY() const{ return m_posY; }
	
	//Used to modify rotation/scale (not position) 
	GfxImageSharedPtr GetGfxBlock() const{ return m_pGfxBlock; }
	
private :

	void UpdateGfxPosition();
	void SetColor(ePieceType pieceType);
};

#endif
