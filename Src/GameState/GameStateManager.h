#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include <string>

#include "IGameState.h"
#include "../Event/IEvent.h"

class GameStateManager
{
private:

	IGameState *m_pCurrentState;
	IGameState *m_pPausedState;
	
public:

	GameStateManager();
	~GameStateManager();
	
	bool Init();
	void Update(unsigned int elapsedTime);
	
	void StateChangeDelegate(EventSharedPtr pEvent);
	
private :
	
	IGameState* CreateState(const eGameState gameState);
	void ChangeState(const eGameState gameState);
	void DestroyState(IGameState* &pState);
};

#endif
