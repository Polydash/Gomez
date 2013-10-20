#ifndef GFXRESOURCE_H
#define GFXRESOURCE_H

#include <SDL/SDL.h>
#include <string>

#include "IResource.h"

class GfxResource : public IResource
{
	private :
		
		std::string m_fileName;
		SDL_Surface *m_pSurface;
	
	public :
	
		GfxResource(const std::string &fileName);
		virtual ~GfxResource();
		
		virtual bool VLoad();

		const SDL_Surface* GetSurface() const{ return m_pSurface; }
};

#endif
