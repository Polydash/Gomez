#ifndef FADEPROCESS_H
#define FADEPROCESS_H

/**
 * \file FadeProcess.h 
 * \brief Process allowing a Graphic Element to fade to a target alpha
 */

#include "../Process.h"
#include "../../Graphics/GfxElement.h"

/**
 * \class FadeProcess 
 * \brief Process allowing a Graphic Element to fade to a target alpha
 */
class FadeProcess : public Process
{
private :

	GfxElementSharedPtr m_pElement;
	float m_currentAlpha;
	byte m_targetAlpha;
	float m_speed;
	bool m_bIsAlphaSet;
	
public :

	FadeProcess(GfxElementSharedPtr pElement, byte targetAlpha, float speed);
	FadeProcess(GfxElementSharedPtr pElement, byte alpha, byte targetAlpha, float speed);
	virtual ~FadeProcess();

	virtual void VUpdate(unsigned int elapsedTime);

protected :

	virtual bool VOnInit();
	virtual void VOnSuccess();
};

#endif
