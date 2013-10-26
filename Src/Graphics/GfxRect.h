#ifndef GFXRECT_H
#define GFXRECT_H

#include "GfxElement.h"

class GfxRect : public GfxElement
{
	public :
	
		GfxRect(int layer);
		GfxRect(int layer, const SDL_Rect &dimension);
		~GfxRect();
	
		virtual bool VInit(SDL_Renderer *pRenderer);
		virtual void VRender(SDL_Renderer* pRenderer);
		virtual bool VIsVisible() const;
		
		void SetDimension(int x, int y, int w, int h);
		void SetDimension(const SDL_Rect &dimension);
};

#endif
