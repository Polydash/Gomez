#ifndef GFXRESOURCE_H
#define GFXRESOURCE_H

#include <SDL/SDL.h>
#include <string>

class GfxResource
{
	protected :
		
		SDL_Surface *m_pSurface;
	
	public :
	
		GfxResource();
		virtual ~GfxResource();
		
		virtual bool VLoad() = 0;

		SDL_Surface* GetRes() const{ return m_pSurface; }
};

#endif
