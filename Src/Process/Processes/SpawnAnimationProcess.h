#ifndef SPAWNANIMATIONPROCESS_H
#define SPAWNANIMATIONPROCESS_H

#include "../Process.h"
#include "../../Graphics/GfxImage.h"

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
