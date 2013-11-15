#include "DisappearAnimationProcess.h"
#include "../../GameApp/SDLApp.h"
#include "../../Graphics/GfxManager.h"

DisappearAnimationProcess::DisappearAnimationProcess(GfxImageSharedPtr pImage, float speed, bool bRemove):
m_pImage(pImage),
m_speed(speed),
m_bRemove(bRemove)
{
}

DisappearAnimationProcess::~DisappearAnimationProcess()
{
}

void DisappearAnimationProcess::VUpdate(unsigned int elapsedTime)
{
	int alpha = m_pImage->GetAlpha();
	alpha -= elapsedTime*m_speed;
	
	m_pImage->SetScale(1 + 0.5*(1 - alpha/255.0f)); 
	
	if(alpha <= 128)
	{
		m_pImage->VSetColor(255, 255, 255);
	}
	
	if(alpha <= 0)
	{
		m_pImage->VSetAlpha(0);
		Success();
	}
	else
		m_pImage->VSetAlpha(alpha);
}

void DisappearAnimationProcess::VOnSuccess()
{
	if(m_bRemove)
	{
		g_pApp->GetGfxMgr()->RemoveElement(m_pImage);
	}
}
