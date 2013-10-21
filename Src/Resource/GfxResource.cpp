#include <SDL/SDL_image.h>

#include "GfxResource.h"
#include "../GameStd.h"

GfxResource::GfxResource(const std::string &fileName, bool bHasTransparency):
m_pSurface(NULL),
m_fileName(fileName),
m_bHasTransparency(bHasTransparency)
{
}

GfxResource::~GfxResource()
{
	if(m_pSurface)
	{
		SDL_FreeSurface(m_pSurface);
		m_pSurface = NULL;
	}
}

bool GfxResource::VLoad()
{
	if(m_pSurface)
	{
		ERROR("GfxResource \"" << m_fileName << "\" already loaded");
		return false;
	}
	
	if((m_pSurface = IMG_Load(m_fileName.c_str())) == NULL)
	{
		ERROR("Failed to load \"" << m_fileName << "\"");
		return false;
	}
	
	if(m_bHasTransparency)
	{
		SDL_Surface* temp = m_pSurface;
		m_pSurface = SDL_DisplayFormatAlpha(temp);
		SDL_FreeSurface(temp);
	}
	
	return true;
}
