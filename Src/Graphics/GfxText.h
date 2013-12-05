#ifndef GFXTEXT_H
#define GFXTEXT_H

/**
 * \file GfxText.h 
 * \brief Graphic Element representing a Text 
 */

#include "GfxImage.h"

class GfxText;

typedef shared_ptr<GfxText> GfxTextSharedPtr;

class GfxText : public GfxImage
{
private :

	std::string m_text;
	
public :

	GfxText(int layer, const std::string &fileName, const std::string &text);
	GfxText(int layer, const std::string &fileName, const std::string &text, float posX, float posY);
	virtual ~GfxText();
	
	virtual bool VInit(SDL_Renderer *pRenderer);
};

#endif
