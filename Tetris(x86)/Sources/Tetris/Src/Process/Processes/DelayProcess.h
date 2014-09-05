#ifndef DELAYPROCESS_H
#define DELAYPROCESS_H

/**
 * \file DelayProcess.h 
 * \brief Process creating a delay
 */

#include "../Process.h"

/**
 * \class DelayProcess 
 * \brief Process creating a delay
 */
class DelayProcess : public Process
{
private:

	unsigned long m_timeToDelay;
	unsigned long m_timeDelayed;
	
public:

	DelayProcess(unsigned long timeToDelay);
	~DelayProcess();

	virtual void VUpdate(unsigned int elapsedTime);
};

#endif
