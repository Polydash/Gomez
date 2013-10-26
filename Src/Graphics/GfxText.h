#ifndef GFXTEXT_H
#define GFXTEXT_H

#include "GfxImage.h"

class GfxText : public GfxImage
{
private :

	std::string m_text;
	
public :

	GfxText(int layer, const std::string &fileName, const std::string &text);
	GfxText(int layer, const std::string &fileName, const std::string &text, const SDL_Rect &position);
	virtual ~GfxText();
	
	virtual bool VInit(SDL_Renderer *pRenderer);
};

#endif
