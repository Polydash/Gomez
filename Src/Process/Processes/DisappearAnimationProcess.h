#ifndef DISAPPEARANIMATIONPROCESS_H
#define DISAPPEARANIMATIONPROCESS_H

#include "../Process.h"
#include "../../Graphics/GfxImage.h"

class DisappearAnimationProcess : public Process
{
private :

	GfxImageSharedPtr m_pImage;

	float m_speed;
	bool m_bRemove;

public :

	DisappearAnimationProcess(GfxImageSharedPtr pImage, float speed, bool bRemove = false);
	~DisappearAnimationProcess();
	
	virtual void VUpdate(unsigned int elapsedTime);
	virtual void VOnSuccess();
};

#endif
