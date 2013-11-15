#include "IntroState.h"
#include "../GameApp/SDLApp.h"
#include "../GameStd.h"
#include "../Event/EventManager.h"
#include "../Event/Events/Evt_StateChange.h"
#include "../Resource/ResourceManager.h"
#include "../Graphics/GfxManager.h"
#include "../Process/Processes/FadeProcess.h"
#include "../Process/Processes/DelayProcess.h"

void IntroState::VOnUpdate(unsigned int elapsedTime)
{
	if(m_pFadeOutProc->IsDone())
	{
		shared_ptr<Evt_StateChange> pEvent(new Evt_StateChange(GS_MENU));
		EventManager::Get()->QueueEvent(pEvent);
	}
}

void IntroState::VOnEnter()
{
	INFO("Entering INTRO state");
	LOG("Entering INTRO state");
	ResourceManager::Get()->Clear();
	
	SetDisplay();
	SetProc();
}

void IntroState::VOnLeave()
{
	g_pApp->GetGfxMgr()->RemoveElement(m_pTextPolydash);
	g_pApp->GetGfxMgr()->RemoveElement(m_pTextDeveloppedBy);
	g_pApp->GetGfxMgr()->RemoveElement(m_pTextNames);
	g_pApp->GetGfxMgr()->RemoveElement(m_pFadeRect);
}

void IntroState::SetDisplay()
{
	float posX = g_pApp->GetScreenWidth()/2;
	float posY = 5*(g_pApp->GetScreenHeight()/16);
	m_pTextPolydash.reset(new GfxText(1, "operator.ttf", "A Polydash game", posX, posY));
	m_pTextPolydash->SetScale(0.85);
	
	posY = 9*(g_pApp->GetScreenHeight()/16);
	m_pTextDeveloppedBy.reset(new GfxText(1, "operator.ttf", "Developed by", posX, posY));
	m_pTextDeveloppedBy->SetScale(0.5);
	
	posY = 11*(g_pApp->GetScreenHeight()/16);
	m_pTextNames.reset(new GfxText(1, "operator.ttf", "Paul Gerst, Stan Wilhelm", posX, posY));
	m_pTextNames->SetScale(0.5);
	
	m_pFadeRect.reset(new GfxRect(0));
	m_pFadeRect->SetDimensions(g_pApp->GetScreenWidth(), g_pApp->GetScreenHeight());
	m_pFadeRect->SetPosition(g_pApp->GetScreenWidth()/2, g_pApp->GetScreenHeight()/2);
	m_pFadeRect->VSetColor(0, 0, 0);
	
	g_pApp->GetGfxMgr()->AddElement(m_pTextPolydash);
	g_pApp->GetGfxMgr()->AddElement(m_pTextDeveloppedBy);
	g_pApp->GetGfxMgr()->AddElement(m_pTextNames);
	g_pApp->GetGfxMgr()->AddElement(m_pFadeRect);
}

void IntroState::SetProc()
{
	ProcessSharedPtr pFirstDelayProc;
	pFirstDelayProc.reset(new DelayProcess(500));
	
	ProcessSharedPtr pFadeInProc;
	pFadeInProc.reset(new FadeProcess(m_pFadeRect, 255, 0, 0.2f));
	pFirstDelayProc->AttachChild(pFadeInProc);
	
	ProcessSharedPtr pSecondDelayProc;
	pSecondDelayProc.reset(new DelayProcess(1000));
	pFadeInProc->AttachChild(pSecondDelayProc);
	
	m_pFadeOutProc.reset(new FadeProcess(m_pFadeRect, 0, 255, 0.3f));
	pSecondDelayProc->AttachChild(m_pFadeOutProc);
	
	AttachLogicProcess(pFirstDelayProc);
}
