#ifndef VERTICALSCROLLPROCESS_H
#define VERTICALSCROLLPROCESS_H

/**
 * \file VerticalScrollProcess.h 
 * \brief Process allowing an image to scroll vertically
 */

#include "ScrollProcess.h"

class VerticalScrollProcess : public ScrollProcess
{
public :
	
	VerticalScrollProcess(float speed, int layer, const std::string &fileName);
	virtual ~VerticalScrollProcess(){}
	
	virtual bool VOnInit();
	virtual void VUpdate(unsigned int elapsedTime);
	
protected :

	virtual void VOnSuccess();
	virtual void VOnAbort();
};

#endif
