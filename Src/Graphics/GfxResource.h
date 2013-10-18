#ifndef GFXRESOURCE_H
#define GFXRESOURCE_H

#include <SDL/SDL.h>
#include <string>

class GfxResource
{
	protected :
		
		std::string m_resName;
		
		SDL_Surface *m_pSurface;
	
	public :
	
		GfxResource(const std::string &resName);
		virtual ~GfxResource();
		
		virtual bool VLoad() = 0;

		const SDL_Surface* GetRes() const{ return m_pSurface; }
		const std::string& GetName() const{ return m_resName; }
};

#endif
