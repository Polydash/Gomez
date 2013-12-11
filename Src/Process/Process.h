#ifndef PROCESS_H
#define PROCESS_H

/**
 * \file Process.h 
 * \brief Process Base class 
 */

#include <tr1/memory>
using std::tr1::shared_ptr;

class Process;

/// Typedef defining a process shared pointer
typedef shared_ptr<Process> ProcessSharedPtr; 

/// Enumeration defining processes states
enum eProcessState { PS_UNINITIALIZED,
					 PS_RUNNING,
					 PS_ABORTED,
					 PS_SUCCEEDED
				   };

/**
 * \class Process
 * \brief Process Base class
 * 
 * Process class needed by ProcessManager. Every Process must inherit
 * from this class.
 * 
 * Processes may have a "child" process attached to it. If the current
 * process successes, its "child" process is attached (allowing processes
 * to start one after another). 
 */
class Process
{
private :

	ProcessSharedPtr m_pChild;
	eProcessState	 m_state;
	
public :

	Process();
	virtual ~Process();
	
	void Success();
	void Abort();
	bool Init();
	
	virtual void VUpdate(unsigned int elapsedTime) = 0;
	
	bool IsDone() const;
	eProcessState GetState() const;
	
	void AttachChild(ProcessSharedPtr pProcess);
	ProcessSharedPtr GetChild() const;
	ProcessSharedPtr RemoveChild();
	
protected :

	virtual bool VOnInit(){ return true; }
	virtual void VOnSuccess(){}
	virtual void VOnAbort(){}
};

#endif
