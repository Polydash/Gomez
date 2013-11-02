#ifndef TETRISGFXBLOCK_H
#define TETRISGFXBLOCK_H

#include "../Graphics/GfxImage.h"

enum ePieceType{ PT_IBLOCK,
				 PT_JBLOCK,
				 PT_TBLOCK,
				 PT_LBLOCK,
				 PT_ZBLOCK,
				 PT_OBLOCK,
				 PT_SBLOCK
			   };

class TetrisGfxBlock
{
private :

	GfxImageSharedPtr m_pGfxImage;
	
	ePieceType m_pieceType;
	
public :

	static const int s_pieceSize;

	TetrisGfxBlock(int layer, ePieceType pieceType);
	~TetrisGfxBlock();
	 
	ePieceType GetPieceType() const{ return m_pieceType; }
	GfxImageSharedPtr GetGfxImage() const{ return m_pGfxImage; }
	
private :

	void SetColor(ePieceType pieceType);
};

#endif
