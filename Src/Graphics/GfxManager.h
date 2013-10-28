#ifndef GFXMANAGER_H
#define GFXMANAGER_H

#include <list>

#include "GfxElement.h"

class GfxManager
{
private :

	typedef std::list<GfxElementSharedPtr> GfxElementList;
	
	GfxElementList m_gfxElements;

	SDL_Window 		*m_pScreen;
	SDL_Renderer 	*m_pRenderer;

public :

	GfxManager();
	~GfxManager();
	
	bool Init(SDL_Window* pScreen);
	
	void PreRender();
	void Render();
	void PostRender();
	
	void Clear();
	
	void AddElement(GfxElementSharedPtr pElement);
	void RemoveElement(GfxElementSharedPtr pElement);
};

#endif
