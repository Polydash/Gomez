/**
 * \file FadeProcess.cpp 
 * \brief Process allowing a Graphic Element to fade to a target alpha
 */

#include "FadeProcess.h"
#include "../../GameApp/SDLApp.h"
#include "../../Graphics/GfxManager.h"
#include "../../GameStd.h"

FadeProcess::FadeProcess(GfxElementSharedPtr pElement, byte targetAlpha, float speed):
m_pElement(pElement),
m_targetAlpha(targetAlpha),
m_speed(speed),
m_bIsAlphaSet(false)
{	
}

FadeProcess::FadeProcess(GfxElementSharedPtr pElement, byte alpha, byte targetAlpha, float speed):
m_pElement(pElement),
m_currentAlpha(alpha),
m_targetAlpha(targetAlpha),
m_speed(speed),
m_bIsAlphaSet(true)
{	
}

FadeProcess::~FadeProcess()
{
}

bool FadeProcess::VOnInit()
{
	if(!m_bIsAlphaSet)
		m_currentAlpha = m_pElement->GetAlpha();
		
	return true;
}

void FadeProcess::VUpdate(unsigned int elapsedTime)
{
	float delta = m_speed*elapsedTime;
	
	if(fabs(m_targetAlpha - m_currentAlpha) < fabs(delta))
	{
		m_currentAlpha = m_targetAlpha;
		Success();
	}
	else
	{
		int sign = (((float)m_targetAlpha - m_currentAlpha) > 0) ? 1 : -1;
		m_currentAlpha += sign*delta;	
	}
	
	m_pElement->VSetAlpha((byte)m_currentAlpha);	
}

void FadeProcess::VOnSuccess()
{
	m_pElement->VSetAlpha((byte)m_targetAlpha);
}
