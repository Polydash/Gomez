#include <tinyxml.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>

#include "../GameApp/SDLApp.h"
#include "../GameStd.h"
#include "../Event/EventManager.h"
#include "../Event/Events/Evt_LostFocus.h"
#include "../GameState/GameStateManager.h"
#include "../Resource/ResourceManager.h"
#include "../Graphics/GfxManager.h"

SDLApp* g_pApp = NULL;

SDLApp::SDLApp():
m_width(800),
m_height(600),
m_title("Tetris"),
m_imgPath("Data/Images"),
m_fontPath("Data/Fonts"),
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
	
	SDL_DestroyWindow(m_pScreen);
	
	TTF_Quit();
	IMG_Quit();
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
	srand(time(NULL));
	
	LOG("Game Configuration");
	LoadConfig();
	
	if(!SDLInit())
		return false;
	
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
				
			if(event.type == SDL_WINDOWEVENT)
			{
				switch(event.window.event)
				{
					case SDL_WINDOWEVENT_MINIMIZED :
						bIsMinimized = true;
						break;
						
					case SDL_WINDOWEVENT_RESTORED :
						bIsMinimized = false;
						break;
						
					case SDL_WINDOWEVENT_FOCUS_LOST :
						shared_ptr<Evt_LostFocus> pEvent(new Evt_LostFocus());
						EventManager::Get()->QueueEvent(pEvent);
						break;
				}
			}
			
			if(!bIsMinimized)
			{
				switch(event.type)
				{
					case SDL_KEYDOWN :
					case SDL_KEYUP :
						m_pGameStateMgr->OnInput(event);
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
			m_pGfxMgr->Render();
			m_pGfxMgr->PostRender();
		}
	}
}

GameStateManager* SDLApp::GetGameStateMgr() const
{
	return m_pGameStateMgr;
}

GfxManager* SDLApp::GetGfxMgr() const
{
	return m_pGfxMgr;
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
		m_title = pElem->Attribute("Title");
		
		pElem = pElem->NextSiblingElement();
		m_imgPath = pElem->Attribute("Images");
		m_fontPath = pElem->Attribute("Fonts");
	}
}

bool SDLApp::SDLInit()
{
	LOG("SDL Init");
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) == -1)
	{
		ERROR("Failed to init SDL");
		return false;
	}
	
	LOG("SDL Configuration");
	m_pScreen = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, SDL_WINDOW_SHOWN);
	if(!m_pScreen)
	{
		ERROR("Failed to create SDL Screen : " << SDL_GetError());
		return false;
	}
	
	SDL_ShowCursor(SDL_DISABLE);
	//~ if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	//~ {
		//~ ERROR("Failed to enable linear texture filtering");
		//~ return false;
	//~ }
		//~ 
	LOG("SDL_image Init");
	int flags = IMG_INIT_PNG;
	if(!(IMG_Init(flags) & flags))
	{
		ERROR("Failed to init SDL_image : " << IMG_GetError());
		return false;
	}
	
	if(TTF_Init() == -1)
	{
		ERROR("Failed to init SDL_ttf : " << TTF_GetError());
		return false;
	}
	
	return true;
}
