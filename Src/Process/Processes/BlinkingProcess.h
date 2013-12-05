#ifndef BLINKINGPROCESS_H
#define BLINKINGPROCESS_H

/**
 * \file BlinkingProcess.h 
 * \brief Process allowing an image to blink repeatedly 
 */

#include "../Process.h"
#include "../../Graphics/GfxImage.h"

class BlinkingProcess : public Process
{
private :

	GfxImageSharedPtr m_pImage;
	
	float m_initScale;
	float m_scaleAmplitude, m_fadeAmplitude;
	float m_angle, m_speed;
	
public :

	BlinkingProcess(GfxImageSharedPtr pImage, float scaleAmplitude, float fadeAmplitude, float speed);
	~BlinkingProcess();
	
	virtual void VUpdate(unsigned int elapsedTime);
	
private :

	virtual bool VOnInit();
	virtual void VOnSuccess();
};

#endif
