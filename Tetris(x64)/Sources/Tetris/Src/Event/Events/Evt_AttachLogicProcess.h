#ifndef EVT_ATTACHLOGICPROCESS_H
#define EVT_ATTACHLOGICPROCESS_H

/**
 * \file Evt_AttachLogicProcess.h 
 * \brief Attach Logic Process Event
 */

#include "../IEvent.h"

/**
 * \class Evt_AttachLogicProcess
 * \brief Attach Logic Process Event
 * 
 * Event allowing an object to attach a logic process to the current
 * GameState.
 */
class Evt_AttachLogicProcess : public IEvent
{
private :

	ProcessSharedPtr m_pProcess;
	
public :
	
	Evt_AttachLogicProcess(ProcessSharedPtr pProcess){ m_pProcess = pProcess; }
	~Evt_AttachLogicProcess(){}
	
	ProcessSharedPtr GetProcessPtr() const{ return m_pProcess; }
	
	virtual eEventType VGetType() const{ return ET_ATTACHLOGICPROCESS; } 
	
};

#endif
