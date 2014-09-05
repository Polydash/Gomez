/**
 * \file SpawnAnimationProcess.cpp 
 * \brief Process allowing an image to appear smoothly 
 */

#include "SpawnAnimationProcess.h"

SpawnAnimationProcess::SpawnAnimationProcess(GfxImageSharedPtr pImage, float speed):
m_pImage(pImage),
m_speed(speed)
{
	m_pImage->SetScale(0.01f);
	m_pImage->VSetAlpha(0);
}

SpawnAnimationProcess::~SpawnAnimationProcess()
{
}

void SpawnAnimationProcess::VUpdate(unsigned int elapsedTime)
{
	float scale = m_pImage->GetScale();
	int alpha = m_pImage->GetAlpha();
	
	scale += m_speed*elapsedTime;
	alpha += m_speed*elapsedTime*255;
	
	if(scale >= 1.0f)
		m_pImage->SetScale(1.0f);
	else
		m_pImage->SetScale(scale);
		
	if(alpha >= 255)
		m_pImage->VSetAlpha(255);
	else
		m_pImage->VSetAlpha(alpha);
		
	if(scale >= 1.0f && alpha >= 255)
		Success();
}

bool SpawnAnimationProcess::VOnInit()
{
	return true;
}
