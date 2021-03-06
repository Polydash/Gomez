#ifndef HORIZONTALSCROLLPROCESS_H
#define HORIZONTALSCROLLPROCESS_H

/**
 * \file HorizontalScrollProcess.h 
 * \brief Process allowing an image to scroll horizontally
 */

#include "ScrollProcess.h"

/**
 * \class HorizontalScrollProcess
 * \brief Process allowing an image to scroll horizontally
 */
class HorizontalScrollProcess : public ScrollProcess
{
public :
	
	HorizontalScrollProcess(float speed, int layer, const std::string &fileName);
	virtual ~HorizontalScrollProcess(){}
	
	virtual bool VOnInit();
	virtual void VUpdate(unsigned int elapsedTime);
	
protected :

	virtual void VOnSuccess();
	virtual void VOnAbort();
};

#endif
