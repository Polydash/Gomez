#ifndef GFXRESOURCE_H
#define GFXRESOURCE_H

#include <SDL2/SDL.h>
#include <string>

#include "IResource.h"

class GfxResource : public IResource
{
	private :
		
		SDL_Surface *m_pSurface;
	
		std::string m_fileName;
	
	public :
	
		GfxResource(const std::string &fileName);
		virtual ~GfxResource();
		
		virtual bool VLoad();

		const SDL_Surface* GetSurface() const{ return m_pSurface; }
		const SDL_Texture* GetTexture(SDL_Renderer* pRenderer) const;
};

#endif
