#ifndef TETRISAPP_H
#define TETRISAPP_H

#include <SDL/SDL.h>
#include <string>

class TetrisApp
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

	TetrisApp();
	~TetrisApp();
	
	void LoadConfig();
};

#endif
