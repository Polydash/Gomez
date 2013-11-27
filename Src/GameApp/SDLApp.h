#ifndef SDLAPP_H
#define SDLAPP_H

#include <SDL2/SDL.h>
#include <string>

extern int g_linesCleared;

//Game Application Global
class SDLApp;
extern SDLApp* g_pApp;

class GameStateManager;
class GfxManager;
class Server;

class SDLApp
{
private :

	int m_width, m_height;
	bool m_bIsDone;
	std::string m_title, m_imgPath, m_fontPath;

	SDL_Window *m_pScreen;
	SDL_Joystick *m_pJoystick;
	
	GameStateManager *m_pGameStateMgr;
	GfxManager *m_pGfxMgr;
	Server *m_pServer;

public :
	
	static void Create();
	static void Destroy();
	
	bool Init();
	void MainLoop();
	
	GameStateManager* GetGameStateMgr() const;
	GfxManager* GetGfxMgr() const;
	Server* GetServer() const;
	
	void RequestExit(){ m_bIsDone = true; }
	
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
