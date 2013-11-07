#ifndef SMOOTHFOLLOWPROCESS_H
#define SMOOTHFOLLOWPROCESS_H

#include "../Process.h"
#include "../../Graphics/GfxImage.h"

class SmoothFollowProcess : public Process
{
private :

	GfxImageSharedPtr m_pImage;
	
	float m_posX, m_posY;
	float m_speed;
	
	double m_angle;

public :

	SmoothFollowProcess(GfxImageSharedPtr pImage, float speed);
	~SmoothFollowProcess();
	
	virtual void VUpdate(unsigned int elapsedTime);
	
	void SetPosition(float posX, float posY);
	void Translate(float deltaX, float deltaY);
	void SetAngle(double angle);
	void AddAngle(double deltaAngle);
	
	bool IsMoving(float diff) const;

protected :

	void VOnSuccess();

private :

	void ClearMove();
};

#endif
