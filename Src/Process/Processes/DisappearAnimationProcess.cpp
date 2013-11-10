#include "DisappearAnimationProcess.h"

DisappearAnimationProcess::DisappearAnimationProcess(GfxImageSharedPtr pImage, float speed):
m_pImage(pImage),
m_speed(speed)
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
