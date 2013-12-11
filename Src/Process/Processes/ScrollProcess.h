#ifndef SCROLLPROCESS_H
#define SCROLLPROCESS_H

/**
 * \file ScrollProcess.h 
 * \brief Base Process allowing an image to scroll 
 */

#include "../Process.h"
#include "../../Graphics/GfxImage.h"

/**
 * \class ScrollProcess 
 * \brief Base Process allowing an image to scroll 
 */
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
	
	virtual void VUpdate(unsigned int elapsedTime) = 0;
};

#endif
