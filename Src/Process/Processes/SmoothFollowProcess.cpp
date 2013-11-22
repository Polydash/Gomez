#include "SmoothFollowProcess.h"

SmoothFollowProcess::SmoothFollowProcess(GfxImageSharedPtr pImage, float speed, bool endIfStatic):
m_pImage(pImage),
m_speed(speed),
m_bEndIfStatic(endIfStatic)
{
	m_posX  = pImage->GetPosX();
	m_posY  = pImage->GetPosY();
	m_angle = pImage->GetAngle();
}

SmoothFollowProcess::~SmoothFollowProcess()
{
}

void SmoothFollowProcess::VUpdate(unsigned int elapsedTime)
{
	float diffX = m_posX - m_pImage->GetPosX();
	float diffY = m_posY - m_pImage->GetPosY();
	
	float deltaX = diffX*m_speed*elapsedTime;
	float deltaY = diffY*m_speed*elapsedTime;
	
	if(fabs(deltaX) > fabs(diffX))
		deltaX = diffX;
	
	if(fabs(deltaY) > fabs(diffY))
		deltaY = diffY;
	
	m_pImage->Translate(deltaX, deltaY);
	
	double diffAngle = m_angle - m_pImage->GetAngle();
		
	if(diffAngle < -180)
		diffAngle += 360;
	else if(diffAngle > 180)
		diffAngle -= 360;
		
	double deltaAngle = diffAngle*m_speed*elapsedTime;
	
	if(fabs(deltaAngle) > fabs(diffAngle))
		deltaAngle = diffAngle;
		
	m_pImage->SetAngle(m_pImage->GetAngle() + deltaAngle);
	
	if(!IsMoving(0.5f) && m_bEndIfStatic)
		Success();
}

void SmoothFollowProcess::SetPosition(float posX, float posY)
{
	m_posX = posX;
	m_posY = posY;
}

void SmoothFollowProcess::Translate(float deltaX, float deltaY)
{
	m_posX += deltaX;
	m_posY += deltaY;
}

void SmoothFollowProcess::SetAngle(double angle)
{
	m_angle = angle;
}

void SmoothFollowProcess::AddAngle(double deltaAngle)
{
	m_angle += deltaAngle;
}

bool SmoothFollowProcess::IsMoving(float diff) const
{
	float diffX = m_posX - m_pImage->GetPosX();
	float diffY = m_posY - m_pImage->GetPosY();
	double diffAngle = m_angle - m_pImage->GetAngle();
	
	if(diffAngle < -180)
		diffAngle += 360;
	else if(diffAngle > 180)
		diffAngle -= 360;

	if(fabs(diffX) > diff || fabs(diffY) > diff || fabs(diffAngle) > diff)
		return true;
	
	return false;
}

void SmoothFollowProcess::VOnSuccess()
{
	ClearMove();
}

void SmoothFollowProcess::ClearMove()
{
	m_pImage->SetPosition(m_posX, m_posY);
}
