/**
 * \file HorizontalScrollProcess.cpp
 * \brief Process allowing an image to scroll horizontally
 */

#include "HorizontalScrollProcess.h"
#include "../../GameApp/SDLApp.h"
#include "../../Graphics/GfxManager.h"

HorizontalScrollProcess::HorizontalScrollProcess(float speed, int layer, const std::string &fileName):
ScrollProcess(speed, layer)
{
	int frameWidth = g_pApp->GetScreenWidth();
	
	m_pFirstImage.reset(new GfxImage(m_layer, fileName));
	m_pSecondImage.reset(new GfxImage(m_layer, fileName));
	m_pFirstImage->SetPosition(g_pApp->GetScreenWidth()*m_pFirstImage->GetScale() / 2,
						  g_pApp->GetScreenHeight()*m_pFirstImage->GetScale() / 2);
	if(m_speed > 0)
	{
		m_pSecondImage->SetPosition(m_pFirstImage->GetPosX() + frameWidth,
							   g_pApp->GetScreenHeight()*m_pSecondImage->GetScale() / 2);
	}
	else
	{
		m_pSecondImage->SetPosition(m_pFirstImage->GetPosX() - frameWidth,
							   g_pApp->GetScreenHeight()*m_pSecondImage->GetScale() / 2);
	}
}

bool HorizontalScrollProcess::VOnInit()
{
	g_pApp->GetGfxMgr()->AddElement(m_pFirstImage);
	g_pApp->GetGfxMgr()->AddElement(m_pSecondImage);
	
	return true;
}

void HorizontalScrollProcess::VUpdate(unsigned int elapsedTime)
{
	int frameWidth = g_pApp->GetScreenWidth();
	
	m_pFirstImage->Translate(-m_speed*elapsedTime, 0);
	if(m_speed > 0)
	{
		if(m_pFirstImage->GetPosX() + (frameWidth/2) <= 0)
		{
			m_pFirstImage->SetPosition(g_pApp->GetScreenWidth()*m_pFirstImage->GetScale() / 2,
								  g_pApp->GetScreenHeight()*m_pFirstImage->GetScale() / 2);
			m_pSecondImage->SetPosition(m_pFirstImage->GetPosX() + frameWidth,
								   g_pApp->GetScreenHeight()*m_pSecondImage->GetScale() / 2);
			
		}
		if(m_pFirstImage->GetPosX() + (frameWidth/2) < g_pApp->GetScreenWidth())
		{
			m_pSecondImage->Translate(-m_speed*elapsedTime, 0);
		}
	}
	else
	{
		if(m_pFirstImage->GetPosX() - (frameWidth/2) >= g_pApp->GetScreenWidth())
		{
			m_pFirstImage->SetPosition(g_pApp->GetScreenWidth()*m_pFirstImage->GetScale() / 2,
								  g_pApp->GetScreenHeight()*m_pFirstImage->GetScale() / 2);
			m_pSecondImage->SetPosition(m_pFirstImage->GetPosX() - frameWidth,
								   g_pApp->GetScreenHeight()*m_pSecondImage->GetScale() / 2);
			
		}
		if(m_pFirstImage->GetPosX() - (frameWidth/2) > 0)
		{
			m_pSecondImage->Translate(-m_speed*elapsedTime, 0);
		}
	}
}		

void HorizontalScrollProcess::VOnSuccess()
{
	g_pApp->GetGfxMgr()->RemoveElement(m_pFirstImage);
	g_pApp->GetGfxMgr()->RemoveElement(m_pSecondImage);
}

void HorizontalScrollProcess::VOnAbort()
{
	g_pApp->GetGfxMgr()->RemoveElement(m_pFirstImage);
	g_pApp->GetGfxMgr()->RemoveElement(m_pSecondImage);
}
