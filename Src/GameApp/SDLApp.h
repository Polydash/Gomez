#ifndef SDLAPP_H
#define SDLAPP_H

#include <SDL/SDL.h>
#include <string>

class EventManager;
class GameStateManager;

//Game Application Global
class SDLApp;
extern SDLApp* g_pApp;

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
	EventManager* GetEventMgr() const;
	
	int GetScreenWidth()  const{ return m_width;  }
	int GetScreenHeight() const{ return m_height; }
	
private :

	SDLApp();
	~SDLApp();
	
	void LoadConfig();
};

#endif
