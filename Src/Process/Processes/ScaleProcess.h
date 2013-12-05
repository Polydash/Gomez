#ifndef SCALEPROCESS_H
#define SCALEPROCESS_H

/**
 * \file ScaleProcess.h 
 * \brief Process allowing an image to scale to a target value
 */

#include "../Process.h"
#include "../../Graphics/GfxImage.h"

class ScaleProcess : public Process
{
private :

	GfxImageSharedPtr m_pImage;
	
	float m_scaleStart, m_scaleFinal;
	float m_velocity;
	float m_accel;

public :
	
	ScaleProcess(GfxImageSharedPtr pImage, float scale, float scaleFinal, float velocity, float accel);
	virtual ~ScaleProcess();
	
	virtual bool VOnInit();
	virtual void VUpdate(unsigned int elapsedTime);
};

#endif
