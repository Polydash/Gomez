		Gomez Project


===============
	SDLApp

Manages application layer : 60 FPS, SDL, Window events
Holds a GameStateManager : m_pGameStateMgr
===============

MainLoop()
{
	while(Game_Is_Running)
	{
		Regulate_Frame_Rate;
		
		while(There_Are_Inputs_To_Handle)
		{
			if(Window_Event)
				Handle_Window_Event;
			
			if(Keyboard_Event)
				m_pGameStateMgr->OnInput(Keyboard_Event);
		}
		
		if(Game_Not_Minimized)
			m_pGameStateMgr->Update;
	}
}

===============
	GameStateManager
	
Manages game state changes : Intro, Menu, etc.
Send input to IGameState
Holds an IGameState : m_pCurState
===============

OnInput(Keyboard_Event)
{
	m_pCurState->OnInput(Keyboard_Event);
}

Update()
{
	m_pCurState->Update;
}

===============
	IGameState
	
Manages game state logic : OnInput, Update
Manages game state rendering : Render
Holds an ActorManager
Holds a ScreenElementManager
===============

OnInput(Keyboard_Event)
{
	if(!ScreenElementManager->OnInput)	//If the GUI system didn't "swallow" the input, send it to the actors
		ActorManager->OnInput
}

Update()
{
	if(Game_Logic_Is_Not_Paused)
		ActorManager->Update
		
	ScreenElementManager->Update
}

Render()
{
	ScreenElementManager->Render
}
