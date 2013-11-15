#include "MenuState.h"
#include "../GameStd.h"
#include "../GameApp/SDLApp.h"
#include "../Graphics/GfxManager.h"
#include "../Event/Events/Evt_StateChange.h"
#include "../Event/EventManager.h"
#include "../Process/Processes/HorizontalScrollProcess.h"
#include "../Process/Processes/ScaleProcess.h"
#include "../Process/Processes/FadeProcess.h"
#include "../Process/Processes/BlinkingProcess.h"
#include "../Resource/ResourceManager.h"

MenuState::MenuState():
m_bIsDone(false),
m_bHasInput(false),
m_option(0)
{
}

void MenuState::VOnInput(const SDL_Event &event)
{
	if(m_bHasInput)
	{
		if(event.type == SDL_KEYDOWN && !event.key.repeat)
		{
			switch(event.key.keysym.sym)
			{		
				case SDLK_DOWN :
					m_option = (m_option+1)%2;
					m_pBlink->Success();
					m_pBlink.reset(new BlinkingProcess(m_pOptions[m_option], 0.05f, 192, 0.01f));
					AttachLogicProcess(m_pBlink);
					break;
					
				case SDLK_UP :
					m_option = (m_option-1);
					if(m_option < 0) m_option = 1;
					m_pBlink->Success();
					m_pBlink.reset(new BlinkingProcess(m_pOptions[m_option], 0.05f, 192, 0.01f));
					AttachLogicProcess(m_pBlink);
					break;
				
				case SDLK_RETURN :
					m_bHasInput = false;
					m_bIsDone = true;
					
					if(m_pFlash)
						m_pFlash->Abort();
						
					m_pFadeRect->VSetColor(0, 0, 0);
					m_pFadeOutProc.reset(new FadeProcess(m_pFadeRect, 0, 255, 0.4f));
					AttachLogicProcess(m_pFadeOutProc);
					break;
				
				default :
					break;
			}
		}
	
	}
}

void MenuState::VOnUpdate(unsigned int elapsedTime)
{ 
	if(m_pFadeInProc && m_pFadeInProc->IsDone())
	{
		m_pFadeInProc.reset();
		
		g_pApp->GetGfxMgr()->AddElement(m_pTitle[0]);
		m_pScale.reset(new ScaleProcess(m_pTitle[0], 15, 1.0f, 0.01f, 0.0001f));
	
		m_pFadeRect->VSetColor(255, 255, 255);
		m_pFlash.reset(new FadeProcess(m_pFadeRect, 255, 0, 0.25f));
		
		m_pScale->AttachChild(m_pFlash);
		AttachLogicProcess(m_pScale);
	}
	
	if(m_pScale && m_pScale->IsDone())
	{
		m_pScale.reset();
		
		m_pBlink.reset(new BlinkingProcess(m_pOptions[m_option], 0.05f, 192, 0.01f));
		AttachLogicProcess(m_pBlink);
		
		g_pApp->GetGfxMgr()->AddElement(m_pOptions[0]);
		g_pApp->GetGfxMgr()->AddElement(m_pOptions[1]);
		
		m_pScrollingProc[0].reset(new HorizontalScrollProcess(0.05f, 5, "starsBG.png"));
		m_pScrollingProc[1].reset(new HorizontalScrollProcess(0.07f, 4, "starsFG.png"));
		m_pScrollingProc[2].reset(new HorizontalScrollProcess(0.1f, 3, "starsFG2.png"));
		
		AttachLogicProcess(m_pScrollingProc[0]);
		AttachLogicProcess(m_pScrollingProc[1]);
		AttachLogicProcess(m_pScrollingProc[2]);
		
		m_bHasInput = true;
	}
	
	if(m_bIsDone && m_pFadeOutProc && m_pFadeOutProc->IsDone())
	{
		m_pFadeOutProc.reset();
		if(m_option == 0)
		{
			shared_ptr<Evt_StateChange> pEvent(new Evt_StateChange(GS_MAINGAME));
			EventManager::Get()->QueueEvent(pEvent);
		}
		else
			g_pApp->RequestExit();
	}
}

void MenuState::VOnEnter()
{
	INFO("Entering MENU state");
	LOG("Entering MENU state");
	ResourceManager::Get()->Clear();
	
	SetDisplay();
	SetProc();
}

void MenuState::VOnLeave()
{
	m_pScrollingProc[0]->Success();
	m_pScrollingProc[1]->Success();
	m_pScrollingProc[2]->Success();
	m_pBlink->Success();
	
	g_pApp->GetGfxMgr()->RemoveElement(m_pTitle[0]);
	g_pApp->GetGfxMgr()->RemoveElement(m_pTitle[1]);
	g_pApp->GetGfxMgr()->RemoveElement(m_pOptions[0]);
	g_pApp->GetGfxMgr()->RemoveElement(m_pOptions[1]);
	g_pApp->GetGfxMgr()->RemoveElement(m_pFadeRect);
}

void MenuState::SetDisplay()
{
	float posX = g_pApp->GetScreenWidth()/2;
	float posY = g_pApp->GetScreenHeight()/4;
	m_pTitle[0].reset(new GfxImage(1, "tetris.png"));
	m_pTitle[0]->SetPosition(posX, posY);
	m_pTitle[1].reset(new GfxImage(2, "tetorisu.png"));
	m_pTitle[1]->SetPosition(posX, posY);
	
	m_pFadeRect.reset(new GfxRect(0));
	m_pFadeRect->SetDimensions(g_pApp->GetScreenWidth(), g_pApp->GetScreenHeight());
	m_pFadeRect->SetPosition(g_pApp->GetScreenWidth()/2, g_pApp->GetScreenHeight()/2);
	m_pFadeRect->VSetColor(0, 0, 0);
	
	m_pOptions[0].reset(new GfxText(1, "operator.ttf", "Play Game"));
	m_pOptions[1].reset(new GfxText(1, "operator.ttf", "Exit"));
	m_pOptions[0]->SetScale(0.45f);
	m_pOptions[1]->SetScale(0.45f);
	posY = g_pApp->GetScreenHeight()/8*5;
	m_pOptions[0]->SetPosition(posX, posY);
	posY = g_pApp->GetScreenHeight()/8*6;
	m_pOptions[1]->SetPosition(posX, posY);
	
	g_pApp->GetGfxMgr()->AddElement(m_pTitle[1]);
	g_pApp->GetGfxMgr()->AddElement(m_pFadeRect);
}

void MenuState::SetProc()
{
	m_pFadeInProc.reset(new FadeProcess(m_pFadeRect, 255, 0, 0.2f));
	AttachLogicProcess(m_pFadeInProc);
}
