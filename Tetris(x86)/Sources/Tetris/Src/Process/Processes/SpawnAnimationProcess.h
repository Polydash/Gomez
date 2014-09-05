#ifndef SPAWNANIMATIONPROCESS_H
#define SPAWNANIMATIONPROCESS_H

/**
 * \file SpawnAnimationProcess.h 
 * \brief Process allowing an image to appear quickly 
 */

#include "../Process.h"
#include "../../Graphics/GfxImage.h"

/**
 * \class SpawnAnimationProcess
 * \brief Process allowing an image to appear quickly 
 */
class SpawnAnimationProcess : public Process
{
private :

	GfxImageSharedPtr m_pImage;
	
	float m_speed;

public :

	SpawnAnimationProcess(GfxImageSharedPtr pImage, float speed);
	~SpawnAnimationProcess();
	
	virtual void VUpdate(unsigned int elapsedTime);
	
protected :

	virtual bool VOnInit();
};

#endif
