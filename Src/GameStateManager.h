#ifndef _GAMESTATEMANAGER_H_
#define _GAMESTATEMANAGER_H_

#include <string>

#include "IGameState.h"

class GameStateManager
{
private:

	IGameState *m_pCurrentState;
	bool m_bIsPaused;
	
public:

	GameStateManager();
	~GameStateManager();
	
	bool Init();
	void Update(unsigned int elapsedTime);
	
	IGameState* CreateState(const eGameState gameState);
	void ChangeState(IGameState *pState);
	void DestroyState();
	
	void Pause();
};

#endif
