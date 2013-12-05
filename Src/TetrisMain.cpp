/**
 * \file TetrisMain.cpp 
 * \brief Entry point of the game
 */

#include "GameStd.h"
#include "GameApp/SDLApp.h"

/**
 * \fn main
 * \brief Entry point of the game
 */
int main()
{
	/// Reset log file
	remove("Data/log.txt");
	LOG("Program started"); 
	
	/// Create game application
	SDLApp::Create();
	
	/// Init and application loop
	if(g_pApp->Init())
		g_pApp->MainLoop();
	
	/// End program
	SDLApp::Destroy();	
	LOG("Program ended");
	
	return 0;
}
