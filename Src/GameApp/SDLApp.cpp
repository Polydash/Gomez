#include <tinyxml.h>

#include "../GameApp/SDLApp.h"
#include "../GameStd.h"
#include "../Event/EventManager.h"
#include "../Event/Events.h"
#include "../GameState/GameStateManager.h"
#include "../Resource/ResourceManager.h"
#include "../Graphics/GfxManager.h"

SDLApp* g_pApp = NULL;

SDLApp::SDLApp():
m_width(800),
m_height(600),
m_bitsPerPixel(32),
m_title("Tetris"),
m_imgPath("Data/Images"),
m_pScreen(NULL),
m_pGameStateMgr(NULL),
m_pGfxMgr(NULL)
{
}

SDLApp::~SDLApp()
{
	LOG("GameState Manager Destruction");
	SAFE_DELETE(m_pGameStateMgr);
	
	if(m_pGfxMgr)
	{
		LOG("Graphics Manager Destruction");
		SAFE_DELETE(m_pGfxMgr);
	}
	
	if(EventManager::Get())
	{
		LOG("Event Manager Destruction");
		EventManager::Destroy();
	}
	
	LOG("Resource Manager Destruction");
	ResourceManager::Destroy();
	
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
	LOG("SDL Init");
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) == -1)
	{
		ERROR("Failed to init SDL");
		return false;
	}
	
	LOG("Game Configuration");
	LoadConfig();
	
	LOG("SDL Configuration");
	// Forced conversion from const char* to char*
	std::string param = "SDL_VIDEO_CENTERED=center";
	SDL_putenv(const_cast<char*>(param.c_str()));
	
	m_pScreen = SDL_SetVideoMode(m_width, m_height, m_bitsPerPixel, SDL_HWSURFACE | SDL_DOUBLEBUF);
	if(!m_pScreen)
	{
		ERROR("Failed to create SDL Screen : " << SDL_GetError());
		return false;
	}
	
	SDL_WM_SetCaption("Tetris", NULL);
	SDL_ShowCursor(SDL_ENABLE);
	
	LOG("Resource Manager Init");
	ResourceManager::Create();
	
	LOG("Event Manager Init");
	EventManager::Create();
	if(!EventManager::Get())
	{
		ERROR("Failed to init Event Manager");
		return false;
	}
	
	LOG("Graphics Manager Init");
	m_pGfxMgr = new GfxManager;
	if(!m_pGfxMgr->Init(m_pScreen))
	{
		ERROR("Failed to init Graphics Manager");
		return false;
	}
	
	LOG("GameState Manager Init");
	m_pGameStateMgr = new GameStateManager;
	if(!m_pGameStateMgr->Init())
	{
		ERROR("Failed to init GameState Manager");
		return false;
	}
	
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
				
				if(event.active.state & SDL_APPINPUTFOCUS)
				{	
					if(!event.active.gain)
					{
						shared_ptr<Evt_FocusLost> pEvent(new Evt_FocusLost());
						EventManager::Get()->QueueEvent(pEvent);
					}
				}
			}
			
			if(!bIsMinimized)
			{
				switch(event.type)
				{
					case SDL_KEYDOWN :
					case SDL_KEYUP :
						//Queue GameInput Event
						break;
						
					default :
						break;
				}
			}
		}
		
		//Run game if not minimized
		if(!bIsMinimized)
		{
			EventManager::Get()->Update();
			m_pGameStateMgr->Update(elapsedTime);
			m_pGfxMgr->PreRender();
			m_pGfxMgr->PostRender();
		}
	}
}

GameStateManager* SDLApp::GetGameStateMgr() const
{
	return m_pGameStateMgr;
}

void SDLApp::LoadConfig()
{
	TiXmlDocument configDoc("Data/config.xml");
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
		
		pElem = pElem->NextSiblingElement();
		m_imgPath = pElem->Attribute("Images");
	}
}


