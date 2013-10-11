#ifndef SDLAPP_H
#define SDLAPP_H

#include <SDL/SDL.h>
#include <string>

class SDLApp
{
private :

	int m_width, m_height, m_bitsPerPixel;
	std::string m_title;

	SDL_Surface *m_pScreen;

public :
	
	static void Create();
	static void Destroy();
	
	bool Init();
	void MainLoop();
	
private :

	SDLApp();
	~SDLApp();
	
	void LoadConfig();
};

#endif
