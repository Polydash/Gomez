#include "MenuState.h"
#include "../GameStd.h"
#include "../GameApp/SDLApp.h"
#include "../Graphics/GfxManager.h"
#include "../Event/Events/Evt_StateChange.h"
#include "../Event/EventManager.h"
#include "../Process/Processes/HorizontalScrollProcess.h"
#include "../Process/Processes/ScaleProcess.h"
#include "../Process/Processes/FadeProcess.h"
#include "../Resource/ResourceManager.h"

void MenuState::VOnUpdate(unsigned int elapsedTime)
{ 
	if(m_pFadeInProc && m_pFadeInProc->IsDone())
	{
		m_pFadeInProc.reset();
		
		g_pApp->GetGfxMgr()->AddElement(m_pTitle[0]);
		m_pScale.reset(new ScaleProcess(m_pTitle[0], 15, 1.0f, 0.01f, 0.0001f));
	
		ProcessSharedPtr pFlash;
		m_pFadeRect->VSetColor(255, 255, 255);
		pFlash.reset(new FadeProcess(m_pFadeRect, 255, 0, 0.25f));
		
		m_pScale->AttachChild(pFlash);
		AttachLogicProcess(m_pScale);
	}
	
	if(m_pScale && m_pScale->IsDone())
	{
		m_pScale.reset();
		
		g_pApp->GetGfxMgr()->AddElement(m_pOptions[0]);
		g_pApp->GetGfxMgr()->AddElement(m_pOptions[1]);
		
		m_pScrollingProc[0].reset(new HorizontalScrollProcess(0.05f, 5, "starsBG.png"));
		m_pScrollingProc[1].reset(new HorizontalScrollProcess(0.07f, 4, "starsFG.png"));
		m_pScrollingProc[2].reset(new HorizontalScrollProcess(0.1f, 3, "starsFG2.png"));
		
		AttachLogicProcess(m_pScrollingProc[0]);
		AttachLogicProcess(m_pScrollingProc[1]);
		AttachLogicProcess(m_pScrollingProc[2]);
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
	g_pApp->GetGfxMgr()->RemoveElement(m_pTitle[0]);
	g_pApp->GetGfxMgr()->RemoveElement(m_pTitle[1]);
	g_pApp->GetGfxMgr()->RemoveElement(m_pFadeRect);
	g_pApp->GetGfxMgr()->RemoveElement(m_pOptions[0]);
	g_pApp->GetGfxMgr()->RemoveElement(m_pOptions[1]);
	
	m_pScrollingProc[0]->Success();
	m_pScrollingProc[1]->Success();
	m_pScrollingProc[2]->Success();
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
