#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

/**
 * \file GameStateManager.h 
 * \brief Manager allowing Game State changes
 */

#include <SDL2/SDL.h>
#include <string>

#include "BaseGameState.h"
#include "../Event/IEvent.h"

/**
 * \class GameStateManager
 * \brief Manager allowing Game State changes
 * 
 * This manager handles GameState transitions. It also sends inputs to
 * the current GameState.
 */
class GameStateManager
{
private:

	BaseGameState *m_pCurrentState;
	
public:

	GameStateManager();
	~GameStateManager();
	
	bool Init();
	void OnInput(const SDL_Event &event);
	void Update(unsigned int elapsedTime);
	
private :

	void StateChangeDelegate(EventSharedPtr pEvent);
	
	BaseGameState* CreateState(const eGameState gameState);
	void ChangeState(const eGameState gameState);
	void DestroyState(BaseGameState* &pState);
};

#endif
