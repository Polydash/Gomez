#ifndef EVT_ATTACHLOGICPROCESS_H
#define EVT_ATTACHLOGICPROCESS_H

#include "../IEvent.h"

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
