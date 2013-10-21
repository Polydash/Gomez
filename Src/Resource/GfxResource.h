#ifndef GFXRESOURCE_H
#define GFXRESOURCE_H

#include <SDL/SDL.h>
#include <string>

#include "IResource.h"

class GfxResource : public IResource
{
	private :
		
		SDL_Surface *m_pSurface;
	
		std::string m_fileName;
		bool m_bHasTransparency;
	
	public :
	
		GfxResource(const std::string &fileName, bool bHasTransparency = false);
		virtual ~GfxResource();
		
		virtual bool VLoad();

		const SDL_Surface* GetSurface() const{ return m_pSurface; }
};

#endif
