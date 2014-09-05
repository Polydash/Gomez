#ifndef LINEARMOVEPROCESS_H
#define LINEARMOVEPROCESS_H

/**
 * \file LinearMoveProcess.h 
 * \brief Process allowing an image to move linearly to a target position
 */

#include "../Process.h"
#include "../../Graphics/GfxElement.h"

/**
 * \class LinearMoveProcess 
 * \brief Process allowing an image to move linearly to a target position
 */
class LinearMoveProcess : public Process
{
private :

	GfxElementSharedPtr m_pElement;
	
	float m_speed, m_speedX, m_speedY;
	float m_targetX, m_targetY;
	
	bool m_bRemove;
	
public :
	
	LinearMoveProcess(GfxElementSharedPtr pElement, float targetX, float targetY, float speed, bool bRemove = false);
	~LinearMoveProcess();
	
	virtual void VUpdate(unsigned int elapsedTime);
	
protected :

	virtual bool VOnInit();
	virtual void VOnSuccess();
	virtual void VOnAbort();
};

#endif
