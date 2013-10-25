#ifndef GFXMANAGER_H
#define GFXMANAGER_H

#include <list>

#include "GfxElement.h"

class GfxManager
{
private :

	typedef std::list<GfxElement*> GfxElementList;
	
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
	
	void AddElement(GfxElement* pElement);
	void RemoveElement(GfxElement* pElement);
	
private :
	
	void AddElementDelegate(/*Evt_AddGfxElement*/);
	void RemoveElementDelegate(/*Evt_RemoveGfxElement*/);
};

#endif
