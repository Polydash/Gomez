#ifndef TETRISGFXBLOCK_H
#define TETRISGFXBLOCK_H

/**
 * \file TetrisGfxBlock.h 
 * \brief Tetris block (graphic & logic)
 */

#include "../Graphics/GfxImage.h"

/// Enumeration defining every Tetris piece type
enum ePieceType{ PT_IBLOCK,
				 PT_JBLOCK,
				 PT_TBLOCK,
				 PT_LBLOCK,
				 PT_ZBLOCK,
				 PT_OBLOCK,
				 PT_SBLOCK,
				 PIECETYPE_NB
			   };

/**
 * \class TetrisGfxBlock 
 * \brief Tetris block (graphic & logic)
 * 
 * This class represent one of the four blocks contained in a Tetris 
 * piece. It is needed by TetrisGrid to render blocks contained in the
 * grid.
 */
class TetrisGfxBlock
{
private :

	GfxImageSharedPtr m_pGfxImage;
	
	ePieceType m_pieceType;
	
public :

	static const int s_pieceSize;
	static SDL_Color GetColor(ePieceType pieceType);

	TetrisGfxBlock(int layer, ePieceType pieceType);
	~TetrisGfxBlock();
	 
	ePieceType GetPieceType() const{ return m_pieceType; }
	GfxImageSharedPtr GetGfxImage() const{ return m_pGfxImage; }
	
private :

	void SetColor(ePieceType pieceType);
};

#endif
