#ifndef FONTRESOURCE_H
#define FONTRESOURCE_H

#include <SDL2/SDL_ttf.h>
#include <string>

#include "IResource.h"

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
