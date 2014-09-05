/**
 * \file TetrisAIMain.cpp 
 * \brief Entry point of the AI
 */

#include "AI.h"
#include "../../Tetris/Src/GameStd.h"
#include "../../Tetris/Src/Network/Client.h"
#include "../../Tetris/Src/Event/Events/Evt_MainGameInput.h"
#include "../../Tetris/Src/Event/EventManager.h"

/**
 * \fn main
 * \brief Entry point of the AI
 */
int main(int argc, char** argv)
{
	//Init
	EventManager::Create();
	if(!EventManager::Get())
	{
		ERROR("Failed to create EventManager");
		return 1;
	}
	
	Client *pClient = new Client();
	if(!pClient->Init())
	{
		ERROR("Failed to init client");
		SAFE_DELETE(pClient);
		EventManager::Destroy();
		return 1;
	}
	
	AI *pAI = new AI(pClient);
	if(!pAI->Init())
	{
		ERROR("Failed to init AI");
		SAFE_DELETE(pAI);
		SAFE_DELETE(pClient);
		EventManager::Destroy();
		return 1;
	}
	
	//Main loop
	pClient->Connect("127.0.0.1", 4000);
	while(pClient->IsConnected())
	{
		pClient->Select();
		EventManager::Get()->Update();
	}
	
	//Shutdown
	SAFE_DELETE(pAI);
	SAFE_DELETE(pClient);
	EventManager::Destroy();
	
	return 0;
}
