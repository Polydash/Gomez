#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include <string>

#include "BaseGameState.h"
#include "../Event/IEvent.h"

class GameStateManager
{
private:

	BaseGameState *m_pCurrentState;
	
public:

	GameStateManager();
	~GameStateManager();
	
	bool Init();
	void Update(unsigned int elapsedTime);
	
private :

	void StateChangeDelegate(EventSharedPtr pEvent);
	
	BaseGameState* CreateState(const eGameState gameState);
	void ChangeState(const eGameState gameState);
	void DestroyState(BaseGameState* &pState);
};

#endif
