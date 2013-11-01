#ifndef FALLINGPIECEPROCESS_H
#define FALLINGPIECEPROCESS_H

#include "../Process.h"
#include "../../Event/IEvent.h"

class FallingPieceProcess : public Process
{
public :

	FallingPieceProcess();
	~FallingPieceProcess(); 

	virtual bool VOnInit();
	virtual void VUpdate(unsigned int elapsedTime);
	
private :

	void MainGameInputDelegate(EventSharedPtr pEvent);
	void RegisterEvents();
	void UnregisterEvents();
};

#endif
