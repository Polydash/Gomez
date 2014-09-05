/**
 * \file VerticalScrollProcess.cpp 
 * \brief Process allowing an image to scroll vertically
 */

#include "VerticalScrollProcess.h"
#include "../../GameApp/SDLApp.h"
#include "../../Graphics/GfxManager.h"

VerticalScrollProcess::VerticalScrollProcess(float speed, int layer, const std::string &fileName):
ScrollProcess(speed, layer)
{
	int m_frameHeight = g_pApp->GetScreenHeight();
	
	m_pFirstImage.reset(new GfxImage(m_layer, fileName));
	m_pSecondImage.reset(new GfxImage(m_layer, fileName));
	m_pFirstImage->SetPosition(g_pApp->GetScreenWidth()*m_pFirstImage->GetScale() / 2,
						  g_pApp->GetScreenHeight()*m_pFirstImage->GetScale() / 2);
	if(m_speed > 0)
	{
		m_pSecondImage->SetPosition(g_pApp->GetScreenWidth()*m_pSecondImage->GetScale() / 2,
							   m_pFirstImage->GetPosY() + m_frameHeight);
	}
	else
	{
		m_pSecondImage->SetPosition(g_pApp->GetScreenWidth()*m_pSecondImage->GetScale() / 2,
							   m_pFirstImage->GetPosY()- m_frameHeight);
	}
}

bool VerticalScrollProcess::VOnInit()
{
	g_pApp->GetGfxMgr()->AddElement(m_pFirstImage);
	g_pApp->GetGfxMgr()->AddElement(m_pSecondImage);
	
	return true;
}

void VerticalScrollProcess::VUpdate(unsigned int elapsedTime)
{
	int m_frameHeight = g_pApp->GetScreenHeight();
	
	m_pFirstImage->Translate(0, -m_speed*elapsedTime);
	if(m_speed > 0)
	{
		if(m_pFirstImage->GetPosY() + (m_frameHeight/2) <= 0)
		{
			m_pFirstImage->SetPosition(g_pApp->GetScreenWidth()*m_pFirstImage->GetScale() / 2,
								  g_pApp->GetScreenHeight()*m_pFirstImage->GetScale() / 2);
			m_pSecondImage->SetPosition(g_pApp->GetScreenWidth()*m_pSecondImage->GetScale() / 2,
								   m_pFirstImage->GetPosY() + m_frameHeight);
			
		}
		if(m_pFirstImage->GetPosY() + (m_frameHeight/2) < g_pApp->GetScreenHeight())
		{
			m_pSecondImage->Translate(0, -m_speed*elapsedTime);
		}
	}
	else
	{
		if(m_pFirstImage->GetPosY() - (m_frameHeight/2) >= g_pApp->GetScreenHeight())
		{
			m_pFirstImage->SetPosition(g_pApp->GetScreenWidth()*m_pFirstImage->GetScale() / 2,
								  g_pApp->GetScreenHeight()*m_pFirstImage->GetScale() / 2);
			m_pSecondImage->SetPosition(g_pApp->GetScreenWidth()*m_pSecondImage->GetScale() / 2,
								   m_pFirstImage->GetPosY() - m_frameHeight);
			
		}
		if(m_pFirstImage->GetPosY() - (m_frameHeight/2) > 0)
		{
			m_pSecondImage->Translate(0, -m_speed*elapsedTime);
		}
	}
}		

void VerticalScrollProcess::VOnSuccess()
{
	g_pApp->GetGfxMgr()->RemoveElement(m_pFirstImage);
	g_pApp->GetGfxMgr()->RemoveElement(m_pSecondImage);
}

void VerticalScrollProcess::VOnAbort()
{
	g_pApp->GetGfxMgr()->RemoveElement(m_pFirstImage);
	g_pApp->GetGfxMgr()->RemoveElement(m_pSecondImage);
}
