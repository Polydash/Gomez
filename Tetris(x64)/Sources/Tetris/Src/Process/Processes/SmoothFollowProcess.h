#ifndef SMOOTHFOLLOWPROCESS_H
#define SMOOTHFOLLOWPROCESS_H

/**
 * \file SmoothFollowProcess.h 
 * \brief Process allowing an image to smoothly follow a target position and angle 
 */

#include "../Process.h"
#include "../../Graphics/GfxImage.h"

/**
 * \class SmoothFollowProcess
 * \brief Process allowing an image to smoothly follow a target position and angle 
 */
class SmoothFollowProcess : public Process
{
private :

	GfxImageSharedPtr m_pImage;
	
	float m_posX, m_posY;
	float m_speed;
	
	double m_angle;
	bool m_bEndIfStatic;

public :

	SmoothFollowProcess(GfxImageSharedPtr pImage, float speed, bool endIfStatic = false);
	~SmoothFollowProcess();
	
	virtual void VUpdate(unsigned int elapsedTime);
	
	void SetPosition(float posX, float posY);
	void Translate(float deltaX, float deltaY);
	void SetAngle(double angle);
	void AddAngle(double deltaAngle);
	
	bool IsMoving(float diff) const;

protected :

	virtual void VOnSuccess();

private :

	void ClearMove();
};

#endif
