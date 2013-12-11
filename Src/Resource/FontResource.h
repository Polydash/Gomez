#ifndef FONTRESOURCE_H
#define FONTRESOURCE_H

/**
 * \file FontResource.h 
 * \brief Resource allowing a font to be loaded
 */

#include <SDL2/SDL_ttf.h>
#include <string>

#include "IResource.h"

/**
 * \class FontResource 
 * \brief Resource allowing a font to be loaded
 * 
 * Resource inheriting from the IResource interface. It allows fonts to
 * be loaded and stored in the ResourceManager.
 */
class FontResource : public IResource
{
	private :
		
		TTF_Font *m_pFont;
	
		std::string m_fileName;
	
	public :
	
		FontResource(const std::string &fileName);
		virtual ~FontResource();
		
		virtual bool VLoad();

		TTF_Font* GetFont() const{ return m_pFont; }
};

#endif
