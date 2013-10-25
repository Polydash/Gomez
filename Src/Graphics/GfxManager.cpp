#include "GfxManager.h"

GfxManager::GfxManager():
m_pScreen(NULL)
{
}

GfxManager::~GfxManager()
{
	Clear();
	
	if(m_pRenderer)
	{
		SDL_DestroyRenderer(m_pRenderer);
		m_pRenderer = NULL;
	}
}

bool GfxManager::Init(SDL_Window* pScreen)
{		
	m_pScreen = pScreen;
	if(!m_pScreen)
		return false;
	
	m_pRenderer = SDL_CreateRenderer(m_pScreen, -1, SDL_RENDERER_ACCELERATED);
	if(!m_pRenderer)
	{
		ERROR("Failed to create SDL_Renderer");
		return false;
	}
	
	return true;
}

void GfxManager::PreRender()
{
	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
	SDL_RenderClear(m_pRenderer);
}

void GfxManager::Render()
{
	GfxElementList::iterator i;
	for(i = m_gfxElements.begin(); i != m_gfxElements.end(); i++)
		(*i)->VRender(m_pRenderer);
}

void GfxManager::PostRender()
{
	SDL_RenderPresent(m_pRenderer);
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
	
	if(!pElement->VInit(m_pRenderer))
		return;
	
	GfxElementList::iterator i = m_gfxElements.begin();
	while(i != m_gfxElements.end() && (*i)->GetLayer() > layer)
		i++;
		
	m_gfxElements.insert(i, pElement);
}

void GfxManager::RemoveElement(GfxElement *pElement)
{
	GfxElementList::iterator i;
	for(i = m_gfxElements.begin(); i != m_gfxElements.end(); i++)
	{
		if((*i) == pElement)
		{
			delete (*i);
			m_gfxElements.erase(i);
			break;
		}
	}
}
