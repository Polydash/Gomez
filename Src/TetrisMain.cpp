#include "TetrisStd.h"
#include "TetrisApp.h"

int main()
{
	//Reset log file
	remove("log.txt");
	LOG("Program started"); 
	
	TetrisApp::Create();
	
	if(g_pApp->Init())
		g_pApp->MainLoop();
		
	TetrisApp::Destroy();	
	
	LOG("Program ended");
	
	return 0;
}
