#ifndef GAMESTD_H
#define GAMESTD_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>

/**
 * SAFE_DELETE* macros
 * 
 * Macros allowing a safe memory deallocation
 */
#define SAFE_DELETE(ptr) do{ if(ptr){delete ptr; ptr = NULL;} }while(0)
#define SAFE_DELETE_ARRAY(ptr) do{ if(ptr){delete[] ptr; ptr = NULL;} }while(0)

/// Macros only defined in Debug Mode
#ifdef DEBUG

	/**
	 * ERROR macro
	 * 
	 * Useful macro to point an error out
	 */
	#define ERROR(str) do{\
					std::cerr << "ERROR [" << __FILE__ << "] " << __LINE__ << " : " <<  str << std::endl;\
					}while(0)

	/**
	 * INFO macro
	 * 
	 * Useful macro to show messages while debugging
	 */
	#define INFO(str) do{\
					std::cerr << "[" << __FILE__ << "] " << __LINE__ << " : " <<  str << std::endl;\
					}while(0)

	/**
	 * LOG macro
	 * 
	 * A very specific name is chosen for the local
	 * variable, to avoid any name collision
	 */
	#define LOG(str) do{\
					std::ofstream logFileMacroVar;\
					logFileMacroVar.open("Data/log.txt", std::ios::app);\
					logFileMacroVar << "[" << __FILE__ << "] " << __LINE__ << " : " << str << std::endl;\
					logFileMacroVar.close();\
					}while(0)
					
#else

	/// No output in release mode
	#define ERROR(str) do{}while(0)
	#define INFO(str) do{]}while(0)
	#define LOG(str) do{}while(0)

#endif

#endif
