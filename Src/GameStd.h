#ifndef GAMESTD_H
#define GAMESTD_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>

//Game application singleton
class SDLApp;
extern SDLApp* g_pApp;

//Deallocation
#define SAFE_DELETE(ptr) do{ if(ptr){delete ptr; ptr = NULL;} }while(0)
#define SAFE_DELETE_ARRAY(ptr) do{ if(ptr){delete[] ptr; ptr = NULL;} }while(0)

//Error System
#ifdef DEBUG

	//Error macro
	#define ERROR(str) do{\
					std::cerr << "[" << __FILE__ << "] " << __LINE__ << " : " <<  str << std::endl;\
					}while(0)

	//Log macro
	//A very specific name is chosen for the local
	//variable, to avoid any name collision
	#define LOG(str) do{\
					std::ofstream logFileMacroVar;\
					logFileMacroVar.open("log.txt", std::ios::app);\
					logFileMacroVar << "[" << __FILE__ << "] " << __LINE__ << " : " << str << std::endl;\
					logFileMacroVar.close();\
					}while(0)
					
#else

	//No ouput in release mode
	#define ERROR(str) do{}while(0)
	#define LOG(str) do{}while(0)

#endif

#endif
