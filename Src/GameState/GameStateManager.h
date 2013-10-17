#ifndef GAMESTATEMANAGER_H_
#define GAMESTATEMANAGER_H_

#include <string>

#include "IGameState.h"
#include "../Event/IEvent.h"

class GameStateManager
{
private:

	IGameState *m_pCurrentState;
	
public:

	GameStateManager();
	~GameStateManager();
	
	bool Init();
	void Update(unsigned int elapsedTime);
	
	void StateChangeDelegate(EventSharedPtr pEvent);
	
private :
	
	IGameState* CreateState(const eGameState gameState);
	void ChangeState(IGameState *pState);
	void DestroyState();
};

#endif
