#ifndef SDLAPP_H
#define SDLAPP_H

#include <SDL2/SDL.h>
#include <string>

//Game Application Global
class SDLApp;
extern SDLApp* g_pApp;

class GameStateManager;
class GfxManager;

class SDLApp
{
private :

	int m_width, m_height;
	std::string m_title, m_imgPath, m_fontPath;

	SDL_Window *m_pScreen;
	
	GameStateManager *m_pGameStateMgr;
	GfxManager *m_pGfxMgr;

public :
	
	static void Create();
	static void Destroy();
	
	bool Init();
	void MainLoop();
	
	GameStateManager* GetGameStateMgr() const;
	GfxManager* GetGfxMgr() const;
	
	int GetScreenWidth()  const{ return m_width;  }
	int GetScreenHeight() const{ return m_height; }
	std::string GetImgPath() const{ return m_imgPath; }
	std::string GetFontPath() const{ return m_fontPath; }
	
private :

	SDLApp();
	~SDLApp();
	
	void LoadConfig();
	bool SDLInit();
};

#endif
