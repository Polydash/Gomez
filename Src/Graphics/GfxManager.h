#ifndef GFXMANAGER_H
#define GFXMANAGER_H

/**
 * \file GfxManager.h 
 * \brief Manager allowing Graphic Elements display 
 */

#include <list>

#include "GfxElement.h"

/**
 * \class GfxManager
 * \brief Manager allowing Graphic Elements display
 * 
 * This manager allows GfxElements to be rendered on an SDL_Window with
 * the help of an SDL_Renderer. GfxElements are rendered according to
 * their layer value.
 */
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
