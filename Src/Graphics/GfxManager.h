#ifndef GFXMANAGER_H
#define GFXMANAGER_H

#include <list>

#include "GfxElement.h"

class GfxManager
{
private :

	typedef std::list<GfxElement*> GfxElementList;
	
	GfxElementList m_gfxElements;

	SDL_Window *m_pScreen;

public :

	GfxManager();
	~GfxManager();
	
	bool Init(SDL_Window* pScreen);
	
	void PreRender();
	void Render();
	void PostRender();
	
	void Clear();
	
private :
	
	void AddElement(GfxElement* pElement);
	void RemoveElement(GfxElement* pElement);
	
	void AddElementDelegate(/*Evt_AddGfxElement*/);
	void RemoveElementDelegate(/*Evt_RemoveGfxElement*/);
};

#endif
