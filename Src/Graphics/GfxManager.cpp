#include "GfxManager.h"

GfxManager::GfxManager():
m_pScreen(NULL)
{
}

GfxManager::~GfxManager()
{
	Clear();
}

bool GfxManager::Init(SDL_Window* pScreen)
{		
	m_pScreen = pScreen;
	if(!m_pScreen)
		return false;
	
	return true;
}

void GfxManager::PreRender()
{
}

void GfxManager::Render()
{
}

void GfxManager::PostRender()
{
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
