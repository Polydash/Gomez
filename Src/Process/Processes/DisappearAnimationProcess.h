#ifndef DISAPPEARANIMATIONPROCESS_H
#define DISAPPEARANIMATIONPROCESS_H

#include "../Process.h"
#include "../../Graphics/GfxImage.h"

class DisappearAnimationProcess : public Process
{
private :

	GfxImageSharedPtr m_pImage;

	float m_speed;

public :

	DisappearAnimationProcess(GfxImageSharedPtr pImage, float speed);
	~DisappearAnimationProcess();
	
	virtual void VUpdate(unsigned int elapsedTime);
};

#endif
