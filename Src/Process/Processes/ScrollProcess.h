#ifndef SCROLLPROCESS_H
#define SCROLLPROCESS_H

#include "../Process.h"
#include "../../Graphics/GfxImage.h"

class ScrollProcess : public Process
{
protected :

	GfxImageSharedPtr m_pFirstImage;
	GfxImageSharedPtr m_pSecondImage;
	
	float m_speed;
	int m_layer;

public :
	
	ScrollProcess(float speed, int layer);
	virtual ~ScrollProcess();
	
	virtual void VUpdate(unsigned int elapsedTime){}
};

#endif
