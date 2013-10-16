#ifndef SDLAPP_H
#define SDLAPP_H

#include <SDL/SDL.h>
#include <string>

#include "GameStateManager.h"
#include "EventManager.h"

class SDLApp
{
private :

	int m_width, m_height, m_bitsPerPixel;
	std::string m_title;

	SDL_Surface *m_pScreen;
	
	GameStateManager *m_pGameStateMgr;
	EventManager *m_pEventMgr;

public :
	
	static void Create();
	static void Destroy();
	
	bool Init();
	void MainLoop();
	
	GameStateManager* GetGameStateMgr() const;
	
private :

	SDLApp();
	~SDLApp();
	
	void LoadConfig();
};

#endif
