#include <tinyxml.h>

#include "../GameApp/SDLApp.h"
#include "../GameStd.h"

SDLApp* g_pApp = NULL;

SDLApp::SDLApp():
m_width(800),
m_height(600),
m_bitsPerPixel(32),
m_title("Tetris"),
m_pScreen(NULL),
m_pGameStateMgr(NULL),
m_pEventMgr(NULL)
{
}

SDLApp::~SDLApp()
{
	SAFE_DELETE(m_pGameStateMgr);
	
	if(m_pEventMgr)
	{
		EventManager::Destroy();
		m_pEventMgr = NULL;
	}
	
	SDL_Quit();
	LOG("SDL Quit");
}

void SDLApp::Create()
{
	if(g_pApp)
		ERROR("SDLApp already created");
	else
		g_pApp = new SDLApp;
}

void SDLApp::Destroy()
{
	SAFE_DELETE(g_pApp);
}

bool SDLApp::Init()
{
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) == -1)
	{
		ERROR("Failed to init SDL");
		return false;
	}
	
	LOG("SDL Init");
	
	LoadConfig();
	m_pScreen = SDL_SetVideoMode(m_width, m_height, m_bitsPerPixel, SDL_HWSURFACE | SDL_DOUBLEBUF);
	if(!m_pScreen)
	{
		ERROR("Failed to create SDL Screen : " << SDL_GetError());
		return false;
	}
	
	SDL_WM_SetCaption("Tetris", NULL);
	SDL_ShowCursor(SDL_ENABLE);
	
	LOG("SDL Configuration");
	
	m_pGameStateMgr = new GameStateManager;
	if(!m_pGameStateMgr->Init())
		return false;
	
	m_pEventMgr = EventManager::Create();
	if(!m_pEventMgr)
		return false;
	
	return true;
}

void SDLApp::MainLoop()
{
	SDL_Event event;
	unsigned int startTime, elapsedTime, FPSTime;
	bool bIsDone = false;
	bool bIsMinimized = false;
	
	FPSTime = 1000 / 60;
	startTime = SDL_GetTicks();
	
	while(!bIsDone)
	{		
		//60 FPS Limit	
		elapsedTime = SDL_GetTicks() - startTime;	
		if(elapsedTime < FPSTime)
		{
			SDL_Delay(FPSTime - elapsedTime);
			elapsedTime = SDL_GetTicks() - startTime;
		}
		
		startTime = SDL_GetTicks();
		
		//Input Loop
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
				bIsDone = true;
				
			if(event.type == SDL_ACTIVEEVENT)
			{
				if(event.active.state & SDL_APPACTIVE)
					bIsMinimized = !event.active.gain;
			}
			
			if(!bIsMinimized)
			{
				switch(event.type)
				{
					case SDL_KEYDOWN :
					case SDL_KEYUP :
						//Send input to GameStateManager
						break;
						
					default :
						break;
				}
			}
		}
		
		//Run game if not minimized
		if(!bIsMinimized)
		{
			m_pGameStateMgr->Update(elapsedTime);
		}
	}
}

GameStateManager* SDLApp::GetGameStateMgr() const
{
	return m_pGameStateMgr;
}

void SDLApp::LoadConfig()
{
	TiXmlDocument configDoc("config.xml");
	if(!configDoc.LoadFile())
	{
		LOG("Failed to load config.xml, configuration set to default");
		return;
	}
	
	TiXmlHandle hdl(&configDoc);
	TiXmlElement *pElem = hdl.FirstChildElement().FirstChildElement().Element();
	if(!pElem)
		LOG("Error while parsing config.xml, configuration set to default");
	else
	{
		pElem->QueryIntAttribute("Width", &m_width);
		pElem->QueryIntAttribute("Height", &m_height);
		pElem->QueryIntAttribute("BPP", &m_bitsPerPixel);
		m_title = pElem->Attribute("Title");
	}
}


