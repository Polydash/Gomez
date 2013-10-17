#include "GfxResource.h"

GfxResource::GfxResource():
m_pSurface(NULL)
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
