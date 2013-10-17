#include "GameStd.h"
#include "GameApp/SDLApp.h"

int main()
{
	//Reset log file
	remove("log.txt");
	LOG("Program started"); 
	
	SDLApp::Create();
	
	if(g_pApp->Init())
		g_pApp->MainLoop();
				
	SDLApp::Destroy();	
	
	LOG("Program ended");
	
	return 0;
}
