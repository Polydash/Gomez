#include <SDL/SDL_image.h>

#include "GfxResImage.h"
#include "../GameStd.h"

GfxResImage::GfxResImage(const std::string &resName):
m_resName(resName)
{
}

GfxResImage::~GfxResImage()
{
}

bool GfxResImage::VLoad()
{
	if(m_pSurface)
	{
		ERROR("GfxResource \"" << m_resName << "\" already loaded");
		return false;
	}
	
	if((m_pSurface = IMG_Load(m_resName.c_str())) == NULL)
	{
		ERROR("Failed to load \"" << m_resName << "\"");
		return false;
	}
	
	return true;
}


