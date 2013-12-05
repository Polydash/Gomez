/**
 * \file BlinkingProcess.cpp 
 * \brief Process allowing an image to blink repeatedly 
 */

#include "BlinkingProcess.h"
#include "../../GameStd.h"

BlinkingProcess::BlinkingProcess(GfxImageSharedPtr pImage, float scaleAmplitude, float fadeAmplitude, float speed):
m_pImage(pImage),
m_scaleAmplitude(scaleAmplitude),
m_fadeAmplitude(fadeAmplitude),
m_angle(0.0f),
m_speed(speed)
{
	if(m_speed < 0)
		m_speed = fabs(m_speed);
		
	if(m_fadeAmplitude > 255)
		m_fadeAmplitude = 255;
}

BlinkingProcess::~BlinkingProcess()
{
}

void BlinkingProcess::VUpdate(unsigned int elapsedTime)
{
	m_angle += m_speed*elapsedTime;
	if(m_angle > 2*PI)
		m_angle -= 2*PI;
		
	m_pImage->SetScale(m_initScale + sin(m_angle)*m_scaleAmplitude);
	m_pImage->VSetAlpha((byte) (255 - (int) m_fadeAmplitude/2) + cos(m_angle)*((int) m_fadeAmplitude/2));
}

bool BlinkingProcess::VOnInit()
{
	m_initScale = m_pImage->GetScale();
	return true;
}

void BlinkingProcess::VOnSuccess()
{
	m_pImage->SetScale(m_initScale);
	m_pImage->VSetAlpha(255);
}
