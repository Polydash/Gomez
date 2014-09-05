#ifndef IMAGERESOURCE_H
#define IMAGERESOURCE_H

/**
 * \file ImageResource.h 
 * \brief Resource allowing an image to be loaded
 */

#include <SDL2/SDL.h>
#include <string>

#include "IResource.h"

/**
 * \class ImageResource 
 * \brief Resource allowing an image to be loaded
 * 
 * Resource inheriting from the IResource interface. It allows images to
 * be loaded and stored in the ResourceManager.
 */
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
		SDL_Texture* CreateTexture(SDL_Renderer* pRenderer) const;
};

#endif
