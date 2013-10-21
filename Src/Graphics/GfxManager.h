#ifndef GFXMANAGER_H
#define GFXMANAGER_H

#include <list>

#include "GfxElement.h"

class GfxManager
{
private :

	typedef std::list<GfxElement*> GfxElementList;
	
	GfxElementList m_gfxElements;

	SDL_Surface *m_pScreen;
	SDL_Surface *m_pBlackSurface;

public :

	GfxManager();
	~GfxManager();
	
	bool Init(SDL_Surface* pScreen);
	
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
