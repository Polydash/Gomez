#include "DelayProcess.h"

DelayProcess::DelayProcess(unsigned long timeToDelay):
m_timeToDelay(timeToDelay),
m_timeDelayed(0)
{
}

DelayProcess::~DelayProcess()
{
}

void DelayProcess::VUpdate(unsigned int elapsedTime)
{
	m_timeDelayed += elapsedTime;
	if(m_timeDelayed >= m_timeToDelay)
		Success();
}
