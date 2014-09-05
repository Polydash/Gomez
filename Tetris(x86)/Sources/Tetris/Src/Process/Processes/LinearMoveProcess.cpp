/**
 * \file LinearMoveProcess.cpp 
 * \brief Process allowing an image to move linearly to a target position
 */

#include "LinearMoveProcess.h"
#include "../../GameStd.h"
#include "../../GameApp/SDLApp.h"
#include "../../Graphics/GfxManager.h"

LinearMoveProcess::LinearMoveProcess(GfxElementSharedPtr pElement, float targetX, float targetY, float speed, bool bRemove):
m_pElement(pElement),
m_speed(speed),
m_targetX(targetX),
m_targetY(targetY),
m_bRemove(bRemove)
{
}

LinearMoveProcess::~LinearMoveProcess()
{
}

void LinearMoveProcess::VUpdate(unsigned int elapsedTime)
{
	float diffX = m_targetX - m_pElement->GetPosX();
	float diffY = m_targetY - m_pElement->GetPosY();
	
	if(fabs(diffX) < fabs(m_speedX*elapsedTime) || fabs(diffY) < fabs(m_speedY*elapsedTime))
	{
		m_pElement->SetPosition(m_targetX, m_targetY);
		Success();
	}
	else
	{
		m_pElement->Translate(m_speedX*elapsedTime, m_speedY*elapsedTime);
	}
}

bool LinearMoveProcess::VOnInit()
{
	float diffX = m_targetX - m_pElement->GetPosX();
	float diffY = m_targetY - m_pElement->GetPosY();
	
	if(fabs(diffY) > fabs(diffX))
	{
		m_speedX = (diffX/fabs(diffY))*m_speed;
		if(diffX < 0)
			m_speedY = -m_speed;
		else
			m_speedY = m_speed;
	}
	else
	{
		m_speedY = (diffY/fabs(diffX))*m_speed;
		if(diffX < 0)
			m_speedX = -m_speed;
		else
			m_speedX = m_speed;
	}
	
	return true;
}

void LinearMoveProcess::VOnSuccess()
{
	if(m_bRemove)
		g_pApp->GetGfxMgr()->RemoveElement(m_pElement);
}

void LinearMoveProcess::VOnAbort()
{
	if(m_bRemove)
		g_pApp->GetGfxMgr()->RemoveElement(m_pElement);
}
