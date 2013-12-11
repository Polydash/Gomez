#ifndef TETRISNEXTPIECE_H
#define TETRISNEXTPIECE_H

/**
 * \file TetrisNextPiece.h 
 * \brief Graphic element showing next piece
 */

#include "../Graphics/GfxImage.h"
#include "../Graphics/GfxText.h"
#include "TetrisPiece.h"

/**
 * \class TetrisNextPiece 
 * \brief Graphic element showing next piece
 * 
 * This class only has a graphic purpose. It allows the next piece to be
 * displayed.
 */
class TetrisNextPiece
{
private :
	
	int m_width, m_height;
	int m_posX, m_posY;
	
	GfxTextSharedPtr m_pTitle;
	GfxImageSharedPtr m_pImage;
	
public :

	TetrisNextPiece(int width, int height, int posX, int posY);
	~TetrisNextPiece();
	
	void UpdateNextPiece(ePieceType type);
};

#endif
