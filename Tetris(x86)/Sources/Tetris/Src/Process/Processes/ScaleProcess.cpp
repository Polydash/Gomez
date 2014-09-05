/**
 * \file ScaleProcess.cpp 
 * \brief Process allowing an image to scale to a target value
 */

#include "ScaleProcess.h"
#include "../../GameApp/SDLApp.h"
#include "../../Graphics/GfxManager.h"

ScaleProcess::ScaleProcess(GfxImageSharedPtr pImage, float scaleStart, float scaleFinal, float velocity, float accel):
m_pImage(pImage),
m_scaleStart(scaleStart),
m_scaleFinal(scaleFinal),
m_velocity(velocity),
m_accel(accel)
{
}

ScaleProcess::~ScaleProcess()
{
}

bool ScaleProcess::VOnInit()
{
	m_pImage->SetScale(m_scaleStart);
	return true;
}

void ScaleProcess::VUpdate(unsigned int elapsedTime)
{	
	float currentScale = m_pImage->GetScale();
	float diffScale = m_scaleFinal - currentScale;
	
	m_velocity += m_accel;
	
	if(fabs(m_velocity*elapsedTime) > fabs(diffScale))
	{
		m_pImage->SetScale(m_scaleFinal);
		Success();
	}
	else if(diffScale > 0)
		m_pImage->SetScale(currentScale + m_velocity*elapsedTime);
	else
		m_pImage->SetScale(currentScale - m_velocity*elapsedTime);
}		
