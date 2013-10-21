#include "GfxManager.h"

GfxManager::GfxManager():
m_pScreen(NULL),
m_pBlackSurface(NULL)
{
}

GfxManager::~GfxManager()
{
	Clear();
	SDL_FreeSurface(m_pBlackSurface);
	m_pBlackSurface = NULL;
}

bool GfxManager::Init(SDL_Surface* pScreen)
{		
	m_pScreen = pScreen;
	if(!m_pScreen)
		return false;
	
	int bpp = m_pScreen->format->BitsPerPixel;
	int w = m_pScreen->w;
	int h = m_pScreen->h;
	
	m_pBlackSurface = SDL_CreateRGBSurface(SDL_HWSURFACE, w, h, bpp, 0, 0, 0, 0);
	SDL_FillRect(m_pBlackSurface, NULL, SDL_MapRGB(m_pScreen->format, 0, 0, 0));
	
	return true;
}

void GfxManager::PreRender()
{
	SDL_Rect pos;
	pos.x = 0;
	pos.y = 0;
	
	SDL_BlitSurface(m_pBlackSurface, NULL, m_pScreen, &pos);
}

void GfxManager::Render()
{
}

void GfxManager::PostRender()
{
	SDL_Flip(m_pScreen);
}

void GfxManager::Clear()
{
	GfxElementList::iterator i;
	for(i = m_gfxElements.begin(); i != m_gfxElements.end(); i++)
	{
		delete (*i);
		(*i) = NULL;
	}
	
	m_gfxElements.clear();
}

void GfxManager::AddElement(GfxElement *pElement)
{
	int layer = pElement->GetLayer();
	
	GfxElementList::iterator i = m_gfxElements.begin();
	while(i != m_gfxElements.end() && (*i)->GetLayer() > layer)
		i++;
		
	m_gfxElements.insert(i, pElement);
}
