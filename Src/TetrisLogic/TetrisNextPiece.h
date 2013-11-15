#ifndef TETRISNEXTPIECE_H
#define TETRISNEXTPIECE_H

#include "../Graphics/GfxImage.h"
#include "../Graphics/GfxText.h"
#include "TetrisPiece.h"

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
