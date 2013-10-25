#ifndef IMAGERESOURCE_H
#define IMAGERESOURCE_H

#include <SDL2/SDL.h>
#include <string>

#include "IResource.h"

class ImageResource : public IResource
{
	private :
		
		SDL_Surface *m_pSurface;
	
		std::string m_fileName;
	
	public :
	
		ImageResource(const std::string &fileName);
		virtual ~ImageResource();
		
		virtual bool VLoad();

		const SDL_Surface* GetSurface() const{ return m_pSurface; }
		const SDL_Texture* GetTexture(SDL_Renderer* pRenderer) const;
};

#endif
