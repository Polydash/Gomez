#ifndef SDLAPP_H
#define SDLAPP_H

/**
 * \file SDLApp.h 
 * \brief SDL-based Game Application
 */

#include <SDL2/SDL.h>
#include <string>

//Game Application Global
class SDLApp;
extern SDLApp* g_pApp;

class GameStateManager;
class GfxManager;
class Server;

/**
 * \class SDLApp
 * \brief SDL-based Game Application
 * 
 * SDLApp represents the game application. It manages every part of the
 * engine and SDL initialization and shutdown.
 * 
 * It also takes informations from a configuration file "config.xml"
 * thanks to the "TinyXML" library.
 */
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
